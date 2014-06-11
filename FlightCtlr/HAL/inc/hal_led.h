/**
 ******************************************************************************
 * @file    hal_led.h
 * @author  Philippose Rajan
 * @date    06.06.2014
 * @brief   Public interface to the Hardware Abstraction Layer functionality
 *          for interacting with LEDs which are present on a target platform
 *          or evaluation board
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

#ifndef __hal_led_H
#define __hal_led_H

#include "hal_base.h"

/* ---- Publicly visible Macros ---------------------------------------- */

/* ---- Publicly visible Structs and Typedefs -------------------------- */
/**
 * @brief Primary Data Object for defining a single LED to be used within the
 * application
 *
 * Use this object type to initiate and use an LED present on the target
 * platform
 */
typedef struct HAL_LED
{
    /* ---- Internal Data - Do not use directly ---- */
    PLAT_LED_Pins led;                          /*!< LED to be addressed via this object */
    bool initOK;                                /*!< Indicate whether the initialisation was successful */
    bool inverted;                              /*!< Should the LED have inverted logic or not */
    /*---------------------------------------------- */

    /**
     * @copydoc HAL_LED_On()
     */
    void (*On)(struct HAL_LED *inst);

    /**
     * @copydoc HAL_LED_Off()
     */
    void (*Off)(struct HAL_LED *inst);

    /**
     * @copydoc HAL_LED_Toggle()
     */
    void (*Toggle)(struct HAL_LED *inst);
} HAL_LED;

/* ---- Publicly visible Variables and Constants ----------------------- */

/* ---- Publicly visible Functions ------------------------------------- */

/**
 * @brief Initiate an LED Data Object
 *
 * All LED Data Objects need to be initiated once before use.
 *
 * @param inst          Instance of the Data Object to be initiated
 * @param led           LED on the board to be accessed by this object
 * @param inverted      Use inverted logic or not for this LED
 * @return              Indicate whether the initialisation was successful or not
 */
extern HAL_Errors HAL_LED_Init(HAL_LED *inst, PLAT_LED_Pins led, bool inverted);


#endif /* __hal_led_H */

