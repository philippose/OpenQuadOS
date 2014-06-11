/**
 ******************************************************************************
 * @file    hal_plat_mapping.h
 * @author  Philippose Rajan
 * @date    03.06.2014
 * @brief   <Put in a brief description here>
 *
 * @see     The GNU Public License (GPL) Version 3
 *
 ******************************************************************************
 */
/*
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 * or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License
 * for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 */

#ifndef __hal_plat_mapping_H
#define __hal_plat_mapping_H

/* ---- Publicly visible Macros ---------------------------------------- */

/**
 * Maximum number possible for selection of pins on a port
 *
 * Note: This does not imply that all the ports have this many
 * Pins!
 */
#define PLAT_PORT_MAX_PINS       15


/* ---- LED Definitions for the STM32F3Discovery Board --------- */
typedef enum
{
    PLAT_LED_Min           = 0,
    PLAT_LED_Red_N         = 0,
    PLAT_LED_Orange_NE     = 1,
    PLAT_LED_Green_E       = 2,
    PLAT_LED_Blue_SE       = 3,
    PLAT_LED_Red_S         = 4,
    PLAT_LED_Orange_SW     = 5,
    PLAT_LED_Green_W       = 6,
    PLAT_LED_Blue_NW       = 7,
    PLAT_LED_Max           = 7
} PLAT_LED_Pins;
/* ------------------------------------------------------------- */


/* ---- Publicly visible Variables and Constants ----------------------- */

/* ---- Publicly visible Functions ------------------------------------- */


#endif /* __hal_plat_mapping_H */

