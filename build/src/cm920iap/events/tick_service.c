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
/***********************************************************************
 * Simple Little Operating System
 ***********************************************************************/

/***********************************************************************
 *
 * Module       : Service
 * Description  : Service for a TICK event
 * Status       : complete
 * Platform     : Integrator/AP
 * History      : 
 *
 * 30th April 2002 Andrew N. Sloss
 * - corrected the header information and started converting to
 * Integrator/AP.
 *
 ************************************************************************/

/************************************************************************
 * IMPORT
 ************************************************************************/

#include "../headers/led.h"
#include "../headers/macros.h"

#include "../../headers/api_types.h"

/************************************************************************
 * MACRO'S
 ************************************************************************/

#define OneMilliSecond   93750000
#define Irq0             0x14000000
#define Int_EnableSet    2

/************************************************************************
 * GLOBAL
 ************************************************************************/

/************************************************************************
 * EXTERN's
 ************************************************************************/

// none...

/************************************************************************
 * GLOBALS
 ************************************************************************/

static int led_pulse = 0;
static UINT rate;

/************************************************************************
 * ROUTINES
 ************************************************************************/

/* -- eventTickInit ------------------------------------------------------
 *                                                            
 * Description : Initialises the counter timer and sets the timer divisor.      
 *
 * Parameters  : none...   
 * Return      : none...
 * Notes       : none...
 *                                                                             
 */

void eventTickInit (UINT msec)
{
volatile int *TIMER = (int *) Timer2;

/* ---------------------------------------------------
 *
 * Setup the rate. If not 2 then 24 milliseconds...
 *
 * -------------------------------------------------- */

  switch (msec)
  {
  case 2: /* fast ... */
  rate = 2;
  break;
	
  default: /* slow ... */
  rate = 24;
  break;	
  }

/* ---------------------------------------------------
 *
 * Clear Timer and Load the rate
 *
 * -------------------------------------------------- */

*(TIMER + Timer_Clear) = 0;
*(TIMER + Timer_Load) = OneMilliSecond * rate;
*(TIMER + Timer_Control) = TimerEnable | TimerPrescale256 | TimerPeriodic;
}

/* -- eventTimerISR -----------------------------------------------------------
 *
 * Description : interrupt service routine for timer0 interrupt.
 *
 * Parameters  : none...
 * Return      : none...
 * Notes       : Integrator Timer
 *
 */ 

void eventTimerISR (void) 
{ 
volatile int *TIMER = (int *) Timer2;

/* ---------------------------------------------------
 *
 * Toggle LED
 *
 * -------------------------------------------------- */
   
   PAUSE;
   if ( led_pulse ) 
	{ LED_1_ON; led_pulse = 0; }
   else 
	{ LED_1_OFF; led_pulse = 1; }
	

/* ---------------------------------------------------
 *
 * Reset Timer
 *
 * -------------------------------------------------- */

*(TIMER + Timer_Clear) = 0;
*(TIMER + Timer_Load) = OneMilliSecond * rate; 
*(TIMER + Timer_Control) = TimerEnable | TimerPrescale256 | TimerPeriodic;
} 

void eventsTickCM920IAPService(void) 
{
eventTimerISR ();
}

/* -- eventTickStart -----------------------------------------------------------
 *
 * Description : switches the timer on
 *
 * Parameters  : none...
 * Return      : none...
 * Notes       : none...
 *
 */  

void eventTickStart (void)
{
volatile unsigned int * IRQ = (unsigned int  *)Irq0;  /* default to Interrupt 0 */
*(IRQ + Int_EnableSet) =  0x80; /* set interrupt n */ 
}

/*******************************************************************************
 * END OF service.c
 *******************************************************************************/
