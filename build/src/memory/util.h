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
 * Module       : util.h
 * Description  : memory utils
 * OS           : SLOS 0.03
 * Platform     : cm920iap
 * History      :
 *
 * 23rd July 2003 Andrew N. Sloss
 * - started
 *
 *****************************************************************************/

/*****************************************************************************
 * TYPES
 *****************************************************************************/

typedef unsigned int RT[10];

/*****************************************************************************
 * ROUTINES
 *****************************************************************************/

/* -- mmuInitSystem -----------------------------------------------------------
 * 
 * Description : initialize the system
 *
 * Parameter   : RT rt - region to be created
 * Return      : TRUE - always
 * Notes       :
 *
 */


int mmuInitSystem(void);

/* -- mmuInitTask -------------------------------------------------------------
 * 
 * Description : initialize a task
 *
 * Parameter   : RT rt - region to be created
 * Return      : TRUE - always
 * Notes       :
 *
 */


int mmuInitTask(RT rt);

/* -- mmuLoadTask -------------------------------------------------------------
 * 
 * Description : load a task
 *
 * Parameter   : RT rt - region to be created
 * Return      : TRUE - always
 * Notes       :
 *
 */
 
int mmuLoadTask(RT rt);

/* -- mmuCreatePT -------------------------------------------------------------
 * 
 * Description : create a page table
 *
 * Parameter   : RT rt - region to be created
 * Return      : TRUE - always
 * Notes       :
 *
 */
 
int mmuCreatePT(RT rt);

/* -- mmuAttachPT -------------------------------------------------------------
 * 
 * Description : attach a page table
 *
 * Parameter   : RT rt - region to be created
 * Return      : TRUE - always
 * Notes       :
 *
 */

int mmuAttachPT(RT rt);

/* -- mmuCreateRegion ---------------------------------------------------------
 * 
 * Description : Create a new region
 *
 * Parameter   : RT rt - region to be created
 * Return      : TRUE - always
 * Notes       :
 *
 */

int mmuCreateRegion(RT rt);

/* -- mmuLoadRegion -----------------------------------------------------------
 * 
 * Description : Load a region
 *
 * Parameter   : RT rt - region to be loaded
 * Return      : TRUE - always
 * Notes       :
 *
 */

int mmuLoadRegion(RT rt);

/* -- mmuInitTasks ------------------------------------------------------------
 * 
 * Description : Initialize the 3 tasks
 *
 * Parameter   : none...
 * Return      : none...
 * Notes       :
 *
 */

void mmuInitTasks(void);

/* -- mmuLoadTasks ------------------------------------------------------------
 * 
 * Description : Load 3 tasks
 *
 * Parameter   : none...
 * Return      : none...
 * Notes       :
 *
 */
 
void mmuLoadTasks(void);

/* -- mmuSchedule -------------------------------------------------------------
 * 
 * Description : schedules the a new task
 *
 * Parameter   : unsigned int tsk - 0 | 1 | 2
 * Return      : none...
 * Notes       :
 *
 */

void mmuSchedule (unsigned int tsk);
      
/* -- memoryMmuSystem ---------------------------------------------------------
 * 
 * Description : initializes the MMU on 920 core module.
 *
 * Parameter   : none...
 * Return      : none...
 * Notes       :
 *
 * added to replace the main.c in the original code
 *
 */

void memoryMmuSystem(void);

/*****************************************************************************
 * Assembler prototypes - mmu.s calls 
 *****************************************************************************/

extern int mmuSetTTB(unsigned int);
extern void mmuFlushTLB(void);
extern void mmuFlushCache(void);
extern int changeDomAccess(unsigned int, unsigned int);
extern int changeControl(unsigned int, unsigned int);

