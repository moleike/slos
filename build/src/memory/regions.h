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
 * Module       : regions.h
 * Description  : privide the MMU definitions 
 * OS           : mmuSLOS
 * Platform     : cm920iap
 * History      :
 *
 * 9th August 2002 Andrew N. Sloss
 * - taken from Chris Wright's original code
 *
 *****************************************************************************/

/*****************************************************************************
 * MACROS
 *****************************************************************************/

/* Region Size */

#define SZ_4G   31
#define SZ_2G   30
#define SZ_1G   29
#define SZ_512M 28
#define SZ_256M 27
#define SZ_128M 26
#define SZ_64M  25
#define SZ_32M  24
#define SZ_16M  23
#define SZ_8M   22
#define SZ_4M   21
#define SZ_2M   20
#define SZ_1M   19
#define SZ_512K 18
#define SZ_256K 17
#define SZ_128K 16
#define SZ_64K  15
#define SZ_32K  14
#define SZ_16K  13
#define SZ_8K   12
#define SZ_4K   11

/* 920T */

#define cb 0x0
#define cB 0x1
#define WT 0x2
#define WB 0x3

/* 940T CB = ICache[2], DCache[1], Write Buffer[0] */

#define CCB 7
#define CCb 6
#define CcB 5
#define Ccb 4
#define cCB 3
#define cCb 2
#define ccB 1
#define ccb 0

/* CB by function */
/* 940T ICache[2], WB[1:0] = writeback, WT[1:0] = writethrough */
#define CWB 7
#define CWT 6
#define cWB 3
#define cWT 2

/* Std Data Permissions */
#define rwrw 0x0
#define RWrw 0x1 
#define RWRw 0x2 
#define RWRW 0x3 

/* Extended Data Permissions */
#define Rwrw 0x5
#define RwRw 0x6 


/* Instruction Permissions */
#define xx 0x0
#define Xx 0x1 
#define XX 0x3

/* 920T permissions */
#define RWX 0x3


/* Std System Permissions = (inst[7:4] + data[3:0]) 2bits valid */
#define rwxrwx (xx << 4) + (rwrw)
#define rwXrwx (Xx << 4) + (rwrw)
#define rwXrwX (XX << 4) + (rwrw)

#define RWxrwx (xx << 4) + (RWrw)
#define RWXrwx (Xx << 4) + (RWrw)
#define RWXrwX (XX << 4) + (RWrw)

#define RWxRwx (xx << 4) + (RWRw)
#define RWXRwx (Xx << 4) + (RWRw)
#define RWXRwX (XX << 4) + (RWRw)

#define RWxRWx (xx << 4) + (RWRW)
#define RWXRWx (Xx << 4) + (RWRW)
#define RWXRWX (XX << 4) + (RWRW)



/* Extended System Permissions = (inst[7:4] + data[3:0]) 4bits valid */

#define Rwxrwx (xx << 4) + (Rwrw)
#define RwXrwx (Xx << 4) + (Rwrw)
#define RwXrwX (XX << 4) + (Rwrw)

#define RwxRwx (xx << 4) + (RwRw)
#define RwXRwx (Xx << 4) + (RwRw)
#define RwXRwX (XX << 4) + (RwRw)


#define ACTIVE 1
#define DORMANT 0

/* Define Domains */
#define D15 0x0f
#define D14 0x0e
#define D13 0x0d
#define D12 0x0c
#define D11 0x0b
#define D10 0x0a
#define D09 0x09
#define D08 0x08
#define D07 0x07
#define D06 0x06
#define D05 0x05
#define D04 0x04
#define D03 0x03
#define D02 0x02
#define D01 0x01
#define D00 0x00

/* Page Table Assignments */

#define SYSTEM   0
#define  TASK1   1 
#define  TASK2   2 
#define  TASK3   3 

/* Region Number Assignment */
#define  BACKGROUND 0 
#define  PRIVATE_SYSTEM 2 
#define  ACTIVE_TASK  4 
#define  SHARED_SYSTEM 6 
#define  PERIPHERAL    8 
#define  BLOCK_REGION  10
#define  PT_REGION  20 

#define VA 0
#define SIZE 1
#define AP 2
#define CB 3
#define ENABLE 4
#define PTA 5
#define TYPE 6
#define DOM 7
#define PA 8
#define LA 9

#define FAULT 0
#define COARSE 1
#define SECTION 2
#define FINE 3

#define TTB 0x00038000
#define PTB TTB + 0x4000 
#define PT(x) PTB +(x*0x400)
