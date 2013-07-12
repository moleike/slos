@  ____________________________________________________________________
@ 
@  Copyright (c) 2002, Andrew N. Sloss, Chris Wright and Dominic Symes
@  All rights reserved.
@  ____________________________________________________________________
@ 
@  NON-COMMERCIAL USE License
@  
@  Redistribution and use in source and binary forms, with or without 
@  modification, are permitted provided that the following conditions 
@  are met: 
@  
@  1. For NON-COMMERCIAL USE only.
@ 
@  2. Redistributions of source code must retain the above copyright 
@     notice, this list of conditions and the following disclaimer. 
@ 
@  3. Redistributions in binary form must reproduce the above 
@     copyright notice, this list of conditions and the following 
@     disclaimer in the documentation and/or other materials provided 
@     with the distribution. 
@ 
@  4. All advertising materials mentioning features or use of this 
@     software must display the following acknowledgement:
@ 
@     This product includes software developed by Andrew N. Sloss,
@     Chris Wright and Dominic Symes. 
@ 
@   THIS SOFTWARE IS PROVIDED BY THE CONTRIBUTORS ``AS IS'' AND ANY 
@   EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE 
@   IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR 
@   PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE CONTRIBUTORS BE 
@   LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, 
@   OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, 
@   PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES@ LOSS OF USE, DATA, 
@   OR PROFITS@ OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY 
@   THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR 
@   TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT 
@   OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY 
@   OF SUCH DAMAGE. 
@ 
@  If you have questions about this license or would like a different
@  license please email :
@ 
@ 	andrew@sloss.net
@ 
@ 
@ ****************************************************************************
@ * Simple Little Operating System - SLOS
@ ****************************************************************************

@ ***************************************************************************
@ *
@ * Module     : sal.s
@ * Project	: SLOS
@ * Version	: 0.09
@ * Originator	: Andrew N. Sloss
@ * History    :
@ * 
@ * 16th July 2003 Andrew N. Sloss
@ * - added header information
@ *
@ ***************************************************************************

     .global applicationLoader
     .extern initSetUpStacks

@ -- applicationLoader ------------------------------------------------------
@
@ Descriptions : application loader
@
@ Parameters   :
@ Return       :
@ Notes        :
@ 

applicationLoader:

     LDR     r11,=ALT

applicationLoaderLoop:
     LDR     r12,[r11],#4
     LDR     r14,[r11],#4
     LDR     r13,[r11],#4

     CMP     r13,#0
     BEQ     initSetUpStacks

applicationBlockCopy:
     LDMIA   r12!,{r0-r10}
     STMIA   r13!,{r0-r10}
     CMP     r12,r14
     BLE     applicationBlockCopy
     B       applicationLoaderLoop

@ ******************************************************************
@ *
@ * Application Loader Table
@ *
@ ******************************************************************

ALT:
@ ; entry into the table
@ ; {
@ ; src_startaddr
@ ; src_endaddr
@ ; dest_addr
@ ; }

@ ; task (3)

     .word    task3start
     .word    task3end
     .word    0x30000

@ ; task (2)

     .word    task2start
     .word    task2end
     .word    0x28000

@ ; task (1)

     .word    task1start 
     .word    task1end
     .word    0x20000

@ ; Terminate

     .word     0
     .word     0
     .word     0

     .data 
     .align 4
task1start:
     .incbin "../image/apps/task1.bin"
task1end:
task2start:
     .incbin "../image/apps/task2.bin"
task2end:
task3start:
     .incbin "../image/apps/task3.bin"
task3end:
     .end
