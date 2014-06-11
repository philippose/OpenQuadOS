/**
 ******************************************************************************
 * @file    hal_platform_config.h
 * @author  Philippose Rajan
 * @date    04.06.2014
 * @brief   Configuration of the Platform Specific Hardware Abstraction Layer
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

#ifndef __hal_platform_config_H
#define __hal_platform_config_H

/* ---- Publicly visible Macros ---------------------------------------- */

/* ----------------------------------------------------------------- */
/**
 * Define the Platform to be used on the Hardware Level
 */
#define USE_STM32F3Discovery
/* ----------------------------------------------------------------- */

/*
 * Uncomment all the features required by the Application, and
 * Comment out all the features not required.
 *
 * Note: Based on the Settings here, the ports available for GPIO or
 * other alternate functions will vary!
 */

/**
 * Enable / Disable the SPI-1 Subsystem (if available in the Platform)
 */
#define NEED_SPI_1

/**
 * Enable / Disable the SPI-2 Subsystem (if available in the Platform)
 */
// #define NEED_SPI_2

/**
 * Enable / Disable the SPI-3 Subsystem (if available in the Platform)
 */
// #define NEED_SPI_3

/**
 * Enable / Disable the I2C-1 Subsystem (if available in the Platform)
 */
#define NEED_I2C_1

/**
 * Enable / Disable the I2C-2 Subsystem (if available in the Platform)
 */
// #define NEED_I2C_2

/**
 * Enable / Disable the User USB Subsystem (if available in the Platform)
 */
#define NEED_USB_USER

/**
 * Enable / Disable the CAN Bus Subsystem (if available in the Platform)
 */
// #define NEED_CAN_BUS

/**
 * Enable / Disable the Programmable Voltage Detector (if available)
 */
// #define NEED_PVD


/**
 * These are the basic Error codes to be used by the HAL
 * and the lower level Platform specific code
 */
typedef enum HAL_Errors
{
    HAL_OK              = 0,//!< HAL_OK
    HAL_INVALID_CFG     = 1,//!< HAL_INVALID_CFG
    HAL_INVALID_PIN     = 2,//!< HAL_INVALID_PIN
    HAL_INVALID_PORT    = 3,//!< HAL_INVALID_PORT
    HAL_PIN_RESERVED    = 4,//!< HAL_PIN_RESERVED
    HAL_PORT_RESERVED   = 5,//!< HAL_PORT_RESERVED
} HAL_Errors;


/* ---- Publicly visible Variables and Constants ----------------------- */

/* ---- Publicly visible Functions ------------------------------------- */


#endif /* __hal_platform_config_H */

