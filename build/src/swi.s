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
     .global coreSWIHandler
     .global coreCallSWI
     .extern eventsSWIHandler

@ ****************************************************************************
@ * kernel swi handler event
@ ****************************************************************************

@
@  void coreCallSWI(registerstr *r0)
@

coreCallSWI:
     STMFD   r13!,{r0-r4,r12,lr}
     MOV     r4,r0
     LDMIA   r4,{r0-r3}
     SWI     5075
     STMIA   r4,{r0-r3}
     LDMFD   r13!,{r0-r4,r12,pc}

@
@  void coreSWIHandler(void)
@

coreSWIHandler:
     STMFD   sp!,{r0-r12,lr}       
     LDR     r10,[lr,#-4]          
     BIC     r10,r10,#0xff000000  
     MOV     r0,r10
     MOV     r1,sp
     MRS     r2,SPSR        
     STMFD   sp!,{r2}
     BL      eventsSWIHandler    @ eventsSWIHandler(r0-swiNumber,r1-point);
     LDMFD   sp!,{r2}          
     MSR     SPSR_cxsf,r2      
     LDMFD   sp!,{r0-r12,pc}^
     .end
