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
*/

   .global mmuChangeControl
   .global changeDomAccess   
   .global mmuSetTTB   
   .global mmuFlushTLB   
   .global mmuFlushCache     

mmuFlushCache:
     MOV r0, #0
     MCR p15,0,r0,c7,c5,0   @ ; flush i Cache
     MCR p15,0,r0,c7,c6,0   @ ; flush d cache
     MOV pc, lr

/*
;-----------------
; Change Domain Access Register Values
; int changeDomAccess(unsigned value, unsigned mask)
;-----------------
*/
changeDomAccess:
   MVN r2, r1                @ ; invert mask
   BIC r3, r0, r2            @ ; clear values that are not masked
   CMP r3, r0
   BNE ErrorControl          @ ; value outside of mask set 
   MRC p15, 0, r3, c3, c0, 0 @ ; get domain access register values
   BIC r3, r3, r1            @ ; mask off bits that change
   ORR r3, r3, r0            @ ; set bits that change
   MCR p15, 0, r3, c3, c0, 0 @ ; set domain access register values
   MOV r0, #0
   MOV pc, lr

mmuSetTTB:
    MCR p15, 0, r0, c2, c0, 0 @ ; Write TTB register with base address
    MOV pc, lr
mmuFlushTLB:
    MOV r0, #0
    MCR p15, 0, r0, c8, c7, 0 @ ; flush both the TLBs
    MOV pc, lr
/*
;-----------------
; Change Control Register Values
; int changeControl(unsigned value, unsigned mask)
;-----------------   
*/
mmuChangeControl:
   MVN r2, r1                @ ; invert mask
   BIC r3, r0, r2            @ ; clear values that are not masked
   CMP r3, r0
   BNE ErrorControl          @ ; value outside of mask set 
   MRC p15, 0, r3, c1, c0, 0 @ ; get control register values
   BIC r3, r3, r1            @ ; mask off bits that change
   ORR r3, r3, r0            @ ; set bits that change
   MCR p15, 0, r3, c1, c0, 0 @ ; set control register values
   MOV r0, #0
   MOV pc, lr


OutOfRange:
   B OutOfRange               @ ; loop at error for debugging

ErrorControl:
   b ErrorControl
ErrorPermission:              @ ; Error Permission =4
   b ErrorPermission          @ ; debug test
   ADD r0, r0, #1
ErrorSize:                    @ ; Error  Size = 3
   ADD r0, r0, #1
ErrorAddress:                 @ ; Error  Address unaligned = 2
   ADD r0, r0, #1
ErrorRegion:                  @ ; Error  Region not valid = 1
   ADD r0, r0, #1
   MOV pc, lr
   .end
