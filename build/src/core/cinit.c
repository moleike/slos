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
 * Simple Little Operating System - mmuSLOS
 *****************************************************************************/

/*****************************************************************************
 *
 * Module       : cinit.c
 * Description  : initialize the command line and task1 
 * OS           : mmuSLOS 0.03
 * Platform     : cm920iap
 * History      :
 *
 * 10th November 2001 Andrew N. Sloss
 * - created
 *
 * 11th December 2001 Andrew N. Sloss
 * - updated the cinit with comments and new structure
 *
 * 4th July 2002 (USA Independence Day) Andrew N. Sloss
 * - added new application launch code.
 *
 * 26th July 2002 Andrew N. Sloss
 * - added MMU code.
 *
 *****************************************************************************/

/*****************************************************************************
 * IMPORTS
 *****************************************************************************/

#include "all.h"
#include "../cm920iap/events/events_init.h"
#include "../memory/util.h"

/*****************************************************************************
 * MACROS
 *****************************************************************************/

/* trace - note this should go into a separate file ... */

#define DEVICESINIT    1
#define SERVICESINIT   2
#define TICKINIT       3
#define CINITINIT      4
#define TICKSTART      5
#define MMUSETUP       6
#define ENTERTASK      7

#define LOW_LEVEL_INITIALIZATION 	1
#define BOOT_SLOS			2

/*****************************************************************************
 * DATATYPES
 *****************************************************************************/

/* n/a */

/*****************************************************************************
 * STATICS
 *****************************************************************************/

unsigned int STATE;

/*****************************************************************************
 * PROTOTYPE
 *****************************************************************************/

void switchOnSystem (void); /* final initialization .. */
	
/*****************************************************************************
 * ROUTINUES
 *****************************************************************************/

/* -- cinit_init --------------------------------------------------------------
 *
 * Description : The platform initialization code is placed here...
 *
 * Parameters  : none...
 * Return      : none...
 * Notes       : none...
 *		  
 */

void cinit_init (void)
{
STATE = LOW_LEVEL_INITIALIZATION;

 /* -------------------------------------------------------------------
  * Initialize all the device drivers
  * 
  * This routine has to be called before any of the device driver can 
  * be used. It complies with version 0.01 of the Wright Device Driver 
  * Framework (v0.01).
  *
  * ------------------------------------------------------------------- 
  */

lltrace(eventIODeviceInit(),DEVICESINIT);

 /* -------------------------------------------------------------------
  * 
  * Initialize all the unique services /kernel/events/cm920iap/init.h
  * In SLOS Services are devices that cause interrupts.
  *
  * ------------------------------------------------------------------- 
  */

lltrace(eventServicesInit(),SERVICESINIT);

 /* -------------------------------------------------------------------
  * 
  * Initialize the timer to interrupt every 2 milliseconds
  * 
  * ------------------------------------------------------------------- 
  */
 
lltrace(eventTickInit(2),TICKINIT);
}
	
/* -- C_Entry -----------------------------------------------------------------
 *
 * Description : This is the entry point...
 * 
 * Parameters  : none...
 * Return      : return 1 if successful
 * Notes       : none...
 *
 */

int C_Entry ( void )
{
 /* --------------------------------------------------------------------
  * 
  * Initalize all the internal data structures for device drivers and
  * services. 
  *
  * Terminology:
  *
  *  - services are called by interrupt... 
  *  - device drivers are called by applications
  *
  * -------------------------------------------------------------------
  */

lltrace(cinit_init(),CINITINIT);

 /* -------------------------------------------------------------------
  *
  * Start the periodic timer. This will not effect the system until 
  * IRQ or FIQ interrupts are enabled.
  * 
  * -------------------------------------------------------------------
  */

lltrace(eventTickStart(),TICKSTART);

 /* -------------------------------------------------------------------
  *
  * Initialize a start state for the MMU memory regions.
  * 
  * -------------------------------------------------------------------
  */

lltrace(memoryMmuSystem(),MMUSETUP);

 /* -------------------------------------------------------------------
  *
  * Enter into Application/Task1 
  * 
  * -------------------------------------------------------------------
  */

STATE=BOOT_SLOS;

lltrace(switchOnSystem(),ENTERTASK); 

 /* -------------------------------------------------------------------
  *
  * THIS CODE SHOULD NEVER BE REACHED 
  *
  * -------------------------------------------------------------------
  */
 
return 0;
}

