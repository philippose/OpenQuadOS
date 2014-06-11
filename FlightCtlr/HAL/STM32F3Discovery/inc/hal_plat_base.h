/**
 ******************************************************************************
 * @file    hal_plat_base.h
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

#ifndef __hal_plat_base_H
#define __hal_plat_base_H

/* ---- Basic Includes required to develop on this Platform ------------ */

/* Setup the STM32 Libraries to use the Peripheral Libraries */
#if !defined (USE_STDPERIPH_DRIVER)
    #define USE_STDPERIPH_DRIVER
#endif


#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

/* ---- Platform specific Hardware includes ------------ */
#include "stm32f30x.h"
#include "stm32f30x_conf.h"
/* ----------------------------------------------------- */

/* ---- Includes from the Common HAL code -------------- */
#include "hal_platform_config.h"
/* ----------------------------------------------------- */

/* ---- Platform specific implementation --------------- */
#include "hal_plat_mapping.h"
/* ----------------------------------------------------- */

/* ---- Publicly visible Macros ---------------------------------------- */
/**
 * Simple Check to see if the specified port is within limits.
 *
 * Note: This does not do a full validation, only the upper and lower
 * limits.
 */
#define VALIDATE_PORT(Port, min, max)     (((Port < min) || (Port > max)) ? 0 : 1)

/**
 * Check to see if the specified pin is within limits for the platform
 *
 * Note: If there are any missing pins in a port, this will not be
 * considered in this check.
 */
#define VALIDATE_PIN(Pin, min, max)       (((Pin < min) || (Pin > max)) ? 0 : 1)

/**
 * Check if a specific bit in a value is set or not
 *
 * Returns a 0 if the bit is not set, and a 1 if the bit is set
 */
#define CHECK_BIT(val, pos)     (!!((1 << (pos)) & val))

/* ---- Publicly visible Variables and Constants ----------------------- */

/* ---- Publicly visible Functions ------------------------------------- */


#endif /* __hal_plat_base_H */

