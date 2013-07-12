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
 * Module        : readline.c
 * Descriptions  : provides all readline functions
 * OS            : SLOS 0.03
 * Platform      : cm940iap
 * History       :
 *
 * 16th November 2001 Andrew N. Sloss
 * - start adding comments
 *
 *****************************************************************************/

/*****************************************************************************
 * IMPORT
 *****************************************************************************/

#include <string.h>

#include "types.h"
#include "com.h"
#include "readline.h"

#define START       ('A'-'@')
#define BACK        ('B'-'@')
#define ERASE_FWD   ('D'-'@')
#define END         ('E'-'@')
#define FORWARD     ('F'-'@')
#define ERASE       ('H'-'@')
#define ERASE_EOL   ('K'-'@')
#define ENTER       ('M'-'@')
#define REDRAW      ('R'-'@')
#define ERASE_LINE  ('U'-'@')
#define ERASE_SOL   ('W'-'@')

#define BACKSPACE   ('H'-'@')
#define DELETE      (0x7f)
#define LF          ('\n')
#define CR          ('\r')
#define CTRL_D      ('D'-'@')

int readC(void);
void writeC(int c);

/*****************************************************************************
 * ROUTINES
 *****************************************************************************/

int xstrlen (char *p)
{
  int n=0;

  while (*p++!=0) n++;

  return (n);
}

void xstrcpy (char *s, char *t)
{
    while ((*s++ = *t++))
	;
}

void xmemmove(char *s, char *t,int n)
{
    while (n--) *s++ = *t++;
}


/* -- backspace ---------------------------------------------------------------
 *
 * Description  : send a backspace to the host port
 *
 * Parameters   : int n - number of backspaces
 * Return       : none...
 * Others       : none...
 *
 */

static void backspace (int n) 
{
  while (n--) writeC(BACKSPACE);
}

/* -- backup ------------------------------------------------------------------
 *
 * Description  : clear all the characters up to a position
 *
 * Parameters   : char *buffer - the buffer 
 *              : int pos - position in the buffer
 * Return       : none...
 * Others       : none...
 *
 */

static void backup(char *buffer, int pos) 
{
backspace(xstrlen(&buffer[pos]));
}

/* -- redraw_eol --------------------------------------------------------------
 *
 * Description  : redraw the line upto the end-of-line marker.
 *
 * Parameters   : char *buffer - the buffer 
 *              : int pos - position in the buffer
 * Return       : none...
 * Others       : none...
 *
 */

static void redraw_eol (char *buffer, int pos) 
{
int c;

c = buffer[pos++];

  while (c) 
  {
  writeC(c);
  c = buffer[pos++];
  }
}

/* -- redraw_line -------------------------------------------------------------
 *
 * Description  : redraw the complete line
 *
 * Parameters   : char *prompt - line prompt
 *              : char *buffer - the buffer 
 *              : int pos - position in the buffer
 * Return       : none...
 * Others       : none...
 *
 */

static void redraw_line(char *prompt, char *buffer, int pos) 
{
int c;

writeC(CR);

c = *prompt++;
	
  while (c) 
  {
  writeC(c);
  c = *prompt++;
  }	

redraw_eol(buffer, 0);
backup(buffer, pos);
}

/* -- delete ------------------------------------------------------------------
 *
 * Description	: delete and backup the line
 *
 * Parameters	: char *buffer - the buffer 
 *		: int pos - position in the buffer
 * Return	: none...
 * Others	: none...
 *
 */

static void delete (char *buffer, int pos)
{
  if (buffer[pos] == 0) return;

xstrcpy(&buffer[pos], &buffer[pos+1]);
redraw_eol(buffer, pos);
writeC(' ');
writeC(BACKSPACE);
backup(buffer, pos);

return;
}

/* -- insert ------------------------------------------------------------------
 *
 * Description : insert a character into the buffer
 *
 * Parameters  : char *buffer - the buffer 
 *             : int pos - position in the buffer
 *             : int c - character to be inserted
 * Return	     : none...
 * Notes	     : none...
 *
 */

static int insert (char *buffer, int pos, int c) 
{
char *s = &buffer[pos];

xmemmove(s+1, s, xstrlen(s)+1);
buffer[pos] = c;
redraw_eol(buffer, pos);
pos++;
backup(buffer, pos);

return pos;
}

/* -- ReadLineZ ---------------------------------------------------------------
 *
 * Description : ReadLineZ
 *
 * Parameters  : char *buffer - the buffer 
 *             : int maxlen - maximum length
 * Return      : integer of position
 * Notes       : none...
 *
 */

int ReadLineZ (char *buffer,int maxlen) 
{
int pos = 0;
int c;

  do 
  {
  c=readC();
	
    if (c == CR || c == LF) 
    {
    buffer[pos] = 0;
    return pos;
    }
	
    if (c == CTRL_D) 
    {
    buffer[0] = 0;
    return -1;
    }
	
    if (c >= ' ' && pos < maxlen)
	    buffer[pos++] = c;
  } while (1);
}

/* -- readLine ----------------------------------------------------------------
 *
 * Description : clear all the characters up to a position. This is the
 *               main interpreter loop for the command line.
 *
 * Parameters  : char *prompt - command line prompt.
 *             : char *buffer - the buffer 
 *             : int maxlen - maximum length
 * Return      : integer position
 * Notes       : none...
 *
 */

int readLine (char *prompt, char *buffer, int maxlen) 
{
int i;
int pos = 0;
int c;

*buffer = 0;
write0(prompt);

  do 
  {
  c = readC();
    if (c == DELETE) c = ERASE;
    if (c < ' ') 
    {
      switch (c) 
      {
      case START:
      backspace(pos);
      pos = 0;
      break;
      case BACK:
        if (pos > 0) 
        {
        writeC(BACKSPACE);
        pos--;
        }
      break;
      case ERASE_FWD:
        if (xstrlen(buffer) == 0) 
        {
        write0("*EOF*\r\n");
        return -1;
        }
      delete(buffer, pos);
      break;
      case END:
      redraw_eol(buffer, pos);
      pos = xstrlen(buffer);
      break;
      case FORWARD:
        if (buffer[pos]) 
        {
        writeC(buffer[pos]);
        pos++;
        }
      break;
      case ERASE:
        if (pos > 0) 
        {
        writeC(BACKSPACE);
        pos--;
        delete(buffer, pos);
        }
      break;
      case ENTER:
      writeC(CR);
      writeC(LF);
      return xstrlen(buffer);
      case REDRAW:
      writeC(LF);
      redraw_line(prompt, buffer, pos);
      break;
      case ERASE_LINE:
      backspace(pos);
      i = pos = xstrlen(buffer);

        while (i--) writeC(' ');
		    
      backspace(pos);
      pos = 0;
      buffer[0] = 0;
      break;
      }
    } else if (xstrlen(buffer) < maxlen)
          pos = insert(buffer, pos, c);
  } while (1);
}

