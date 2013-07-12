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
 * Simple Little Operating System - SLOS 
 ***********************************************************************/

/***********************************************************************
 *
 * Module       : led.h
 * Description  : LED headers
 * OS           : SLOS
 * Platform     : cm940iap
 * History      : 
 *
 * 16th November 2001 Andrew N. Sloss
 * - added a led.h header  
 *
 ***********************************************************************/

/***********************************************************************
 * IMPORTS
 ***********************************************************************/

/* none... */

/***********************************************************************
 * MACROS
 ***********************************************************************/

/* LED's .................................... */

// -- base register
#define LEDBANK		(volatile unsigned int *)0x1a000004		

// -- set

/* ____________________________________________________

   LED Table
 
   GREEN  = 4 
   YELLOW = 3
   RED    = 2
   GREEN2 = 1
   ____________________________________________________

 */

#define LED_4_ON	(*LEDBANK=*LEDBANK|0x00000001)
#define LED_3_ON	(*LEDBANK=*LEDBANK|0x00000002)
#define LED_2_ON	(*LEDBANK=*LEDBANK|0x00000004)
#define LED_1_ON	(*LEDBANK=*LEDBANK|0x00000008)
#define LED_ALL_ON	(*LEDBANK=*LEDBANK|0x0000000f)

// -- reset 

#define LED_4_OFF   (*LEDBANK=*LEDBANK&~0x00000001)
#define LED_3_OFF	(*LEDBANK=*LEDBANK&~0x00000002)
#define LED_2_OFF	(*LEDBANK=*LEDBANK&~0x00000004)
#define LED_1_OFF	(*LEDBANK=*LEDBANK&~0x00000008)
#define LED_ALL_OFF	(*LEDBANK=*LEDBANK&~0x0000000f)

#define PAUSE while (*(volatile unsigned int *)0x1A000000 & 1)

/**********************************************************************
 * DATATYPES
 **********************************************************************/

/* none... */

/**********************************************************************
 * STATICS
 **********************************************************************/

/* none... */

/**********************************************************************
 * ROUTINES
 **********************************************************************/

/* none... */

/**********************************************************************
 * END OF led.h
 **********************************************************************/
