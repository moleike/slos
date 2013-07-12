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
 * Module        : com.c
 * Description   : provides com functions. This file is only
 *                 brought in if a command line is required
 * OS            : SLOS 0.09
 * Platform      : cm940iap
 * History       :
 *
 * 17th November 2001 Andrew N. Sloss
 * - added replacement to make file a template
 *
 *****************************************************************************/

/*****************************************************************************
 * IMPORT
 *****************************************************************************/

#include <stdarg.h>

#include "../../core/all.h"
#include "serial.h"

/*****************************************************************************
 * STATICS
 *****************************************************************************/

char command_line[256];
char *report_buff;
char gpbuff[256];
char *error_buff;

/*****************************************************************************
 * ROUTINES
 *****************************************************************************/

/* Initialize both ports to 9600 baud */

void formatString(const char *fmt, void (*putc)(int), va_list args);

/* -- writeC ------------------------------------------------------------------
 *
 * Description : writes a character to the host 
 *
 * Parameters  : int c
 * Return      : none...
 * Notes       : 
 *
 */

void writeC(int c) 
{
writeCharToHost((char)c);
}

/* -- readC -------------------------------------------------------------------
 *
 * Description : read a character from the host
 *
 * Parameters  : none...
 * Return      : int - character
 * Notes       : none...
 *
 */

int readC(void) 
{
return (int)readCharFromHost();
}

/* -- reportC -----------------------------------------------------------------
 *
 * Description : set the report buffer to c and increment the buffer.
 *
 * Parameters  : int c - character to be inserted into the buffer
 * Return      : none...
 * Notes       : none...
 *
 */

void reportC(int c) 
{
*report_buff++ = c;
}

/* -- internal_write_dec ------------------------------------------------------
 *
 * Description : writes out the value in decimal
 *
 * Parameters  : none...
 * Return      : none...
 * Notes       : none...
 *
 */

void internal_write_dec(unsigned w, void (*putc)(int)) 
{
  if (w >= 10) internal_write_dec(w / 10, putc);
    putc(w % 10 + '0');
}

/* -- digits ------------------------------------------------------------------
 *
 * Description : hexidecimal digits
 *
 */

const char digits[] = "0123456789abcdef";

/* -- internal_write_hex ------------------------------------------------------
 *
 * Description : write the output in hexadecimal
 *
 * Parameters  : unsigned w
 *               putc address
 * Return      : none...
 * Other       : none...
 *
 */

void internal_write_hex(unsigned w, void (*putc)(int)) 
{
int i;
 
  for (i = 0; i < 8; i++) 
  {
  putc(digits[w >> 28]);
  w <<= 4;
  }
}

/* -- write0 ------------------------------------------------------------------
 *
 * Description : write a string to the host port 
 *
 * Parameters  : char *s - string to be written
 * Return      : none...
 * Notes       : none...
 *
 */

void write0(char *s) 
{
int c;

c = *s++;

  while (c) 
  {
  writeC(c);
  c = *s++;
  }
}

/* -- newLine -----------------------------------------------------------------
 *
 * Description : send a newline to the host port
 *
 * Parameters  : none...
 * Return      : none...
 * Notes       : none...
 *
 */

void newLine(void) 
{
writeC('\r');
writeC('\n');
}

/* -- writeHex ----------------------------------------------------------------
 *
 * Description : take and unsigned int and convert it to hexadecimal
 *
 * Parameters  : unsigned w
 * Return      : none...
 * Notes       : none...
 *
 */

void writeHex(unsigned w) 
{
internal_write_hex(w, writeC);
}

/* -- writeDec ----------------------------------------------------------------
 *
 * Description : write a decimal to the host port
 *
 * Parameters  : none...
 * Return      : none...
 * Notes       : none...
 *
 */

void writeDec(unsigned w) 
{
internal_write_dec(w, writeC);
}

/* -- prettyC -----------------------------------------------------------------
 *
 * Description : prettyC
 *
 * Parameters  : int c - character
 * Return      : none...
 * Notes       : none...
 *
 */

void prettyC(int c) 
{
static int n;

  if (c == '\t') 
  {
    do 
    {
    writeC(' ');
    } while (++n & 7);
  return;
  }

  if (c == '\n') 
  {
  n = 0;
  writeC('\r');
  }

  if (c >= 0x20) n++; writeC(c);
}

/* -- prettyPrint -------------------------------------------------------------
 *
 * Description : PrettyPrint 
 *
 * Parameters  : format fmt
 * Return      : none...
 * Notes       : none...
 *
 */

void prettyPrint(const char *fmt, ...) 
{
va_list ap;

va_start(ap, fmt);
formatString(fmt, prettyC, ap);
prettyC('\n');
va_end(ap);
}

/* -- formatString ------------------------------------------------------------
 *
 * Description : format_string
 *
 * Parameters  : const char *fmt - format string
 *             : void (*putc)(int) - function pointer
 *             : va_list - variable list
 * Return      : none...
 * Notes       : none...
 *
 */

void formatString(const char *fmt, void (*putc)(int), va_list args) 
{
int c;

c = *fmt++;

  while (c) 
  {
    if (c != '%') 
    {
    putc(c);
    continue;
    }

  c = *fmt++;

    switch (c) 
    {
    case 'd': internal_write_dec(va_arg(args, unsigned), putc); break;
    case 'x': internal_write_hex(va_arg(args, unsigned), putc); break;
    case 's': 
    {
    int max_string = sizeof( command_line );
    char *s = va_arg(args, char *);

    c = *s++;

      while ( c && (max_string-- > 0)) 
      {
	 putc(c); 
	 c=*s++;
	 }

    break;
    }
    case 0:
    /* backup */
    fmt--;
    break;
    default:
    putc(c);
    break;
    }
  c = *fmt++;
  }
}

/* -- handleReportedError -----------------------------------------------------
 *
 * Description : HandleReportedError
 *
 * Parameters  : none...
 * Return      : CallBack
 * Notes       : none...
 *
 */

CallBack handleReportedError(void) 
{
return 0;
}

/* -- reportOK ----------------------------------------------------------------
 *
 * Description : reportOK
 *
 * Parameters  : none...
 * Return      : CallBack
 * Notes       : none...
 *
 */

CallBack reportOK(void) 
{
return 0;
}

/* -- reportError -------------------------------------------------------------
 *
 * Description : report error
 *
 * Parameters  : unsigned errno - error number
 *             : const char *fmt - format string
 * Return      : CallBack
 * Notes       : none...
 *
 */

CallBack reportError(unsigned errno, const char *fmt, ...) 
{
va_list ap;

va_start(ap, fmt);
report_buff = gpbuff;
*(unsigned *)report_buff = errno;
report_buff += 4;
formatString(fmt, reportC, ap);
reportC(0);
va_end(ap);
error_buff = gpbuff;
return handleReportedError();
}

/* -- CLI ---------------------------------------------------------------------
 *
 * Description : processes the instruction command line
 *
 * Parameters  : char *cmd
 * Return      : CallBack - always ReportOK
 * Notes       :
 *
 */

CallBack CLI(char *cmd) 
{

/*
  while (*cmd == ' ') cmd++;
    if (!*cmd) return reportOK();
*/
return reportOK();
}

