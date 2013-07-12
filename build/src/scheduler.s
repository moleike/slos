@ ****************************************************************************
@ * Simple Little Operating System - SLOS
@ ****************************************************************************

@ ****************************************************************************
@ *
@ * Module     : scheduler.s
@ * Project	: SLOS
@ * Version	: 0.09
@ * Originator	: Andrew N. Sloss
@ * History    :
@ * 
@ * 16th July 2003 Andrew N. Sloss
@ * - added header information
@ *
@ ****************************************************************************

     .text
     .code 32
     .align 0
     .global MmuPCB_CurrentTask
     .global MmuPCB_PtrCurrentTask
     .global MmuPCB_PtrNextTask
     .global MmuPCB_Table
     .global MmuPCB_TopOfIRQStack
     .global kernelScheduler
     .global mmuSchedule

kernelScheduler:

@; ---------------------------------------------------
@; Scheduler: simple round robin algorithm
@; ---------------------------------------------------

CurrentTask:
     LDR     r3,=MmuPCB_CurrentTask
     LDR     r0,[r3]                       @ ; r0 = Current Task ID
     LDR     r1,=MmuPCB_Table
     LDR     r1,[r1,r0,LSL#2]              @ ; r1 = address of current task
     LDR     r2,=MmuPCB_PtrCurrentTask
     STR     r1,[r2]                       @ ; save current structure task
@ ; ** PCB_PtrCurrentTask - updated with the new address
NextTask:
     ADD     r0,r0,#1                      @ ; r0 = Current_Task+1
     CMP     r0,#3
     MOVEQ   r0,#0                         @ ; if r0==MaxTask then r0=0
     STR     r0,[r3]                       @ ; save new Task ID
     STMFD   sp!,{r0-r4,r12,lr}
     BL      mmuSchedule                   @ ; setup mmu
     LDMFD   sp!,{r0-r4,r12,lr}
     LDR     r1,=MmuPCB_Table
     LDR     r1,[r1,r0,LSL#2]              @ ; r1 = new next task PCB address
     LDR     r0,=MmuPCB_PtrNextTask
     STR     r1,[r0]                       @ ; save current structure task
@ ; ** MmuPCB_PtrCurrentTask   = current PCB
@ ; ** MmuPCB_PtrNextTask	  = next PCB
@ ; ** MmuPCB_CurrentTask	  = new TASK_ID

@ ; ---------------------------------------------------
@ ; Context switch
@ ; ---------------------------------------------------

handler_contextswitch:
     LDMFD   sp!,{r0-r3,r12,r14}           @ ; restore the remaining registers
     LDR     r13,=MmuPCB_PtrCurrentTask
     LDR     r13,[r13]
     SUB     r13,r13,#60                   @ ; r13->current PCB
     STMIA   r13,{r0-r14}^                 @ ; save User registers
     MRS     r0, SPSR
     STMDB   r13,{r0,r14}                  @ ; save the rest
     LDR     r13,=MmuPCB_PtrNextTask
     LDR     r13,[r13]
     SUB     r13,r13,#60                   @ ; r13->new PCB
     LDMDB   r13,{r0,r14}
     MSR     spsr_cxsf, r0
     LDMIA   r13,{r0-r14}^                 @ ; load User registers
     LDR     r13,=MmuPCB_IRQStack
     LDR     r13,[r13]
     MOVS    pc,r14                        @ ; return next task
     .end
