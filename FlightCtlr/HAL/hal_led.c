/**
 ******************************************************************************
 * @file    hal_led.c
 * @author  Philippose Rajan
 * @date    06.06.2014
 * @brief   Implementation of the Hardware Abstraction Layer for interacting
 *          with LEDs present on a target platform or evaluation board
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

/* ---- Includes ---------------------------------------- */
#include "hal_base.h"
#include "hal_led.h"

/* ---- File-scope typedefs ----------------------------- */

/* ---- File-scope defines ------------------------------ */

/* ---- File-scope macros ------------------------------- */

/* ---- Extern visible variables ------------------------ */

/* ---- Extern visible functions ------------------------ */
HAL_Errors HAL_LED_Init(HAL_LED *inst, PLAT_LED_Pins led, bool inverted);

/* ---- File-scope variables ---------------------------- */

/* ---- File-scope functions ---------------------------- */

/**
 * @brief Hardware Abstraction Layer method for turning on an
 *        LED
 *
 * This function is accessed by the LED Data Object once the
 * object has been initiated.
 *
 * @param inst          Pointer to the instance of the current LED Object
 */
static void HAL_LED_On(struct HAL_LED *inst);


/**
 * @brief Hardware Abstraction Layer method for turning off an
 *        LED
 *
 * This function is accessed by the LED Data Object once the
 * object has been initiated.
 *
 * @param inst          Pointer to the instance of the current LED Object
 */
static void HAL_LED_Off(struct HAL_LED *inst);


/**
 * @brief Hardware Abstraction Layer method for turning toggling the
 *        state of an LED
 *
 * This function is accessed by the LED Data Object once the
 * object has been initiated.
 *
 * @param inst          Pointer to the instance of the current LED Object
 */
static void HAL_LED_Toggle(struct HAL_LED *inst);
/* ------------------------------------------------------ */

HAL_Errors HAL_LED_Init(HAL_LED *inst, PLAT_LED_Pins led, bool inverted)
{
    /* Check if a valid pointer has been sent in */
    if(!inst) return HAL_INVALID_CFG;

    inst->initOK = false;

    /* Initialise the function pointers early on so that even if the
     * initialisation of the LED itself fails, the function pointers
     * will point to valid functions
     */
    inst->On = HAL_LED_On;
    inst->Off = HAL_LED_Off;
    inst->Toggle = HAL_LED_Toggle;

    if((led < PLAT_LED_Min) || (led > PLAT_LED_Max)) return HAL_INVALID_PIN;


    inst->led = led;
    inst->inverted = inverted;

    HAL_Errors result = HAL_OK;

    /* Call the Platform Specific initialisation of the LEDs */
    result = HAL_Plat_configLED(inst->led, inst->inverted);

    if(result == HAL_OK)
    {
        inst->initOK = true;
    }
    else
    {
        inst->initOK = false;
    }

    return result;
}



void HAL_LED_On(struct HAL_LED *inst)
{
    if(!inst) return;

    if(!(inst->initOK)) return;

    if(inst->inverted)
    {
        HAL_Plat_resetLEDPin(inst->led);
    }
    else
    {
        HAL_Plat_setLEDPin(inst->led);
    }
}



void HAL_LED_Off(struct HAL_LED *inst)
{
    if(!inst) return;

    if(!(inst->initOK)) return;

    if(inst->inverted)
    {
        HAL_Plat_setLEDPin(inst->led);
    }
    else
    {
        HAL_Plat_resetLEDPin(inst->led);
    }
}



void HAL_LED_Toggle(struct HAL_LED *inst)
{
    if(!inst) return;

    if(!(inst->initOK)) return;

    HAL_Plat_toggleLEDPin(inst->led);
}


