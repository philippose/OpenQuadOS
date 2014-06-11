/**
 ******************************************************************************
 * @file    hal_gpio.h
 * @author  Philippose Rajan
 * @date    05.06.2014
 * @brief   Definitions for the GPIO Subsystem of the Hardware Abstraction Layer
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

#ifndef __hal_gpio_H
#define __hal_gpio_H

#include "hal_base.h"

/* ---- Publicly visible Macros ---------------------------------------- */

/* ---- Publicly visible Structs and Typedefs -------------------------- */
/**
 * Available Ports for GPIO
 */
typedef enum
{
    HAL_GPIO_Min = 0x0,
    HAL_GPIOA    = 0x0,
    HAL_GPIOB    = 0x1,
    HAL_GPIOC    = 0x2,
    HAL_GPIOD    = 0x3,
    HAL_GPIOE    = 0x4,
    HAL_GPIOF    = 0x5,
    HAL_GPIO_Max = 0x5
} HAL_GPIO_Ports;


/**
 * All the modes a given General Purpose IO Pin can be switched to
 */
typedef enum
{
    HAL_GPIO_Mode_Min = 0x0, //!< GPIO_Mode_Min
    HAL_GPIO_Input    = 0x0,   //!< GPIO_Input
    HAL_GPIO_Output = 0x1,   //!< GPIO_Output
    HAL_GPIO_Mode_Max = 0x1  //!< GPIO_Mode_Max
} HAL_GPIO_Modes;


/**
 * Specification of the Pull-Up / Pull-Down characteristics of the pin
 */
typedef enum
{
    HAL_GPIO_PuPd_Min = 0x0,//!< GPIO_PuPd_Min
    HAL_GPIO_Floating = 0x0,//!< GPIO_Floating
    HAL_GPIO_PullUp = 0x1,  //!< GPIO_PullUp
    HAL_GPIO_PullDown = 0x2,//!< GPIO_PullDown
    HAL_GPIO_PuPd_Max = 0x2 //!< GPIO_PuPd_Max
} HAL_GPIO_PuPd;


/**
 * Possible output types for the GPIO pin. This setting is not
 * used when the pin is in Input mode
 */
typedef enum
{
    HAL_GPIO_OutType_Min = 0x0,//!< GPIO_OutType_Min
    HAL_GPIO_PushPull = 0x0,   //!< GPIO_PushPull
    HAL_GPIO_OpenDrain = 0x1,  //!< GPIO_OpenDrain
    HAL_GPIO_OutType_Max = 0x1 //!< GPIO_OutType_Max
} HAL_GPIO_OutType;


/**
 * Possible speeds which can be setup for a give GPIO pin
 */
typedef enum
{
    HAL_GPIO_Speed_Min = 0x0,  //!< GPIO_Speed_Min
    HAL_GPIO_LowSpeed = 0x0,   //!< GPIO_LowSpeed
    HAL_GPIO_MediumSpeed = 0x1,//!< GPIO_MediumSpeed
    HAL_GPIO_HighSpeed = 0x2,  //!< GPIO_HighSpeed
    HAL_GPIO_Speed_Max = 0x2   //!< GPIO_Speed_Max
} HAL_GPIO_Speed;



/**
 * Basic Object for a General Purpose Input Output Pin
 * at the Hardware Abstraction Level
 *
 * This object is used to create and interact with simple
 * GPIO pins and provides methods for setting the pin (if
 * it is an output) or reading the pin (for input pins)
 *
 * It is not expected to directly access the individual
 * variables within the structure. All access should be
 * through the given functions.
 */
typedef struct HAL_GPIO_Pin
{
    HAL_GPIO_Ports port;
    uint8_t pin;

    bool initOK;
    bool isConfigured;
    bool isInput;

    void (*Def_Config)(struct HAL_GPIO_Pin *inst);
    HAL_Errors (*Config)(struct HAL_GPIO_Pin *inst, HAL_GPIO_Modes mode, HAL_GPIO_PuPd pupd, HAL_GPIO_OutType oType, HAL_GPIO_Speed speed);

    void (*WritePin)(struct HAL_GPIO_Pin *inst, uint8_t newValue);
    uint8_t (*ReadPin)(struct HAL_GPIO_Pin *inst);
} HAL_GPIO_Pin;

/* ---- Publicly visible Variables and Constants ----------------------- */

/* ---- Publicly visible Functions ------------------------------------- */

/**
 * @brief Initialise a basic GPIO pin on a specific port
 *
 * This function needs to be called before any other access to the
 * object is made! Using the object without calling this initialisation
 * function will lead to run-time errors.
 *
 * @param gpio_pin      Pointer to the GPIO Object to be initialised
 * @param port          Port on the Controller to which the pin belongs
 * @param pin           Specific pin in the port to be used
 * @return              Indicates whether the Initialisation was successful
 */
extern HAL_Errors HAL_GPIO_Pin_Init(HAL_GPIO_Pin *gpio_pin, HAL_GPIO_Ports port, uint8_t pin);

#endif /* __hal_gpio_H */

