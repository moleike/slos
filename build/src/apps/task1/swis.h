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
 * Module      : swis.h
 * Description : this file contain the various system calls swi numbers
 *               they all operate through the SLOS SWI entry 5507
 * OS          : SLOS 0.03
 * Platform    : generic
 * History     :
 *
 * December 7th 2001 Andrew N. Sloss
 * - start creating a SWI interface to SLOS system calls
 * 
 * Note         :
 *
 *  May need to move this in to a generic header sometime.
 *
 *****************************************************************************/
 
/*****************************************************************************
 * MACROS
 *****************************************************************************/

#ifndef SLOS

/* ------------------------------------------------------------
 * SWI: SLOS (5075)
 * ------------------------------------------------------------
 */

#define SLOS 	5075

/* ------------------------------------------------------------ 
 * Device Driver SWI SLOS 
 * ------------------------------------------------------------ */

#define Event_IODeviceInit         0x800
#define Event_IODeviceOpen         Event_IODeviceInit+1
#define Event_IODeviceClose        Event_IODeviceInit+2
#define Event_IODeviceWriteByte    Event_IODeviceInit+3
#define Event_IODeviceReadByte     Event_IODeviceInit+4	
#define Event_IODeviceWriteBit     Event_IODeviceInit+5
#define Event_IODeviceReadBit      Event_IODeviceInit+6	
#define Event_IODeviceWriteBlock   Event_IODeviceInit+7
#define Event_IODeviceReadBlock    Event_IODeviceInit+8

/* ------------------------------------------------------------ 
 * Bring up SWI's
 * ------------------------------------------------------------ */

#define BringUp_Base          0x700
#define BringUp_Trace         BringUp_Base
#define BringUp_FatalError    BringUp_Base+1

/* ------------------------------------------------------------ 
 * SWI Register Structure
 * ------------------------------------------------------------ */

typedef struct SwiRegs 
{
unsigned r[13];     /* R0 - R12 */
unsigned cpsr;      /* spsr on entry to SWI */
unsigned pc;        /* lr on entry to SWI */
} SwiRegs;

#endif

