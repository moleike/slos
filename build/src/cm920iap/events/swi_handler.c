/*
 *  ____________________________________________________________________
 * 
 *  Copyright (c) 2002, Andrew N. Sloss, Chris Wright and Dominic Symes
 *  All rights reserved.
 *  ____________________________________________________________________
 * 
 *  NON-COMMERCIAL USE License
 *  
 *  Redistribution and use in source and binary forms, with or without 
 *  modification, are permitted provided that the following conditions 
 *  are met: 
 *  
 *  1. For NON-COMMERCIAL USE only.
 * 
 *  2. Redistributions of source code must retain the above copyright 
 *     notice, this list of conditions and the following disclaimer. 
 * 
 *  3. Redistributions in binary form must reproduce the above 
 *     copyright notice, this list of conditions and the following 
 *     disclaimer in the documentation and/or other materials provided 
 *     with the distribution. 
 * 
 *  4. All advertising materials mentioning features or use of this 
 *     software must display the following acknowledgement:
 * 
 *     This product includes software developed by Andrew N. Sloss,
 *     Chris Wright and Dominic Symes. 
 * 
 *   THIS SOFTWARE IS PROVIDED BY THE CONTRIBUTORS ``AS IS'' AND ANY 
 *   EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE 
 *   IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR 
 *   PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE CONTRIBUTORS BE 
 *   LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, 
 *   OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, 
 *   PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, 
 *   OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY 
 *   THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR 
 *   TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT 
 *   OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY 
 *   OF SUCH DAMAGE. 
 * 
 *  If you have questions about this license or would like a different
 *  license please email :
 * 
 * 	andrew@sloss.net
 * 
 * 
 */
 
/*****************************************************************************
 * Simple Little Operating System - SLOS
 *****************************************************************************/

/*****************************************************************************
 *
 * Module       : handler.c
 * Description  : provides the SWI handlers
 * Originator   : Andrew N. Sloss
 * History      :
 *	
 * November 4th 2001 Andrew N. Sloss
 * - corrected the header
 *
 * January 3rd 2002 Andrew N. Sloss
 * - added the bringup swi for trace and fatal error
 *
 * April 30th 2002 Andrew N. Sloss
 * - cleaned up for Integrator port
 *
 *****************************************************************************/

/*****************************************************************************
 * IMPORT
 *****************************************************************************/

#include "../../core/all.h"

/*****************************************************************************
 * MACROS
 *****************************************************************************/

/* Mode control bits .......................... */

#define SYSTEM 0x1f
#define SVC    0x13
#define USER   0x10

/* IRQ control bits ........................... */

#define IRQoN  0x40
#define IRQoFF 0xc0

/* Low-level FIQ debug ........................ */

void  modifyControlCPSR(unsigned int);
void  bringUpSetR8fiq(unsigned int);
void  bringUpSetR9fiq(unsigned int);
void  bringUpSetR10fiq(unsigned int);

extern unsigned int STATE;

/*****************************************************************************
 * ROUTINES
 *****************************************************************************/

/* -- events_swi_e7t_handler --------------------------------------------------
 *
 * Descriptions : handler the swi calls for the e7t
 * 
 * Parameters   : int swi_number - swi being called
 *              : SwiRegs *r	 - pointer to the SWI registers
 * Return       : CallBack pointer
 * Other        :
 *
 * This function should migrate to be generic
 *
 */

CallBack eventsSWIHandler(int swi_number, SwiRegs *r) 
{
  switch (swi_number) 
  {

  /**********************************************************************
   * SLOS SWI's 
   **********************************************************************/

  case /* SWI */ SLOS:

    switch (r->r[0]) 
    {
   /* -----------------------------------------------------------------
     * Low level Debug SWI for debugging before the operating system is
     * up and running. The following register hold the debug information.
     *
     *  r8fiq  - fatal error 
     *  r9fiq  - trace entry value
     *  r10fiq - trace exit value
     *
     * -----------------------------------------------------------------
     */
    
    case /* SWI */ BringUp_Trace: 

      switch (r->r[1])
      {
      case 123: /* ENTRY into routine ...................... */
      bringUpSetR9fiq (r->r[2]);
      break;

      case 321: /* EXIT into routine ....................... */
      bringUpSetR10fiq (r->r[2]);
      break;
      }

    break;

    case /* SWI */ BringUp_FatalError:   
    bringUpSetR8fiq (r->r[1]);
     
    fatalerror: goto fatalerror; /* setup infinite loop ... */
     
    break;

    /* -----------------------------------------------------------------
     * Device Driver SWI's for controlling and initializing device
     * drivers
     * -----------------------------------------------------------------
     */

    case /* SWI */ Event_IODeviceInit:
    ioInitializeDrivers ();
    r->r[0] = 1;
    r->r[1] = 2;
    break;
 
    default:

    /* ----------------------------------------------------------------
     * switch to SYSTEM mode and switch ON IRQ interrupts. 
     * ----------------------------------------------------------------
     */

    if (STATE!=1) 
    {
    /* Enable IRQ interrupts and switch to SYSTEM mode */	    
    asm volatile ("MSR CPSR_c,#0x5f");
    }

      switch (r->r[0]) 
      {
		  
      case /* SWI */ Event_IODeviceOpen:
      r->r[0] = (unsigned int) ioOpenDriver ((UID *)r->r[1],r->r[2],r->r[3]);
      break;

      case /* SWI */ Event_IODeviceClose:
      r->r[0] = (unsigned int) ioCloseDriver ((device_treestr *)r->r[1],(UID)r->r[2]);
      break;
	
      case /* SWI */ Event_IODeviceWriteByte:
      ioWriteByte ((device_treestr *)r->r[1],(UID)r->r[2],(BYTE)r->r[3]);
      break;
	
      case /* SWI */ Event_IODeviceReadByte:
      r->r[0] = (unsigned int) ioReadByte ((device_treestr *)r->r[1],(UID)r->r[2]);
      break;

      case /* SWI */ Event_IODeviceWriteBit:
      ioWriteBit ((device_treestr *)r->r[1],(UID)r->r[2],(UINT)r->r[3]);
      break;

      case /* SWI */ Event_IODeviceReadBit:
      r->r[0] = (unsigned int) ioReadBit ((device_treestr *)r->r[1],(UID)r->r[2]);
      break;

      case /* SWI */ Event_IODeviceWriteBlock:
      ioWriteBlock ((device_treestr *)r->r[1],(UID)r->r[2],(void *)r->r[3]);
      break;

      case /* SWI */ Event_IODeviceReadBlock:
      r->r[0] = (unsigned int) ioReadBlock ((device_treestr *)r->r[1],(UID)r->r[2]);
      break;
      
      }

    asm volatile ("MSR CPSR_c,#0xD3");
    }  
 }
return 0;
}

