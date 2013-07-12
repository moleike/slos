@ ****************************************************************************
@ * Simple Little Operating System - SLOS
@ ****************************************************************************

@ ****************************************************************************
@ *
@ * Module     : swi.s
@ * Project	: SLOS
@ * Version	: 0.09
@ * Originator	: Andrew N. Sloss
@ * History    :
@ * 
@ * 16th July 2003 Andrew N. Sloss
@ * - added header information
@ *
@ * 13th January 2004 Andrew N. Sloss
@ * - copy over SWI.s from base SLOS
@ *
@ ****************************************************************************

     .text
     .code 32 
     .align 0
     .global _start,start,_mainCRTStartup
     .global coreCallSWI
     .extern entry

_start:
start:
_mainCRTStartup:

     LDR     lr,=entry
     MOV     pc,lr
     
@ ****************************************************************************
@ * kernel swi handler event
@ ****************************************************************************

@
@  void coreCallSWI (registerstr *r0)
@

coreCallSWI:
     STMFD   r13!,{r0-r4,r12,lr}
     MOV     r4,r0
     LDMIA   r4,{r0-r3}
     SWI     5075
     STMIA   r4,{r0-r3}
     LDMFD   r13!,{r0-r4,r12,pc}
     .end
