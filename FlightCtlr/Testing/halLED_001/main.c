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
    HAL_LED led01;

    HAL_Init();

    result = HAL_LED_Init(&led01, PLAT_LED_Green_E, false);

    if(result != HAL_OK)
    {
        while(1)
        {}
    }

    while(1)
    {
        led01.On(&led01);
        for(int i = 0; i < (1000000/2); i++);
        led01.Off(&led01);
        for(int i = 0; i < (1000000/2); i++);
    }
}

