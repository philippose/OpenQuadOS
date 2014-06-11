/**
 ******************************************************************************
 * @file    hal_plat_gpio.h
 * @author  Philippose Rajan
 * @date    03.06.2014
 * @brief   Platform specific implementation for the Hardware GPIOs
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

#ifndef __hal_plat_gpio_H
#define __hal_plat_gpio_H

#include "hal_plat_base.h"
#include "hal_gpio.h"

/* ---- Publicly visible Macros ---------------------------------------- */

/* ---- Publicly visible Structs and Typedefs -------------------------- */

/* ---- Publicly visible Variables and Constants ----------------------- */

/* ---- Publicly visible Functions ------------------------------------- */
extern HAL_Errors HAL_Plat_configGPIO(HAL_GPIO_Ports port, uint8_t pin, HAL_GPIO_Modes mode, HAL_GPIO_PuPd pupd, HAL_GPIO_OutType oType, HAL_GPIO_Speed speed);

extern bool HAL_Plat_isGPIOPinReserved(HAL_GPIO_Ports port, uint8_t pin);

extern void HAL_Plat_writeGPIOPin(HAL_GPIO_Ports port, uint8_t pin, uint8_t newValue);

extern uint8_t HAL_Plat_readGPIOPin(HAL_GPIO_Ports port, uint8_t pin);

#endif /* __hal_plat_gpio_H */

