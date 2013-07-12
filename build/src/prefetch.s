@ ****************************************************************************
@ * Simple Little Operating System - SLOS
@ ****************************************************************************

@ ****************************************************************************
@ *
@ * Module     : prefetch.s
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
     .global corePrefetchAbortHandler

corePrefetchAbortHandler:

     B	corePrefetchAbortHandler
     .end
