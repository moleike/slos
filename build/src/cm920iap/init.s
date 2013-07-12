@ ****************************************************************************
@ * Simple Little Operating System - SLOS
@ ****************************************************************************

@ ****************************************************************************
@ *
@ * Module     : init.s
@ * OS         : SLOS
@ * Version	: 0.09
@ * Originator	: Andrew N. Sloss
@ *
@ * 14 July 2003 Andrew N. Sloss
@ * - separated the pcbSetUp routine
@ *
@ ****************************************************************************

     .text
     .code 32
     .align 0
     .global coreInitialize
     .extern C_Entry
     .extern MmuPCB_PtrTask2
     .extern MmuPCB_PtrTask3
     .extern mpuInitFlush
     .extern C_EntryTask2
     .extern C_EntryTask3
     .extern MmuPCB_CurrentTask
     .extern applicationLoader
     .extern pcbSetUp
     .global initSetUpStacks
     
     .extern coreCallSWI

     .equ IRQ32md, 0x12
     .equ SVC32md, 0x13
     .equ SYS32md, 0x1f
     .equ NoInt, 0xc0

coreInitialize:

     BL     mmuFlushCache
     BL     bringUpInitFIQRegisters
     B      applicationLoader

/*
@ ------------------------------------------------
@ Setup stacks for SVC,IRQ,SYS&USER 
@ Mode = SVC 
@ ------------------------------------------------
*/
initSetUpStacks:

     MOV     sp,#0x10000           @ ; Kernel Stack
     MSR     CPSR_c,#NoInt|SYS32md
     LDR     sp,=0x408000          @ ; System Stack=0x408000
     MSR     CPSR_c,#NoInt|IRQ32md
     MOV     sp,#0x9000	           @ ; IRQ Stack = 0x9000
     MSR     CPSR_c,#NoInt|SVC32md

/*
@ ------------------------------------------------
@ Setup Task Process Control Block (PCB).
@ Mode = SVC
@ ------------------------------------------------
*/
     LDR     r0,=0x400000          @ ; Task 2
     LDR     r1,=MmuPCB_PtrTask2
     LDR     r2,=0x408000
     BL      pcbSetUp
     
     LDR     r0,=0x400000          @ ; Task 3
     LDR     r1,=MmuPCB_PtrTask3
     LDR     r2,=0x408000
     BL      pcbSetUp
     
@ ; -- set the current ID to TASK1 ...........

     LDR     r0, =MmuPCB_CurrentTask
     MOV     r1, #0
     STR     r1,[r0]              @ ; first task ID=0
     LDR     lr,=C_Entry
     MOV     pc,lr                @ ; call C_Entry
     .end

