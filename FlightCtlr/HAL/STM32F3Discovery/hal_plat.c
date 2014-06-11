/**
 ******************************************************************************
 * @file    hal_plat.c
 * @author  Philippose Rajan
 * @date    04.06.2014
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
#include "hal_plat.h"

/* ---- File-scope typedefs ----------------------------- */

/* ---- File-scope defines ------------------------------ */

/* ---- File-scope macros ------------------------------- */

/* ---- Extern visible variables ------------------------ */

/* ---- Extern visible functions ------------------------ */
HAL_Errors HAL_Plat_Init(void);

/* ---- File-scope variables ---------------------------- */

/* ---- File-scope functions ---------------------------- */
static void Base_Sys_Init(void);

/* ------------------------------------------------------ */

HAL_Errors HAL_Plat_Init(void)
{
    /*
     * Note: It is assumed that when the system gets here,
     * the Startup code for the Platform has already been
     * called from the System Reset Handler, which implies,
     * that the main clock is already setup
     */

    Base_Sys_Init();

    return (HAL_OK);
}



void Base_Sys_Init(void)
{
    /* Update the variable SystemCoreClock with the correct core clock frequency
     * (should be 72MHz for the STM32F3Discovery default setup)
     */
    SystemCoreClockUpdate();

    /* This is required for FreeRTOS (Refer: http://www.freertos.org/RTOS-Cortex-M3-M4.html) */
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);

    /* Set HCLK as the source for Systick */
    SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK);

    /* Disable all the peripheral clocks and reset the Peripherals to start with */
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2 |
                           RCC_APB1Periph_TIM3 |
                           RCC_APB1Periph_TIM4 |
                           RCC_APB1Periph_TIM6 |
                           RCC_APB1Periph_TIM7 |
                           RCC_APB1Periph_WWDG |
                           RCC_APB1Periph_SPI2 |
                           RCC_APB1Periph_SPI3 |
                           RCC_APB1Periph_USART2 |
                           RCC_APB1Periph_USART3 |
                           RCC_APB1Periph_UART4 |
                           RCC_APB1Periph_UART5 |
                           RCC_APB1Periph_I2C1 |
                           RCC_APB1Periph_I2C2 |
                           RCC_APB1Periph_USB |
                           RCC_APB1Periph_CAN1 |
                           RCC_APB1Periph_PWR |
                           RCC_APB1Periph_DAC |
                           0, DISABLE);

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1 |
                           RCC_APB2Periph_TIM8 |
                           RCC_APB2Periph_TIM15 |
                           RCC_APB2Periph_TIM16 |
                           RCC_APB2Periph_TIM17 |
                           RCC_APB2Periph_USART1 |
                           RCC_APB2Periph_SPI1 |
                           RCC_APB2Periph_SYSCFG |
                           0, DISABLE);

    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA |
                          RCC_AHBPeriph_GPIOB |
                          RCC_AHBPeriph_GPIOC |
                          RCC_AHBPeriph_GPIOD |
                          RCC_AHBPeriph_GPIOE |
                          RCC_AHBPeriph_GPIOF |
                          RCC_AHBPeriph_TS |
                          RCC_AHBPeriph_CRC |
                          RCC_AHBPeriph_FLITF |
                          RCC_AHBPeriph_SRAM |
                          RCC_AHBPeriph_DMA2 |
                          RCC_AHBPeriph_DMA1 |
                          RCC_AHBPeriph_ADC34 |
                          RCC_AHBPeriph_ADC12 |
                          0, DISABLE);


    /* Reset the SysCfg registers to default */
    SYSCFG_DeInit();


    /* Enable some essential peripherals */
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR, ENABLE);

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);

    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_SRAM, ENABLE);

    /* Keep the ST-Link Connections alive */
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);

    /* If the CAN Bus is required, the USB Interrupts need to be remapped */
#if NEED_CAN_BUS
    SYSCFG_USBInterruptLineRemapCmd(ENABLE);
#endif /* NEED_CAN_BUS */


#if NEED_PVD
    PWR_PVDCmd(ENABLE);
#endif

}

