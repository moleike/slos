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
 *	Module        : com.h
 * 	Descriptions  : Provides serial API functions. 
 *	OS            : SLOS
 *	Platform      : cm940iap
 *	History       :
 *
 *	1st June 2002 Andrew N. Sloss
 *      - added header information
 *
 *****************************************************************************/

/*****************************************************************************
 * EXTERNAL
 *****************************************************************************/

extern char command_line[256];

/*****************************************************************************
 * ROUTINES
 *****************************************************************************/

/* -- writeC ------------------------------------------------------------------
 *
 * Description : writes a character to the host 
 *
 * Parameters  : int c
 * Return      : none...
 * Notes       : 
 *
 */

void writeC(int c);

/* -- readC -------------------------------------------------------------------
 *
 * Description : read a character from the host
 *
 * Parameters  : none...
 * Return      : int - character
 * Notes       : none...
 *
 */

int readC(void);

/* -- reportC -----------------------------------------------------------------
 *
 * Description : set the report buffer to c and increment the buffer.
 *
 * Parameters  : int c - character to be inserted into the buffer
 * Return      : none...
 * Notes       : none...
 *
 */

void reportC(int c);

/* -- write0 ------------------------------------------------------------------
 *
 * Description : write a string to the host port 
 *
 * Parameters  : char *s - string to be written
 * Return      : none...
 * Notes       : none...
 *
 */

void write0(char *s);

/* -- newLine -----------------------------------------------------------------
 *
 * Description : send a newline to the host port
 *
 * Parameters  : none...
 * Return      : none...
 * Notes       : none...
 *
 */

void newLine(void);

/* -- writeHex ----------------------------------------------------------------
 *
 * Description : take and unsigned int and convert it to hexadecimal
 *
 * Parameters  : unsigned w
 * Return      : none...
 * Notes       : none...
 *
 */

void writeHex(unsigned w);

/* -- writeDec ----------------------------------------------------------------
 *
 * Description : write a decimal to the host port
 *
 * Parameters  : none...
 * Return      : none...
 * Notes       : none...
 *
 */

void writeDec(unsigned w);

/* -- prettyC -----------------------------------------------------------------
 *
 * Description : prettyC
 *
 * Parameters  : int c - character
 * Return      : none...
 * Notes       : none...
 *
 */

void prettyC(int c);

/* -- prettyPrint -------------------------------------------------------------
 *
 * Description : PrettyPrint 
 *
 * Parameters  : format fmt
 * Return      : none...
 * Notes       : none...
 *
 */

void prettyPrint(const char *fmt, ...);

/* -- handleReportedError -----------------------------------------------------
 *
 * Description : HandleReportedError
 *
 * Parameters  : none...
 * Return      : CallBack
 * Notes       : none...
 *
 */

CallBack handleReportedError(void);

/* -- reportOK ----------------------------------------------------------------
 *
 * Description : reportOK
 *
 * Parameters  : none...
 * Return      : CallBack
 * Notes       : none...
 *
 */

CallBack reportOK(void);

/* -- reportError -------------------------------------------------------------
 *
 * Description : ReportError
 *
 * Parameters  : unsigned errno - error number
 *             : const char *fmt - format string
 * Return      : CallBack
 * Notes       : none...
 *
 */

CallBack reportError(unsigned errno, const char *fmt, ...);

/* -- CLI ---------------------------------------------------------------------
 *
 * Description : processes the instruction command line
 *
 * Parameters  : char *cmd
 * Return      : CallBack - always ReportOK
 * Notes       :
 *
 */

CallBack CLI(char *cmd);

