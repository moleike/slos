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
 * Module      : start.c
 * Description : simple task to call the command line.
 * OS          : mpuSLOS 0.03	
 * Platform	: cm940iap
 * History     :
 *
 * November 5th 2001 - Andrew N. Sloss
 * - created a simple command line calling task.
 *
 *****************************************************************************/

/*****************************************************************************
 * DATATYPE
 *****************************************************************************/

/* none... */

/*****************************************************************************
 * IMPORT
 *****************************************************************************/

#include "types.h"
#include "serial.h"
#include "shell.h"

/**************************************************************
 * MACROS
 **************************************************************/

#define COM1 (1)
#define COM0 (0)

/**************************************************************
 * PROTOTYPE
 **************************************************************/

void banner (void); 

/**************************************************************
 * GLOBAL
 **************************************************************/

/**************************************************************
 * ROUTINES
 **************************************************************/

/* -- entry ----------------------------------------------------------
 *
 * Description	: entry point into task 3
 * 
 * Parameters	: none...
 * Return	    : none...
 * Notes        :
 *
 *	    This routine never terminates
 *
 */

void entry(void) 
{

 /* -----------------------------------------------------------
  *
  * Open file stream
  *
  *
  * -----------------------------------------------------------
  */

 if(openHost (COM0)==TRUE)
 {
 banner ();
 shell  ();
 }

/* -----------------------------------------------------------
 *
 * The closing the HostPort should *never* occur
 *
 * -----------------------------------------------------------
 */

closeHost ();
}

