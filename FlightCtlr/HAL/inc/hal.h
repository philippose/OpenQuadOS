/**
 ******************************************************************************
 * @file    hal.h
 * @author  Philippose Rajan
 * @date    05.06.2014
 * @brief   This header is the Interface between the Hardware Abstraction
 *          Layer and the Application Software.
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

#ifndef __hal_H
#define __hal_H

#include "hal_base.h"

/* - Include the individual elements of the Hardware Abstraction Layer - */
#include "hal_gpio.h"
#include "hal_led.h"
/* --------------------------------------------------------------------- */

/* ---- Publicly visible Macros ---------------------------------------- */

/* ---- Publicly visible Variables and Constants ----------------------- */

/* ---- Publicly visible Functions ------------------------------------- */

/**
 * @brief Initialise the entire Hardware Abstraction Layer
 *
 * This function needs to be called as early as possible from the Application
 * Software in order to initialise the entire Hardware Platform and make
 * the lower level interfaces available to the application.
 *
 * @return Indicates whether the initialisation went through successfully or not
 */
extern HAL_Errors HAL_Init(void);


#endif /* __hal_H */

