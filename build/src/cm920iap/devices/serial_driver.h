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
 
/*****************************************************************************
 * Simple Little Operating System - SLOS
 *****************************************************************************/

/*****************************************************************************
 * 
 * Module       : serial_driver.h
 * Description  : low level serial device driver interface
 * OS           : SLOS 0.03
 * Platform     : cm920iap
 * History      : 
 *
 * 25th November 2001 Andrew N. Sloss
 * - create a template
 *
 *****************************************************************************/

/*****************************************************************************
 * ROUTINES
 *****************************************************************************/

/* -- serial_init -------------------------------------------------------------
 *
 * Description : initalize the driver
 * 
 * Parameters  : none...
 * Return      : none...
 * Notes       : none...
 *
 */

void serial_init(void);

/* -- serial_open -------------------------------------------------------------
 *
 * Description : open the serial display  
 * 
 * Parameters  : unsigned device = DEVICE_serial_e7t
 *             : unsigned ignored - for this device
 * Return      : UID -
 * Notes       : 
 *
 */

UID serial_open(unsigned device,unsigned ignored);

/* -- serial_close ------------------------------------------------------------
 *
 * Description : example open on the serial 
 * 
 * Parameters  : UID id = DEVICE_serial_e7t 
 * Return      : 
 *   DEVICE_SUCCESS - successfully close the device
 *   DEVICE_UNKNOWN - couldn't identify the UID
 * Notes       : 
 *
 */

int serial_close(UID id);

/* -- serial_write_byte -------------------------------------------------------
 *
 * Description : read a particular byte value 
 * 
 * Parameters  : UID id
 *             : BYTE serial = 0-9 
 * Return      : none...
 * Notes       : 
 */

void serial_write_byte(UID id,BYTE serial);

/* -- serial_read_byte --------------------------------------------------------
 *
 * Description : read a particular byte value 
 * 
 * Parameters  : UID id
 * Return      : BYTE value 0-9 
 * Notes       : an example of a led read bit
 */

BYTE serial_read_byte(UID id);

