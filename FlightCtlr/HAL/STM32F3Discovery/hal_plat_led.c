/**
 ******************************************************************************
 * @file    hal_plat_led.c
 * @author  Philippose Rajan
 * @date    06.06.2014
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

/* ---- Includes ---------------------------------------- */
#include "hal_plat_base.h"

/* ---- File-scope typedefs ----------------------------- */
#define LED_GPIO_PORT          GPIOE
#define LED_GPIO_RCC           RCC_AHBPeriph_GPIOE

/* ---- File-scope defines ------------------------------ */

/* ---- File-scope macros ------------------------------- */

/* ---- Extern visible variables ------------------------ */

/**
 * Constant mapping between the LED definitions and the
 * actual physical ports to which they are connected on
 * the board
 */
static const uint16_t ledGPIOMapping[PLAT_LED_Max + 1] =
                                    {GPIO_Pin_9,
                                     GPIO_Pin_10,
                                     GPIO_Pin_11,
                                     GPIO_Pin_12,
                                     GPIO_Pin_13,
                                     GPIO_Pin_14,
                                     GPIO_Pin_15,
                                     GPIO_Pin_8};

/* ---- Extern visible functions ------------------------ */
HAL_Errors HAL_Plat_configLED(PLAT_LED_Pins led, bool inverted);

void HAL_Plat_setLEDPin(PLAT_LED_Pins led);

void HAL_Plat_resetLEDPin(PLAT_LED_Pins led);

void HAL_Plat_toggleLEDPin(PLAT_LED_Pins led);

/* ---- File-scope variables ---------------------------- */

/* ---- File-scope functions ---------------------------- */

/* ------------------------------------------------------ */
HAL_Errors HAL_Plat_configLED(PLAT_LED_Pins led, bool inverted)
{
    if((led < PLAT_LED_Min) || (led > PLAT_LED_Max)) return HAL_INVALID_PIN;

    GPIO_InitTypeDef ledGPIOStruct;

    ledGPIOStruct.GPIO_Pin = ledGPIOMapping[led];

    ledGPIOStruct.GPIO_Mode = GPIO_Mode_OUT;
    ledGPIOStruct.GPIO_OType = GPIO_OType_PP;
    ledGPIOStruct.GPIO_PuPd = GPIO_PuPd_UP;
    ledGPIOStruct.GPIO_Speed = GPIO_Speed_2MHz;

    RCC_AHBPeriphClockCmd(LED_GPIO_RCC, ENABLE);
    GPIO_Init(LED_GPIO_PORT, &ledGPIOStruct);

    return HAL_OK;
}



void HAL_Plat_setLEDPin(PLAT_LED_Pins led)
{
    LED_GPIO_PORT->BSRR = ledGPIOMapping[led];
}



void HAL_Plat_resetLEDPin(PLAT_LED_Pins led)
{
    LED_GPIO_PORT->BRR = ledGPIOMapping[led];
}



void HAL_Plat_toggleLEDPin(PLAT_LED_Pins led)
{
    LED_GPIO_PORT->ODR ^= ledGPIOMapping[led];
}

