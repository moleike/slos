/*****************************************************************************
 * Simple Little Operating System - SLOS
 *****************************************************************************/

/*****************************************************************************
 *
 * Module       : serial_driver.c
 * Description  : low level device driver for the serial device
 *                based on DDF v0.01. 
 * OS           : SLOS 0.03
 * Platform     : cm920iap
 * History      :
 *
 * 24th November 2001 Andrew N. Sloss
 * - create template to speed up driver development.
 *
 *****************************************************************************/

/*****************************************************************************
 * IMPORT
 *****************************************************************************/

#include "../../devices/ddf_frame.h"
#include "serial_driver.h"
#include "serial_macros.h"

/*****************************************************************************
 * MACROS
 *****************************************************************************/

#define DEVICE_SERIAL_CM920IAP  55095

/*****************************************************************************
 * DATATYPES
 *****************************************************************************/

typedef struct 
{
  unsigned int baudrate[2]; /* baud rate of the serial port ............ */
  unsigned int uid[2];      /* lock[0] = COM1 lock[1] = COM2 ........... */
} internal_serialstr;

/*****************************************************************************
 * STATICS
 *****************************************************************************/

internal_serialstr  node;

/*****************************************************************************
 * ROUTINES
 *****************************************************************************/

/* -- internal_serial_cm7iap_setup --------------------------------------------
 *
 * Description : internal serial port setup
 *
 * Parameters  : unsigned int port - UART address
 *             : unsigned int baud - baud rate
 * Return      :
 * Notes       :
 * 
 */

void internal_serial_cm920iap_setup(unsigned int port, unsigned int baudRate)
{
IO_WRITE(port + AMBA_UARTLCR_M, ((baudRate & 0xf00) >> 8));
IO_WRITE(port + AMBA_UARTLCR_L, (baudRate & 0xff));
IO_WRITE(port + AMBA_UARTLCR_H, (AMBA_UARTLCR_H_WLEN_8 | AMBA_UARTLCR_H_FEN));
}

/* -- serial_init -------------------------------------------------------------
 *
 * Description : initalize driver.
 * 
 * Parameters  : none...
 * Return      : none...
 * Notes       : none...
 *
 */

void serial_init(void)
{
/* initalize physical device ... */

/* initialize COM0 ......................... */
internal_serial_cm920iap_setup (INTEGRATOR_UART0_BASE,ARM_BAUD_9600);

/* initialize COM1 ......................... */
internal_serial_cm920iap_setup (INTEGRATOR_UART1_BASE,ARM_BAUD_9600);

/* setup internal structure ... */

node.baudrate[0] = ARM_BAUD_9600;
node.baudrate[1] = ARM_BAUD_9600;
node.uid[COM0]   = NONE;
node.uid[COM1]   = NONE;
}

/* -- serial_open -------------------------------------------------------------
 *
 * Description : open the segment device driver 
 * 
 * Parameters  : unsigned major = DEVICE_SEGMENT_E7T 
 *             : unsigned ignored = anything
 * Return      : if (success) return UART0_BASE or UART1_BASE 
 *                  else if (alreadyopen) return DEVICE_IN_USE
 *                  else if (unknown) return DEVICE_NEXT
 * Notes       :
 *
 */

UID serial_open(unsigned major,unsigned com) 
{
  if (major==DEVICE_SERIAL_CM920IAP)
  {
    if (com==COM0 || com==COM1)
    {
      if (node.uid[com]!=NONE) 
      {
      return DEVICE_IN_USE;
      } 
      else
      {
      node.uid[com] = uid_generate ();	
      return node.uid[com];  
      }
    } 
  }
    
return DEVICE_NEXT;
}

/* -- serial_close ------------------------------------------------------------
 *
 * Description : close open handle
 * 
 * Parameters  : UID id 
 * Return      : 
 *   DEVICE_SUCCESS - successfully close the device
 *   DEVICE_UNKNOWN - couldn't identify the UID
 * Notes       : 
 *
 */

int serial_close(UID id) 
{
  if (node.uid[COM0]==id) 
  { 	
  node.uid[COM0] = NONE;
  return DEVICE_SUCCESS;
  }

  if (node.uid[COM1]==id) 
  { 	
  node.uid[COM1] = NONE;
  return DEVICE_SUCCESS;
  }

return DEVICE_UNKNOWN;
}

/* -- serial_write_byte -------------------------------------------------------
 *
 * Description : waites for response from hardware and writes a 
 *               byte to the device 
 * 
 * Parameters  : UART port address
 *             : BYTE data
 * Return      : none...
 * Notes       : an example of a led write bit
 *
 */

void internal_serial_write(unsigned int port,BYTE c)		
{
while ( TX_READY(GET_STATUS(port))==0){;}
PUT_CHAR(port,c);
}

/* -- serial_write_byte -------------------------------------------------------
 *
 * Description : write a byte to the device 
 * 
 * Parameters  : UID device
 *             : BYTE data
 * Return      : none...
 * Notes       : an example of a led write bit
 *
 */

void serial_write_byte(UID id,BYTE data) 
{

  if (node.uid[COM0]==id) 
  {
  internal_serial_write (INTEGRATOR_UART0_BASE,data);
  return;
  }

  if (node.uid[COM1]==id) 
  {
  internal_serial_write (INTEGRATOR_UART1_BASE,data);
  return;
  }

}

/* -- internal_serial_read ----------------------------------------------------
 *
 * Description : standard implementation of getkey.
 *
 * Parameters  : none...
 * Return      : none...
 * Notes       : 
 *
 */	
	
BYTE internal_serial_read(unsigned int port)
{

  while ( (RX_DATA(GET_STATUS(port)))==0 ) {;}

return GET_CHAR(port);
}	

/* -- serial_read_byte --------------------------------------------------------
 *
 * Description : read a particular byte value
 * 
 * Parameters  : UID id
 * Return      : read byte otherwise 255
 * Notes       :
 */

BYTE  serial_read_byte(UID id) 
{
  if (node.uid[COM0]==id) 
  {
  return internal_serial_read (INTEGRATOR_UART0_BASE);
  }
 
  if (node.uid[COM1]==id) 
  {
  return internal_serial_read (INTEGRATOR_UART1_BASE);
  }

return 255;
}

