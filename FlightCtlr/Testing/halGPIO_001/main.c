/**
 ******************************************************************************
 * @file    main.c
 * @author  Philippose Rajan
 * @date    05.06.2014
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
#include "hal.h"

/* ---- File-scope typedefs ----------------------------- */

/* ---- File-scope defines ------------------------------ */

/* ---- File-scope macros ------------------------------- */

/* ---- Extern visible variables ------------------------ */

/* ---- Extern visible functions ------------------------ */

/* ---- File-scope variables ---------------------------- */

/* ---- File-scope functions ---------------------------- */

/* ------------------------------------------------------ */

int main(void)
{
    uint16_t *testArr;

    HAL_Errors result;
    HAL_GPIO_Pin tstGPIO_01;

    HAL_Init();

    result = HAL_GPIO_Pin_Init(&tstGPIO_01, HAL_GPIOE, 9);

    if(result != HAL_OK)
    {
        while(1)
        {}
    }

    result = tstGPIO_01.Config(&tstGPIO_01, HAL_GPIO_Output, HAL_GPIO_PullUp, HAL_GPIO_PushPull, HAL_GPIO_HighSpeed);

    if(result != HAL_OK)
    {
        while(1)
        {}
    }

    while(1)
    {
        tstGPIO_01.WritePin(&tstGPIO_01, 1);
        for(int i = 0; i < (1000000/2); i++);
        tstGPIO_01.WritePin(&tstGPIO_01, 0);
        for(int i = 0; i < (1000000/2); i++);
    }
}

