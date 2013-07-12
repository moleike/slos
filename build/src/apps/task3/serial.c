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
 * Module      : serial.c
 * Description : Provides serial API functions. 
 * OS          : mpuSLOS
 * Platform    : cm940iap
 * History     :
 *
 * 1st June 2002 Andrew N. Sloss
 * - added header information
 *
 *****************************************************************************/

/*****************************************************************************
 * IMPORT
 *****************************************************************************/

#include "types.h"
#include "../../devices/ddf_io.h"
#include "../../devices/ddf_types.h"

#include "swis.h"
#include "../../headers/api_device.h"

/*****************************************************************************
 * STATICS
 *****************************************************************************/

device_treestr *host;
UID	       serial;

/*****************************************************************************
 * ROUTINES
 *****************************************************************************/

/* -- openHostPort ------------------------------------------------------------
 *
 * Description   : opens the communication port for the host
 *                 command line.
 *
 * Parameters    : UINT COM
 * Return        : BOOLean 0 
 * Notes         :
 *
 */

BOOL openHost (UINT com) 
{ 
/* --------------------------------------------------------------
 *
 * eventIODeviceOpen - 
 *
 * open the serial driver node...
 * 
 * --------------------------------------------------------------
 */

  if (com>1) {return FALSE;}

host = eventIODeviceOpen(&serial,DEVICE_SERIAL_CM920IAP,com);

  /* check that a device driver is found ... */

  if (host==0) {return FALSE;}

  /* check the UID .................. */

  switch (serial) 
  {
  case DEVICE_IN_USE:
  case DEVICE_UNKNOWN:

	return FALSE;
  } 
  	
return TRUE; 
}

/* -- writeCharToHost ---------------------------------------------------------
 *
 * Description  : write a character to host port
 *
 * Parameter    : char c - character to be sent to host port
 * Return       : none...
 * Notes	:
 *
 */

void writeCharToHost (char c)
{eventIODeviceWriteByte(host,serial,(UINT)c);}

/* -- writeCharToHost ---------------------------------------------------------
 *
 * Description  : write a character to host port
 *
 * Parameter    : char c - character to be sent to host port
 * Return       : none...
 * Notes	:
 *
 */

void printToHost (char *s)
{
  while (*s!=0)
  {
  writeCharToHost (*s++);
  }
}

/* -- readCharFromHostPort ----------------------------------------------------
 *
 * Description  : read a character from host port
 *
 * Parameter    : none...
 * Return       : char c - character to be sent to host port
 * Notes	:
 *
 */

char readCharFromHost (void)
{return (char)eventIODeviceReadByte(host,serial);}

/* -- closeHostPort -----------------------------------------------------------
 *
 * Description  : closes the host port but this code should never be 
 *                executed.
 *
 * Parameter    : none...
 * Return       : char c - character to be sent to host port
 * Notes	:
 *
 */

int closeHost (void)
{
  if (host==0) return FALSE;

return eventIODeviceClose(host,serial);
}

/* -- banner ------------------------------------------------------------------
 *
 * Description	: prints out on the serial the SLOS banner.
 * 
 * Parameters	: none...
 * Return	    : none...
 * Notes        :
 *
 *	    this uses the printToHost function of the CLI.
 */

void banner (void) 
{
printToHost ("\n\r");
printToHost ("\n\rSimple Little OS - mmuSLOS (0.03)\n\r");
printToHost ("- initialized ...... ok\n\r");
printToHost ("- running on ....... cm920iap \n\r");
printToHost ("- simple shell ..... active\n\r");
printToHost ("\n\r");
printToHost ("\n\r");
}

