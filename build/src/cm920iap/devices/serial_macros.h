#define ON		1
#define OFF		0

#define INTEGRATOR_UART0_BASE   0x16000000
#define INTEGRATOR_UART1_BASE   0x17000000

#define AMBA_UARTDR             0x00
#define AMBA_UARTRSR            0x04
#define AMBA_UARTECR            0x04
#define AMBA_UARTLCR_H          0x08
#define AMBA_UARTLCR_M          0x0C
#define AMBA_UARTLCR_L          0x10
#define AMBA_UARTCR             0x14
#define AMBA_UARTFR             0x18
#define AMBA_UARTIIR            0x1C
#define AMBA_UARTICR            0x1C
#define AMBA_UARTILPR           0x20

#define AMBA_UARTRSR_OE         0x08
#define AMBA_UARTRSR_BE         0x04
#define AMBA_UARTRSR_PE         0x02
#define AMBA_UARTRSR_FE         0x01

#define AMBA_UARTFR_TXFF        0x20
#define AMBA_UARTFR_RXFE        0x10
#define AMBA_UARTFR_BUSY        0x08
#define AMBA_UARTFR_TMSK        (AMBA_UARTFR_TXFF + AMBA_UARTFR_BUSY)
 
#define AMBA_UARTCR_RTIE        0x40
#define AMBA_UARTCR_TIE         0x20
#define AMBA_UARTCR_RIE         0x10
#define AMBA_UARTCR_MSIE        0x08
#define AMBA_UARTCR_IIRLP       0x04
#define AMBA_UARTCR_SIREN       0x02
#define AMBA_UARTCR_UARTEN      0x01
 
#define AMBA_UARTLCR_H_WLEN_8   0x60
#define AMBA_UARTLCR_H_WLEN_7   0x40
#define AMBA_UARTLCR_H_WLEN_6   0x20
#define AMBA_UARTLCR_H_WLEN_5   0x00
#define AMBA_UARTLCR_H_FEN      0x10
#define AMBA_UARTLCR_H_STP2     0x08
#define AMBA_UARTLCR_H_EPS      0x04
#define AMBA_UARTLCR_H_PEN      0x02
#define AMBA_UARTLCR_H_BRK      0x01

#define AMBA_UARTIIR_RTIS       0x08
#define AMBA_UARTIIR_TIS        0x04
#define AMBA_UARTIIR_RIS        0x02
#define AMBA_UARTIIR_MIS        0x01


#define ARM_BAUD_460800         1
#define ARM_BAUD_230400         3
#define ARM_BAUD_115200         7
#define ARM_BAUD_57600          15
#define ARM_BAUD_38400          23
#define ARM_BAUD_19200          47
#define ARM_BAUD_14400          63
#define ARM_BAUD_9600           95
#define ARM_BAUD_4800           191
#define ARM_BAUD_2400           383
#define ARM_BAUD_1200           767

/* Default port for use by Operating System or program */

#define OS_COMPORT              INTEGRATOR_UART0_BASE
#define OS_IRQBIT_NUMBER        INT_UARTINT0
#define OS_IRQBIT_MASK          INTMASK_UARTINT0
#define OS_IRQBIT               OS_IRQBIT_MASK

#define DEBUG_COMPORT           OS_COMPORT
#define DEBUG_IRQBIT            OS_IRQBIT

/* Values to set given baud rates */
#define DEFAULT_HOST_BAUD       ARM_BAUD_9600
#define DEFAULT_OS_BAUD         ARM_BAUD_38400

#ifndef LLEVELIO
#define LLEVELIO                1
#define GET_STATUS(p)           (IO_READ((p) + AMBA_UARTFR))
#define IO_READ(p)              ((*(volatile unsigned int *)(p)) & 0xFF)
#define IO_WRITE(p, c)          (*(unsigned int *)(p) = (c))
#define GET_CHAR(p)             (IO_READ((p) + AMBA_UARTDR))
#define PUT_CHAR(p, c)          (IO_WRITE(((p) + AMBA_UARTDR), (c)))
#define RX_DATA(s)              (((s) & AMBA_UARTFR_RXFE) == 0)
#define TX_READY(s)             (((s) & AMBA_UARTFR_TXFF) == 0)
#define TX_EMPTY(p)             ((GET_STATUS(p) & AMBA_UARTFR_TMSK) == 0)
#endif
		
#define COM1	                (1)
#define COM0	                (0)
