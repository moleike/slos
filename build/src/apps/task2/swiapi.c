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
 * Module       : swiapi.c
 * Description  : provide a SWI interface for calling the kernel
 * Platform     : Integrator/AP
 * History      :
 *
 * 8 Febuary 2004 Andrew N. Sloss
 * - added header information 
 *
 *****************************************************************************/

/*****************************************************************************
 * IMPORT
 *****************************************************************************/
 
#include "../../cm920iap/events/swis.h"
#include "../../devices/ddf_frame.h"

/*****************************************************************************
 * MACROS
 *****************************************************************************/

#define UINT unsigned int

/*****************************************************************************
 * DATATYPES
 *****************************************************************************/

typedef struct 
{
 unsigned int r[4];
} registerstr;

/*****************************************************************************
 * STATICS
 *****************************************************************************/

registerstr rs;

/*****************************************************************************
 * PROTOTYPES
 *****************************************************************************/

void coreCallSWI (registerstr *r);

/*****************************************************************************
 * ROUTINES
 *****************************************************************************/

/* -- eventIODeviceInit -------------------------------------------------------
 *
 * Description : initializes all internal device driver data structures.
 *               this routine should only be called once. Unless for some
 *               reason you need to reset all the device drivers.
 *
 * Parameters  : none....
 * Return      : none...
 * Notes       :
 * 
 *  This function is called in the core/cinit.c file
 *  
 *    eventIOdeviceInit();
 *
 */

void eventIODeviceInit(void)
{
registerstr tmpReg;

   tmpReg.r[0] = Event_IODeviceInit;
   tmpReg.r[1] = 0;
   tmpReg.r[2] = 0;
   tmpReg.r[3] = 0;
   
   coreCallSWI (&tmpReg);
   
   if (tmpReg.r[0]!=1 || tmpReg.r[1]!=2) { while(999);} 
}

/* -- eventIODeviceOpen -------------------------------------------------------
 *
 * Description : open a device driver
 *
 * Parameters  : UID * - address for UID
 *             : UINT - major device. For example, SERIAL
               : UINT - minor device. For exmaple, COM1
 * Return      : device_treestr * - pointer to device driver
 * Notes       :
 * 
 *   This function is used to open a COM1 of a SERIAL device.
 *   Example: 
 *
 *   handle = eventIODeviceOpen(&UID,SERIAL,COM1);
 *
 *   if (handle==DEVICE_UNKNOWN || handle==DEVICE_IN_USE)
 *   {
 *   canNotOpenDevice(); 
 *   }
 */

device_treestr *eventIODeviceOpen(UID *a, UINT b, UINT c)
{
registerstr tmpReg;

   tmpReg.r[0] = Event_IODeviceOpen;
   tmpReg.r[1] = (UINT) a;
   tmpReg.r[2] = b;
   tmpReg.r[3] = c;
	
  coreCallSWI(&tmpReg);

  return (device_treestr *)tmpReg.r[0];
}

/* -- eventIODeviceClose ------------------------------------------------------
 *
 * Description : close a device driver
 *
 * Parameters  : device_treestr * - pointer to device driver
 *             : UID - unique identifer
 * Return      : int
 * Notes       : 
 *
 *  This is used to close an open device
 *  Example: 
 *
 *    if (eventIODeviceClose(handle,id)!=DEVICE_SUCCESS)
 *    {
 *    couldNotCloseDevice();
 *    }
 */

int eventIODeviceClose(device_treestr *a, UID b)
{
registerstr tmpReg;

  tmpReg.r[0] = Event_IODeviceClose;
  tmpReg.r[1] = (UINT) a;
  tmpReg.r[2] = b;
  tmpReg.r[3] = 0;
	
  coreCallSWI(&tmpReg);

  return (int) tmpReg.r[0];
}

/* -- eventIOeviceWriteByte ---------------------------------------------------
 *
 * Description : write a byte to an open device
 *
 * Parameters  : device_treestr * - pointer to device driver
 *             : UID - unique identifier
 *             : UINT - byte store in the lower 8-bits
 * Return      : none...
 * Notes       :
 *
 *   This is used to write a byte to an open device 
 *   Example: eventIODeviceWriteByte(handle,id,c);
 */

void eventIODeviceWriteByte(UINT a,UINT b, UINT c) 
{
registerstr tmpReg;

  tmpReg.r[0] = Event_IODeviceWriteByte;
  tmpReg.r[1] = (UINT) a;
  tmpReg.r[2] = b;
  tmpReg.r[3] = c;
	
  coreCallSWI(&tmpReg);
}

/* -- eventIODeviceReadByte ---------------------------------------------------
 *
 * Description : read a byte from a device
 *
 * Parameters  : device_treestr * - pointer to device driver
 *             : UID - unique identifier
 * Return      : UINT - least significant 8-bits contain the byte
 * Notes       :
 * 
 *  This is used to read a byte from an open device
 *  Example: c = eventIODeviceReadByte(handle,id);
 */

UINT eventIODeviceReadByte(device_treestr *a, UID b) 
{
registerstr tmpReg;

  tmpReg.r[0] = Event_IODeviceReadByte;
  tmpReg.r[1] = (UINT) a;
  tmpReg.r[2] = b;
  tmpReg.r[3] = 0;
	
  coreCallSWI(&tmpReg);

  return (UINT) tmpReg.r[0];
}

/* -- eventIODeviceWriteBit ---------------------------------------------------
 *
 * Description : write a bit to a device
 *
 * Parameters  : device_treestr * - pointer to device driver
 *             : UID - unique identifier
 *             : UINT - byte store in the lower 1-bits 
 * Return      : none...
 * Notes       :
 * 
 *  This is used to write a bit to an open device
 *  Example: eventIOdeviceWriteBit(handle,id,bit);
 */

void eventIODeviceWriteBit(device_treestr *a, UID b, UINT c)
{
registerstr tmpReg;

  tmpReg.r[0] = Event_IODeviceWriteBit;
  tmpReg.r[1] = (UINT) a;
  tmpReg.r[2] = b;
  tmpReg.r[3] = c;
	
  coreCallSWI(&tmpReg);
}

/* -- eventIODeviceReadBit ----------------------------------------------------
 *
 * Description : read a bit from a device
 *
 * Parameters  : device_treestr * - pointer to device driver
 *             : UID - unique identifier
 * Return      : UINT - least significant bits contains the bit
 * Notes       :
 * 
 *  This is used to read a bit from an open device
 *  Example: bit = eventIODeviceReadBit(handle,id);
 */

UINT eventIODeviceReadBit(device_treestr *a, UID b) 
{
registerstr tmpReg;

  tmpReg.r[0] = Event_IODeviceReadBit;
  tmpReg.r[1] = (UINT) a;
  tmpReg.r[2] = b;
  tmpReg.r[3] = 0;
	
  coreCallSWI(&tmpReg);
  
  return (UINT) tmpReg.r[0];
}

/* -- eventIODeviceWriteBlock -------------------------------------------------
 *
 * Description : write a block to a device
 *
 * Parameters  : device_treestr * - pointer to device driver
 *             : UID - unique identifier
 *             : void * - point block to write to a device
 * Notes       :
 * 
 *  This is used to write a block to an open device
 *  Example: eventIODeviceWriteBlock(handle,id,&block);
 */

void eventIODeviceWriteBlock(device_treestr *a, UID b, void *c) 
{
registerstr tmpReg;

  tmpReg.r[0] = Event_IODeviceWriteBlock;
  tmpReg.r[1] = (UINT) a;
  tmpReg.r[2] = b;
  tmpReg.r[3] = (UINT) c;
	
  coreCallSWI(&tmpReg);
}

/* -- event_eventIODeviceReadBlock --------------------------------------------
 *
 * Description : read a block from a device
 *
 * Parameters  : device_treestr * - pointer to device driver
 *             : UID - unique identifier
 * Return      : void * - pointer to data block
 * Notes       :
 * 
 *  This is used to read a block from an open device
 *  Example: block = eventIODeviceReadBlock(handle,id);
 */

void *eventIODeviceReadBlock(device_treestr *a, UID b) 
{
registerstr tmpReg;

  tmpReg.r[0] = Event_IODeviceReadBlock;
  tmpReg.r[1] = (UINT) a;
  tmpReg.r[2] = b;
  tmpReg.r[3] = 0;
	
  coreCallSWI(&tmpReg);

  return (void *)tmpReg.r[0];
}

void bringUpTrace(UINT a, UID b)
{
registerstr tmpReg;

  tmpReg.r[0] = BringUp_Trace;
  tmpReg.r[1] = (UINT) a;
  tmpReg.r[2] = b;
  tmpReg.r[3] = 0;
	
  coreCallSWI(&tmpReg);
}

/* -- bringUpFatalError -------------------------------------------------------
 *
 * Description : very low level fatal error
 *
 * Parameters  : none...
 * Return      : none...
 * Notes       : when this SWI is called SLOS goes into an infinite 
 *               loop. It is designed for basic fatal loops. For PANIC
 *               problems.
 * 
 */

void bringUpFatalError(UID a)
{
registerstr tmpReg;

  tmpReg.r[0] = BringUp_FatalError;
  tmpReg.r[1] = (UINT) a;
  tmpReg.r[2] = 0;
  tmpReg.r[3] = 0;
  
  coreCallSWI(&tmpReg);
}

