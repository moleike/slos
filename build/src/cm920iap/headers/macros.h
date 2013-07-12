/*
 *  ____________________________________________________________________
 * 
 *  Copyright (c) 2002, Andrew N. Sloss, Chris Wright and Dominic Symes
 *  All rights reserved.
 *  ____________________________________________________________________
 * 
 *  NON-COMMERCIAL USE License
 *  
 *  Redistribution and use in source and binary forms, with or without 
 *  modification, are permitted provided that the following conditions 
 *  are met: 
 *  
 *  1. For NON-COMMERCIAL USE only.
 * 
 *  2. Redistributions of source code must retain the above copyright 
 *     notice, this list of conditions and the following disclaimer. 
 * 
 *  3. Redistributions in binary form must reproduce the above 
 *     copyright notice, this list of conditions and the following 
 *     disclaimer in the documentation and/or other materials provided 
 *     with the distribution. 
 * 
 *  4. All advertising materials mentioning features or use of this 
 *     software must display the following acknowledgement:
 * 
 *     This product includes software developed by Andrew N. Sloss,
 *     Chris Wright and Dominic Symes. 
 * 
 *   THIS SOFTWARE IS PROVIDED BY THE CONTRIBUTORS ``AS IS'' AND ANY 
 *   EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE 
 *   IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR 
 *   PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE CONTRIBUTORS BE 
 *   LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, 
 *   OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, 
 *   PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, 
 *   OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY 
 *   THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR 
 *   TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT 
 *   OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY 
 *   OF SUCH DAMAGE. 
 * 
 *  If you have questions about this license or would like a different
 *  license please email :
 * 
 * 	andrew@sloss.net
 * 
 * 
 */
/***********************************************************************
 * Simple Little Operating System - SLOS 
 ***********************************************************************/

/***********************************************************************
 *
 * Module       : macros.h
 * Description  : brings in macro headers
 * OS           : mpuSLOS 0.03
 * Platform     : i940
 * History      : 
 *
 * 16th November 2001 Andrew N. Sloss
 * - added a macro header
 *
 * 28th May 2002 Andrew N. Sloss
 * - added Integrator/AP
 *
 ***********************************************************************/

/* -- Interrupt controller ------------------------------------------ */

/* Timer MACROS */

/*******************************************************************************/
/*  Counter/timer registers                                                    */
/*******************************************************************************/

#define Timer0 0x13000000     /* Timer 0 base address */
#define Timer1 0x13000100     /* Timer 1 base address */
#define Timer2 0x13000200     /* Timer 2 base address */

#define Timer_Load       0    /* offset to load register */
#define Timer_Value      1    /* offset to value register */
#define Timer_Control    2    /* offset to control register */
#define Timer_Clear      3    /* offset to clear timer register */

/*******************************************************************************/
/* Real Time Clock registers                                                   */
/*******************************************************************************/

#define rtc_Base	0x15000000
#define rtc_Data	0x00
#define rtc_Match	0x01
#define rtc_Stat 	0x02
#define rtc_Clear	0x02
#define rtc_Load	0x03
#define rtc_Control	0x04

/*******************************************************************************/
/* Counter/Timer control register bits                                         */
/*******************************************************************************/

#define TimerEnable      0x80
#define TimerPeriodic    0x40
#define TimerDisable     0x00
#define TimerFreerun	0x00
#define TimerPrescale    0x00
#define TimerPrescale16  0x04
#define TimerPrescale256 0x08

/* -- General ------------------------------------------------------ */

#define IRQVector	0x18


#define INTEGRATOR_CT_BASE              0x13000000	 /*  Counter/Timers */
#define INTEGRATOR_IC_BASE              0x14000000	 /*  Interrupt Controller */
#define INTEGRATOR_RTC_BASE             0x15000000	 /*  Real Time Clock */
#define INTEGRATOR_UART0_BASE           0x16000000	 /*  UART 0 */
#define INTEGRATOR_UART1_BASE           0x17000000	 /*  UART 1 */
#define INTEGRATOR_KBD_BASE             0x18000000	 /*  Keyboard */
#define INTEGRATOR_MOUSE_BASE           0x19000000	 /*  Mouse */

#define AMBA_UARTDR                     0x00	 /*  Data read or written from the interface. */
#define AMBA_UARTRSR                    0x04	 /*  Receive status register (Read). */
#define AMBA_UARTECR                    0x04	 /*  Error clear register (Write). */
#define AMBA_UARTLCR_H                  0x08	 /*  Line control register, high byte. */
#define AMBA_UARTLCR_M                  0x0C	 /*  Line control register, middle byte. */
#define AMBA_UARTLCR_L                  0x10	 /*  Line control register, low byte. */
#define AMBA_UARTCR                     0x14	 /*  Control register. */
#define AMBA_UARTFR                     0x18	 /*  Flag register (Read only). */
#define AMBA_UARTIIR                    0x1C	 /*  Interrupt indentification register (Read). */
#define AMBA_UARTICR                    0x1C	 /*  Interrupt clear register (Write). */
#define AMBA_UARTILPR                   0x20	 /*  IrDA low power counter register. */

#define AMBA_UARTRSR_OE                 0x08
#define AMBA_UARTRSR_BE                 0x04
#define AMBA_UARTRSR_PE                 0x02
#define AMBA_UARTRSR_FE                 0x01

#define AMBA_UARTFR_TXFF                0x20
#define AMBA_UARTFR_RXFE                0x10
#define AMBA_UARTFR_BUSY                0x08
#define AMBA_UARTFR_TMSK                (AMBA_UARTFR_TXFF + AMBA_UARTFR_BUSY)
 
#define AMBA_UARTCR_RTIE                0x40
#define AMBA_UARTCR_TIE                 0x20
#define AMBA_UARTCR_RIE                 0x10
#define AMBA_UARTCR_MSIE                0x08
#define AMBA_UARTCR_IIRLP               0x04
#define AMBA_UARTCR_SIREN               0x02
#define AMBA_UARTCR_UARTEN              0x01
 
#define AMBA_UARTLCR_H_WLEN_8           0x60
#define AMBA_UARTLCR_H_WLEN_7           0x40
#define AMBA_UARTLCR_H_WLEN_6           0x20
#define AMBA_UARTLCR_H_WLEN_5           0x00
#define AMBA_UARTLCR_H_FEN              0x10
#define AMBA_UARTLCR_H_STP2             0x08
#define AMBA_UARTLCR_H_EPS              0x04
#define AMBA_UARTLCR_H_PEN              0x02
#define AMBA_UARTLCR_H_BRK              0x01

#define AMBA_UARTIIR_RTIS               0x08
#define AMBA_UARTIIR_TIS                0x04
#define AMBA_UARTIIR_RIS                0x02
#define AMBA_UARTIIR_MIS                0x01


#define ARM_BAUD_460800                 1
#define ARM_BAUD_230400                 3
#define ARM_BAUD_115200                 7
#define ARM_BAUD_57600                  15
#define ARM_BAUD_38400                  23
#define ARM_BAUD_19200                  47
#define ARM_BAUD_14400                  63
#define ARM_BAUD_9600                   95
#define ARM_BAUD_4800                   191
#define ARM_BAUD_2400                   383
#define ARM_BAUD_1200                   767

/* Default port for use by Operating System or program */

#define OS_COMPORT                      INTEGRATOR_UART0_BASE
#define OS_IRQBIT_NUMBER                INT_UARTINT0
#define OS_IRQBIT_MASK                  INTMASK_UARTINT0
#define OS_IRQBIT                       OS_IRQBIT_MASK

#define DEBUG_COMPORT                   OS_COMPORT
#define DEBUG_IRQBIT                    OS_IRQBIT

/* Values to set given baud rates */
#define DEFAULT_HOST_BAUD               ARM_BAUD_9600
#define DEFAULT_OS_BAUD                 ARM_BAUD_38400

#ifndef LLEVELIO
#define LLEVELIO 1
#define GET_STATUS(p)		(IO_READ((p) + AMBA_UARTFR))
#define GET_CHAR(p)		(IO_READ((p) + AMBA_UARTDR))
#define PUT_CHAR(p, c)		(IO_WRITE(((p) + AMBA_UARTDR), (c)))
#define IO_READ(p)             ((*(volatile unsigned int *)(p)) & 0xFF)
#define IO_WRITE(p, c)         (*(unsigned int *)(p) = (c))
#define RX_DATA(s)		(((s) & AMBA_UARTFR_RXFE) == 0)
#define TX_READY(s)		(((s) & AMBA_UARTFR_TXFF) == 0)
#define TX_EMPTY(p)		((GET_STATUS(p) & AMBA_UARTFR_TMSK) == 0)
#endif

