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
 * Simple Little Operating System  - SLOS
 *****************************************************************************/

/*****************************************************************************
 * 
 * Module       : io.c
 * Description  : interface to the low level drivers. io conform
 *                with DDF 0.01 specification.
 * OS           : SLOS 0.03
 * Platform     : cm940iap
 * History      :
 *
 * 20th November 2001 Andrew N. Sloss
 * - created io.c from the DDF 0.01 test program
 *
 *****************************************************************************/

/*****************************************************************************
 * IMPORT 
 *****************************************************************************/

#include "ddf_frame.h"

/*****************************************************************************
 * ROUTINES 
 *****************************************************************************/

/* -- io_initalize_drivers ---------------------------------------------------
 *
 * Description : initializes all the device driver in the device_treestr
 *
 * Parameters  : DDF does not take any parameter
 * Return	     : none...
 * Notes       :
 * 
 */

void ioInitializeDrivers(void);

/* -- io_open_driver ---------------------------------------------------------
 * 
 * Description : open a driver for access
 *
 * Parameters  : int *id - pointer the id 
 *             : unsigned major - major device i.e. DEVICE_SERIAL_E7T
 *             : unsigned minor - minor device i.e. COM1
 * Return      : device_treestr * ptr
 * Notes       :
 *
 */ 

device_treestr *ioOpenDriver(int *id,unsigned major,unsigned minor);

/* -- io_open_driver ---------------------------------------------------------
 * 
 * Description : open a driver for access
 *
 * Parameters  : device_treestr * - pointer to device node. 
 *             : UID id - id of particular device
 * Return      : int 
 * Notes       : 
 *
 */ 

int ioCloseDriver(device_treestr *d, UID id);

/* -- io_write_bit -----------------------------------------------------------
 * 
 * Description : write a bit to the device
 *
 * Parameters  : device_treestr * - pointer to device node. 
 *             : UID id - id of particular device
 *             : BYTE bit - only least significant used
 * Return      : none...
 * Notes       : 
 *
 */ 

void ioWriteBit(device_treestr *d,UID id,BYTE bit);

/* -- io_read_bit ------------------------------------------------------------
 * 
 * Description : write a bit to the device
 *
 * Parameters  : device_treestr * - pointer to device node. 
 *             : UID id - id of particular device
 *             : BYTE bit - only least significant used
 * Return      : BYTE if = 255 then error
 * Notes	     : 
 *
 */ 

BYTE ioReadBit(device_treestr *d,UID id);


/* -- io_write_byte ----------------------------------------------------------
 * 
 * Description : write a bit to the device
 *
 * Parameters  : device_treestr * - pointer to device node. 
 *             : UID id - id of particular device
 *             : BYTE bit - only least significant used
 * Return      : none...
 * Notes       : 
 *
 */ 

void ioWriteByte(device_treestr *d,UID id,BYTE bit);

/* -- io_read_byte -----------------------------------------------------------
 * 
 * Description : write a bit to the device
 *
 * Parameters  : device_treestr * - pointer to device node. 
 *             : UID id - id of particular device
 *             : BYTE bit - only least significant used
 * Return      : BYTE if = 255 then error
 * Notes       : 
 *
 */ 

BYTE ioReadByte(device_treestr *d,UID id);

/* -- io_write_block ---------------------------------------------------------
 * 
 * Description : write a block to the device
 *
 * Parameters  : device_treestr * - pointer to device node. 
 *             : UID id - id of particular device
 *             : BYTE bit - only least significant used
 * Return      : none...
 * Notes       : 
 *
 */ 

void ioWriteBlock(device_treestr *d,UID id,block_datastr *block);

/* -- io_read_bit ------------------------------------------------------------
 * 
 * Description : read a block to the device
 *
 * Parameters  : device_treestr * - pointer to device node. 
 *             : UID id - id of particular device
 *             : BYTE bit - only least significant used
 * Return      : BYTE if = 255 then error
 * Notes       : 
 *
 */ 

block_datastr *ioReadBlock(device_treestr *d,UID id);

