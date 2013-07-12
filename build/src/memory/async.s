/*
;  ____________________________________________________________________
; 
;  Copyright (c) 2002, Andrew N. Sloss, Chris Wright and Dominic Symes
;  All rights reserved.
;  ____________________________________________________________________
; 
;  NON-COMMERCIAL USE License
;  
;  Redistribution and use in source and binary forms, with or without 
;  modification, are permitted provided that the following conditions 
;  are met: 
;  
;  1. For NON-COMMERCIAL USE only.
; 
;  2. Redistributions of source code must retain the above copyright 
;     notice, this list of conditions and the following disclaimer. 
; 
;  3. Redistributions in binary form must reproduce the above 
;     copyright notice, this list of conditions and the following 
;     disclaimer in the documentation and/or other materials provided 
;     with the distribution. 
; 
;  4. All advertising materials mentioning features or use of this 
;     software must display the following acknowledgement:
; 
;     This product includes software developed by Andrew N. Sloss,
;     Chris Wright and Dominic Symes. 
; 
;   THIS SOFTWARE IS PROVIDED BY THE CONTRIBUTORS ``AS IS'' AND ANY 
;   EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE 
;   IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR 
;   PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE CONTRIBUTORS BE 
;   LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, 
;   OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, 
;   PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, 
;   OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY 
;   THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR 
;   TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT 
;   OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY 
;   OF SUCH DAMAGE. 
; 
;  If you have questions about this license or would like a different
;  license please email :
; 
; 	andrew@sloss.net
; 
; 
; *****************************************************************************
; * Simple Little Operating System - mmuSLOS
; *****************************************************************************

; *****************************************************************************
; *
; * Module      : async 
; * Description : switch on system (enable cache and asynchronous mode).
; * History     :
; *
; * 8th July 2002 Andrew N. Sloss
; * - ported from Chris Wright's example code. 
; *
; * 2 August 2002 Andrew N. Sloss
; * - added MMU code
; * 
; *****************************************************************************
*/

     .extern jumpToTask1
     .extern mmuChangeControl
     .extern mmuLoadTasks
     .extern mmuFlushCache
     .extern mmuAttachPT
     .extern mmuFlushTLB	
     .extern MmuPCB_RegionTable1

     .global switchOnSystem

/*
; -------------------------------------------------------------------
; switchOnSystem :
;   enables I & D cache, and Write back
;  special to the 920 set the bus to asynchronous clocking
; -------------------------------------------------------------------
*/

switchOnSystem:
/*
; --------------------------------------------------------------------
; asynchronous clocking, 920t only
; --------------------------------------------------------------------
*/
     LDR     r0,=0xc0000000
     LDR     r1,=0xc0000000
     BL      mmuChangeControl
/*
; --------------------------------------------------------------------
; enable: D&I cache,WB, and/or MMU
; --------------------------------------------------------------------
*/
/*
; Enable just MMU i.e. mmuChangeControl(0x1, 0x1);
;      
;     LDR r0,=0x1
;     LDR r1,=0x1
*/
/*
; --------------------------------------------------------------------
; Enable cache and MMU i.e. changeControl(0x100d, 0x100d);
; --------------------------------------------------------------------
*/
     LDR    r0,=0x100d
     LDR    r1,=0x100d

     BL     mmuChangeControl
/*
; --------------------------------------------------------------------
; load tasks into memory
; --------------------------------------------------------------------
*/
     BL     mmuLoadTasks
/*
; -------------------------------------------------------------------
; Prepare MMU for Task1
; -------------------------------------------------------------------
*/
     BL      mmuFlushCache
     BL      mmuFlushTLB
     LDR     r0,=MmuPCB_RegionTable1    
     BL      mmuAttachPT
/*
; -------------------------------------------------------------------
; Jump to 0x400000 and switch to User mode and enable IRQ interrupts
; -------------------------------------------------------------------
*/
     MOV     r0,#0x400000
     B       jumpToTask1
     .end
