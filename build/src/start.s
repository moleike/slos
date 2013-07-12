@ //
@ // ********************************************************
@ // @ * Simple Little Operating System - SLOS
@ // @ *******************************************************

@ ****************************************************************************
@ *
@ * Module     : start.s
@ * Project	: SLOS
@ * Version	: 0.09
@ * Originator	: Andrew N. Sloss
@ * History    :
@ * 
@ * 16th July 2003 Andrew N. Sloss
@ * - added header information
@ *
@ ****************************************************************************

@ *******************************************************
@ * SLOS 2002 
@ *******************************************************

@ *******************************************************
@ * IMPORT 
@ *******************************************************

     .text
     .code 32
     .align 0
     .global _start,start,_mainCRTStartup


_start:
start:
_mainCRTStartup:
 
/* @ ----------------------------------------------------
 @ table offset  
 @ 00 - Reset
 @ 04 - Undefined instructions
 @ 08 - SWI instructions
 @ 0C - prefetch abort
 @ 10 - Data abort
 @ 14 - Reserved
 @ 18 - IRQ interrupts
 @ 1C - FIQ interrupts
 @ ----------------------------------------------------
*/
     LDR     pc,vectorReset
     LDR     pc,vectorUndefined
     LDR     pc,vectorSWI
     LDR     pc,vectorPrefetchAbort
     LDR     pc,vectorDataAbort
     LDR     pc,vectorReserved
     LDR     pc,vectorIRQ
     LDR     pc,vectorFIQ

@ -- Useful address to the PCB tables ------------------ 

ptrPCBTable:
     .word   MmuPCB_Table

@ -- Kernel Jump table ------------------------------ 

vectorReset:
     .word     coreInitialize
vectorUndefined:     
     .word     coreUndefinedHandler
vectorSWI:           
     .word     coreSWIHandler
vectorPrefetchAbort: 
     .word     corePrefetchAbortHandler
vectorDataAbort:     
     .word     coreDataAbortHandler
vectorReserved:      
     .word     coreReservedHandler
vectorIRQ:           
     .word     coreIRQHandler
vectorFIQ:           
     .word     coreFIQHandler

     .end
