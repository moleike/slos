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
 * Module       : util.c
 * Description  : privide the MMU interface 
 * OS           : mmuSLOS
 * Platform     : cm920iap
 * History      :
 *
 * 9th August 2002 Andrew N. Sloss
 * - taken from Chris Wright's original code
 *
 *****************************************************************************/

/*****************************************************************************
 * IMPORT
 *****************************************************************************/

#include "regions.h"
#include "util.h"

/*****************************************************************************
 * PROTOTYPES
 *****************************************************************************/

void printStatus(void);
int mmuInitSystem(void);
void mmuInitTasks(void);
int mmuInitTask(RT);
int mmuCreateRegion(RT);
int mmuCreatePT(RT);
int mmuAttachPT(RT);
int mmuLoadTask(RT);
int mmuLoadRegion(RT);

extern RT MmuPCB_RegionTable1;
extern RT MmuPCB_RegionTable2;
extern RT MmuPCB_RegionTable3;

/*****************************************************************************
 * STATICS
 *****************************************************************************/
 
/* -- RT ----------------------------------------------------------------------
 *
 * Structure   : Region table
 * Details     :
 *
 *  RT variable =
 *  {
 *  REGION,
 *  VA,
 *  SIZE,
 *  AP,
 *  CB,
 *  ENABLE,
 *  PTA,    
 *  TYPE,
 *  DOM,
 *  PA,
 *  LA
 *  };
 *
 */

RT rtFault =
{
  0x00000000,
  4096,
  rwxrwx,
  ccb, 
  DORMANT,
  TTB,
  SECTION,
  D00,
  0x00000000,
  0x00000000
};

/* System Regions */

RT rtPeriph =
{
  0x10000000,
  256, 
  RWXrwx, 
  ccb, 
  ACTIVE, 
  TTB,
  SECTION,
  D15,
  0x10000000,
  0x10000000
};

RT rtPT =
{
  0x00040000,
  16, 
  RWXrwx, 
  ccb, 
  ACTIVE, 
  PT(SYSTEM),
  COARSE, 
  D15,
  0x00038000,
  0x00038000
};

RT rtLoad =
{
  0x00020000,
  32, 
  RWXRWX, 
  ccb, 
  ACTIVE, 
  PT(SYSTEM),
  COARSE, 
  D15,
  0x00020000,
  0x00020000
};

RT rtShared =
{
  0x00010000,
  16, 
  RWXRWX, 
  CWT, 
  ACTIVE, 
  PT(SYSTEM),
  COARSE, 
  D15,
  0x00010000,
  0x00010000
};

RT rtKernel =
{
  0x00000000,
  16, 
  RWXrwx, 
  CWT, 
  ACTIVE, 
  PT(SYSTEM),
  COARSE, 
  D15,
  0x00000000,
  0x00000000
};

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


int mmuInitSystem(void)
{

/* create L1 PageTable filled with FAULT descriptors */
mmuCreatePT(rtFault);      

/* create L2 Pagetable filled with FAULT descriptors */
mmuCreatePT(rtKernel);

/* fill   L2 Pagetable with region translation descriptors */
mmuCreateRegion(rtKernel); 

/* fill L2 system shared data/code register descriptors */
mmuCreateRegion(rtShared); 

/* fill L2 Pagetable with descriptors */
mmuCreateRegion(rtLoad); 

/* fill L2 storage memory area PAGETABLE REGION */
mmuCreateRegion(rtPT);

/* load   l2 system page table descriptor into L1 pagetable */
mmuAttachPT(rtKernel);     

/* fill L1 with peripheral register descriptors */
mmuCreateRegion(rtPeriph);
   
return 0;
}

/* -- mmuInitTask -------------------------------------------------------------
 * 
 * Description : initialize a task
 *
 * Parameter   : RT rt - region to be created
 * Return      : TRUE - always
 * Notes       :
 *
 */


int mmuInitTask(RT rt)
{
   mmuCreatePT(rt);
   mmuCreateRegion(rt);
   mmuAttachPT(rt);
   return 0;
}

/* -- mmuLoadTask -------------------------------------------------------------
 * 
 * Description : load a task
 *
 * Parameter   : RT rt - region to be created
 * Return      : TRUE - always
 * Notes       :
 *
 */
 
int mmuLoadTask(RT rt)
{
   mmuAttachPT(rt);
   mmuFlushCache();
   mmuFlushTLB();
   mmuLoadRegion(rt);
   return 0;
}

/* -- mmuCreatePT -------------------------------------------------------------
 * 
 * Description : create a page table
 *
 * Parameter   : RT rt - region to be created
 * Return      : TRUE - always
 * Notes       :
 *
 */
 
int mmuCreatePT(RT rt)
{
unsigned int  *pt;
int  count,i; 

pt = (unsigned int *)rt[PTA];

  switch (rt[TYPE])
  { 
  case COARSE: {count =  256; break;}
  case SECTION:{count = 4096; break;}
  case FINE:   {count = 1024; break;}
  default:     { /* place error handler here ... */ break;}
  }  

  for (i = count -1; i >= 0; i--)
  {
  pt[i] = FAULT;
  }
 
return 0; 
}

/* -- mmuAttachPT -------------------------------------------------------------
 * 
 * Description : attach a page table
 *
 * Parameter   : RT rt - region to be created
 * Return      : TRUE - always
 * Notes       :
 *
 */

int mmuAttachPT(RT rt)
{
unsigned int * ttb = (unsigned int *)TTB; 

  switch (rt[TYPE])
  { 
  case COARSE: {ttb[rt[VA] >> 20] = (rt[PTA]&0xfffffc00) | rt[DOM]<<5 | 0x11; break;}
  case SECTION:{break;}
  case FINE:   {ttb[rt[VA] >> 20] = (rt[PTA]&0xfffff000) | rt[DOM]<<5 | 0x13; break;}
  default:     { /* place error handler here */ break;}
  }  

return 0;
}

/* -- mmuCreateRegion ---------------------------------------------------------
 * 
 * Description : Create a new region
 *
 * Parameter   : RT rt - region to be created
 * Return      : TRUE - always
 * Notes       :
 *
 */

int mmuCreateRegion(RT rt )
{
   unsigned int field, start;
   int i,j;
   unsigned int lAP = rt[AP]&0x3;

   unsigned int *pt;
   pt = (unsigned int *)rt[PTA];
   
   switch (rt[TYPE])
   { 
      case COARSE: 
      {
         unsigned int lPA = rt[PA]&0xfffff000;
         start = ((rt[VA]& 0x000ff000) >> 12);
         field = lAP<<10 | lAP<<8 | lAP<<6 | lAP<<4 | (rt[CB]&0x3)<< 2 | 0x2;

         for (i = rt[SIZE]-1 ; i >= 0; i--)
            pt[start+i] = (lPA + (i<<12) | field);
         break;
      }
      case SECTION:
      {
         unsigned int lPA = rt[PA]&0xfff00000;
         start = (rt[VA]>> 20);
         field = lAP<<10 | rt[DOM]<<5 | (rt[CB]&0x3) << 2 | 0x12;

         for (i = rt[SIZE]-1 ; i >= 0; i--)
            pt[start+i] = (lPA + (i<<20) | field);
         break;
      }
      case FINE:
      {
         unsigned int lPA = rt[PA]&0xfffff000;
         start = ((rt[VA]& 0x000ff000) >> 12);
         field = lAP<<10 | lAP<<8 | lAP<<6 | lAP<<4 | (rt[CB]&0x3)<< 2 | 0x2;

         for (i = (rt[SIZE]-1) ; i >= 0; i--)
            for (j = 3 ; j >= 0; j--)
                pt[start+(i*4)+j] = (lPA + (i<<12) | field);
         break;
      }
      default: { /* place error handler here */ break;}
   }  
 
  
    return 0;
}

/* -- mmuLoadRegion -----------------------------------------------------------
 * 
 * Description : Load a region
 *
 * Parameter   : RT rt - region to be loaded
 * Return      : TRUE - always
 * Notes       :
 *
 */

int mmuLoadRegion(RT rt)
{
   unsigned int *from, *to;
      unsigned i;
   from = (unsigned int *)rt[LA];
   to   = (unsigned int *)rt[VA];

   for (i = 0; i < rt[SIZE] * 1024; i++)  
      to[i]=from[i];         //size = number of 4k blocks
   return 0;
}

/* -- mmuInitTasks ------------------------------------------------------------
 * 
 * Description : Initialize the 3 tasks
 *
 * Parameter   : none...
 * Return      : none...
 * Notes       :
 *
 */

void mmuInitTasks(void)
{
mmuInitTask(MmuPCB_RegionTable1);
mmuInitTask(MmuPCB_RegionTable2);
mmuInitTask(MmuPCB_RegionTable3);
}

/* -- mmuLoadTasks ------------------------------------------------------------
 * 
 * Description : Load 3 tasks
 *
 * Parameter   : none...
 * Return      : none...
 * Notes       :
 *
 */
 
void mmuLoadTasks(void)
{
mmuLoadTask(MmuPCB_RegionTable1);
mmuLoadTask(MmuPCB_RegionTable2);
mmuLoadTask(MmuPCB_RegionTable3);
}

/* -- mmuSchedule -------------------------------------------------------------
 * 
 * Description : schedules the a new task
 *
 * Parameter   : unsigned int tsk - 0 | 1 | 2
 * Return      : none...
 * Notes       :
 *
 */

void mmuSchedule (unsigned int tsk)
{
mmuFlushCache();
mmuFlushTLB();

  switch (tsk)
  {
  case 0: mmuAttachPT(MmuPCB_RegionTable1); break;
  case 1: mmuAttachPT(MmuPCB_RegionTable2); break;
  case 2: mmuAttachPT(MmuPCB_RegionTable3); break;
  }
}
      
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

void memoryMmuSystem (void)
{
unsigned int ttb = TTB;

/*
 * -----------------------------------------------------------
 *
 * Initialize all the MMU regions
 *
 * -----------------------------------------------------------
 */

mmuInitSystem ();

/*
 * -----------------------------------------------------------
 *
 * Initialize the tasks
 *
 * -----------------------------------------------------------
 */

mmuInitTasks ();

/*
 * -----------------------------------------------------------
 *
 * Set the Translation table base address
 *
 * -----------------------------------------------------------
 */

mmuSetTTB(ttb);
  
/*
 * -----------------------------------------------------------
 *
 * Change domain access
 *
 * -----------------------------------------------------------
 */

changeDomAccess(0x40000040,0xffffffff);
}

