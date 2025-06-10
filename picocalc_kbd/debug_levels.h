/* SPDX-License-Identifier: GPL-2.0-only */
/*
 * Keyboard Driver for Blackberry Keyboards BBQ10 from arturo182. Software written by wallComputer.
 * debug_levels.h: Describes the debug levels that can be set for viewing code flow in dmesg.
 * Use dmesg -wH | grep beepy-kbd for easy viewing.
 */

#ifndef DEBUG_LEVELS_H_
#define DEBUG_LEVELS_H_

/*
 *  Set Debug Level with DEBUG_LEVEL.
 *   Types of Debug Messages:
 *       1. Functional Entries. printk() & dev_info() used to show Entries in init & exit, probe, irq, logic.
 *       2. Read/Write Values. dev_info() used to show Values read and written from i2c functions.
 *       3. Logical Debugs. dev_info() used for showing Logic flow.
 *   For All Informations ->  DEBUG_LEVEL set as (DEBUG_LEVEL_FE | DEBUG_LEVEL_RW | DEBUG_LEVEL_LD)
 *   For Only Read/Write in I2C Client ->  DEBUG_LEVEL set as (DEBUG_LEVEL_RW)
 *   For Informations on function entires->  DEBUG_LEVEL set as (DEBUG_LEVEL_FE)
 *   For No Debug ->  DEBUG_LEVEL set as (DEBUG_LEVEL_OFF)
 */

#define DEBUG_LEVEL_OFF             0
#define DEBUG_LEVEL_FE              1
#define DEBUG_LEVEL_RW              2
#define DEBUG_LEVEL_LD              4

#define DEBUG_LEVEL                 DEBUG_LEVEL_OFF
// #define DEBUG_LEVEL					DEBUG_LEVEL_FE
// #define DEBUG_LEVEL                (DEBUG_LEVEL_LD)
// #define DEBUG_LEVEL			(DEBUG_LEVEL_FE | DEBUG_LEVEL_RW | DEBUG_LEVEL_LD)
#endif

#if (DEBUG_LEVEL & DEBUG_LEVEL_FE)
#define dev_info_fe(...) dev_info(__VA_ARGS__)
#else
#define dev_info_fe(...)
#endif

#if (DEBUG_LEVEL & DEBUG_LEVEL_LD)
#define dev_info_ld(...) dev_info(__VA_ARGS__)
#else
#define dev_info_ld(...)
#endif
