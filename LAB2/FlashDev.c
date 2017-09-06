/***********************************************************************/
/*  This file is part of the ARM Toolchain package                     */
/*  Copyright KEIL ELEKTRONIK GmbH 2003 - 2008                         */
/***********************************************************************/
/*                                                                     */
/*  FlashDev.C:  Device Description for Philips LPC2xxx 256kB Flash    */
/*               using Flash Boot Loader with IAP                      */
/*                                                                     */
/***********************************************************************/

#include "C:\Keil_v5\ARM\Flash\FlashOS.H"        // FlashOS Structures


struct FlashDevice const FlashDevice  =  {
   FLASH_DRV_VERS,             // Driver Version, do not modify!
   "1986BE IAP 128kB EXTERNAL 1636 Flash",  // Device Name 
   ONCHIP,                     // Device Type
   0x10000000,                 // Device Start Address
   0x00020000,                 // Device Size without Boot Loader (248kB)
   1024,                     // Programming Page Size
   0,                          // Reserved, must be 0
   0xff,                       // Initial Content of Erased Memory
   10000,                        // Program Page Timeout 100 mSec
   30000,                       // Erase Sector Timeout 3000 mSec

// Specify Size and Address of Sectors
   0x000400, 0x000000,         // Sector Size  8kB (8 Sectors)
   SECTOR_END
};
