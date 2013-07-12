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
 * Simple Little Operating System - mpuSLOS
 *****************************************************************************/

/******************************************************************************
 *
 * Module       : startx.c
 * Description  : A task routine that toggles LED2
 * Platform     : Integrator/AP
 * History      :
 *
 * 2000-03-27 Andrew N. Sloss
 * - ported to Evaluator-7T
 * - added header and changed the delay time
 * 
 * 2002-06-17 Andrew N. Sloss
 * - simplified the code (removed MUTEX)
 *
 * July 15th 2002 Andrew N. Sloss
 * - removed direct communication with the hardware  
 *
 *****************************************************************************/

/*****************************************************************************
 * IMPORT
 *****************************************************************************/

#include "led.h"

/*****************************************************************************
 * MACROS
 *****************************************************************************/
 
/* none... */
 
/*****************************************************************************
 * DATATYPES
 *****************************************************************************/

/* none... */

/*****************************************************************************
 * ROUTINES
 *****************************************************************************/

/* -- _start -----------------------------------------------------------------
 *
 * Description : Entry into task1 
 * 
 * Parameters  : none...
 * Return      : none...
 * Notes       :
 *
 * This task executes continuously
 *
 */

void entry (void)
{
volatile int delay;

  if (openRedLED ()==0)
  {

    while (1) 
    {
    switchOnRedLED ();

    /* dummy time delay... */
    for (delay=0; delay<0x40ffff; delay++) {} 
  
    switchOffRedLED ();
	
    /* dummy time delay... */
    for (delay=0; delay<0x40ffff; delay++) {} 
    }
  }

  /* 
   * error loop
   */

  while (1) 
  {
  delay=0xBEEFBEEF;
  };
}




