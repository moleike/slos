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
@ *****************************************************************************
@ * Simple Little Operating System - SLOS
@ *****************************************************************************

@ *****************************************************************************
@ *
@ * Module       : cpsr
@ * Description  : CPSR control routinesb
@ * OS           : SLOS 0.09
@ * Platform     : generic
@ * History      :
@ *
@ * 15th July 2002 Andrew N. Sloss
@ * - added a header
@ *
@ *****************************************************************************

@ *****************************************************************************
@ * EXPORT
@ *****************************************************************************

     .text
     .code 32
     .align 0
     .global modifyControlCPSR

@ -- modifyControlCPSR --------------------------------------------------------
@ Description  : modify the control bits of the CPSR 
@ Parameters   : r0 - new modification
@ Return       : none... 

modifyControlCPSR:

@ ----------------------------------------------------------------------
@ Save registers: r3 and link register on the previous mode
@ stack.
@ Copy the stack to register r2 to preserve during a mode change.
@ Normalize the stack r13 in the calling mode. 
@ Save the remaining register onto the stack.
@ Assumption that the link register has the return address.
@ ----------------------------------------------------------------------

     STMFD   r13!,{r3}
     MOV     r3,r13	
     ADD     r13,r13,#4      
     STMFD   r3!,{r1,lr}

@ ----------------------------------------------------------------------
@ Currently on the stack: r3,r1,lr
@ Modify the control part of the CPSR  
@ ----------------------------------------------------------------------

     MRS     r1,CPSR
     BIC     r1,r1,#0xff 
     ORR     r1,r1,r0 
     MSR     CPSR_c,r1

@ ----------------------------------------------------------------------
@ Restore from the stack: r3,r1,lr
@ Return to the callee
@ ----------------------------------------------------------------------

     LDMFD   r3!,{r1,lr}
     LDMFD   r3,{r3}
     MOV     pc,lr
     .end
