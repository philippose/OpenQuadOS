/**
 ******************************************************************************
 * @file    hal.c
 * @author  Philippose Rajan
 * @date    05.06.2014
 * @brief   Implementation of the Primary Interface to the Hardware Abstraction
 *          Layer from the Application side.
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
HAL_Errors HAL_Init(void);

/* ---- File-scope variables ---------------------------- */

/* ---- File-scope functions ---------------------------- */

/* ------------------------------------------------------ */

HAL_Errors HAL_Init(void)
{
    /* Initialise the Platform Specific Layer of the Hardware Abstraction Layer */
    HAL_Plat_Init();

    return HAL_OK;
}


