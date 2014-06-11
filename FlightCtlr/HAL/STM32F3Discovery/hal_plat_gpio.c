/**
 ******************************************************************************
 * @file    hal_plat_gpio.c
 * @author  Philippose Rajan
 * @date    03.06.2014
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
#include "hal_plat_gpio.h"

/* ---- File-scope typedefs ----------------------------- */
#define MAX_PORTS           (6)

/* ---- File-scope defines ------------------------------ */

/* ---- File-scope macros ------------------------------- */

/* ---- Extern visible variables ------------------------ */

/* ---- Extern visible functions ------------------------ */
HAL_Errors HAL_Plat_configGPIO(HAL_GPIO_Ports port, uint8_t pin, HAL_GPIO_Modes mode, HAL_GPIO_PuPd pupd, HAL_GPIO_OutType oType, HAL_GPIO_Speed speed);

bool HAL_Plat_isGPIOPinReserved(HAL_GPIO_Ports port, uint8_t pin);

void HAL_Plat_writeGPIOPin(HAL_GPIO_Ports port, uint8_t pin, uint8_t newValue);

uint8_t HAL_Plat_readGPIOPin(HAL_GPIO_Ports port, uint8_t pin);

/* ---- File-scope variables ---------------------------- */
/**
 * @brief GPIO Pins on the board that are already reserved for
 *        other purposes
 *
 * Refer to the STM32F3Discovery Manual for the reserved
 * pins in each port
 */
static const uint16_t reservedPins[MAX_PORTS] =
                      {
                          0x78e1, /* GPIOA: 0111100011100001 */
                          0x00C0, /* GPIOB: 0000000011000000 */
                          0x0030, /* GPIOC: 0000000000110000 */
                          0x0000, /* GPIOD: 0000000000000000 */
                          0xff3f, /* GPIOE: 1111111100111111 */
                          0xf9a9, /* GPIOF: 1111100110101001 */
                      };

/* ---- File-scope functions ---------------------------- */

/* ------------------------------------------------------ */

HAL_Errors HAL_Plat_configGPIO(HAL_GPIO_Ports port, uint8_t pin, HAL_GPIO_Modes mode, HAL_GPIO_PuPd pupd, HAL_GPIO_OutType oType, HAL_GPIO_Speed speed)
{
    HAL_Errors result = HAL_OK;

    GPIO_InitTypeDef gpioStruct;

    /* Fill the structure with default values */
    GPIO_StructInit(&gpioStruct);

    /* Now fill up the structure based on the inputs to the function */
    gpioStruct.GPIO_Pin = (uint32_t)(1 << (pin));
    gpioStruct.GPIO_Mode = (GPIOMode_TypeDef)mode;
    gpioStruct.GPIO_PuPd = (GPIOPuPd_TypeDef)pupd;
    gpioStruct.GPIO_OType = (GPIOOType_TypeDef)oType;

    /* The speed is not a direct mapping of the platform dependent values */
    switch(speed)
    {
        case(HAL_GPIO_LowSpeed):
            gpioStruct.GPIO_Speed = GPIO_Speed_2MHz;
            break;

        case(HAL_GPIO_MediumSpeed):
            gpioStruct.GPIO_Speed = GPIO_Speed_10MHz;
            break;

        case(HAL_GPIO_HighSpeed):
            gpioStruct.GPIO_Speed = GPIO_Speed_50MHz;
            break;

        default:
            gpioStruct.GPIO_Speed = GPIO_Speed_2MHz;
    }


    /* Initialise the GPIO and at the same time enable the
     * clock
     *
     * This would also work:
     * GPIO_Init(AHB2PERIPH_BASE + (0x0400 * port), &gpioStruct);
     *
     * NOTE: THE PERIPHERAL CLOCK HAS TO BE ENABLED BEFORE MAKING
     * THE CALL TO THE INIT ROUTINE (IF NOT ALREADY ENABLED) !!!!
     */
    switch(port)
    {
        case HAL_GPIOA:
            RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);
            GPIO_Init(GPIOA, &gpioStruct);
            break;

        case HAL_GPIOB:
            RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB, ENABLE);
            GPIO_Init(GPIOB, &gpioStruct);
            break;

        case HAL_GPIOC:
            RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOC, ENABLE);
            GPIO_Init(GPIOC, &gpioStruct);
            break;

        case HAL_GPIOD:
            RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOD, ENABLE);
            GPIO_Init(GPIOD, &gpioStruct);
            break;

        case HAL_GPIOE:
            RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOE, ENABLE);
            GPIO_Init(GPIOE, &gpioStruct);
            break;

        case HAL_GPIOF:
            RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOF, ENABLE);
            GPIO_Init(GPIOF, &gpioStruct);
            break;

        default:
            result = HAL_INVALID_PORT;
    }

    return result;
}



void HAL_Plat_writeGPIOPin(HAL_GPIO_Ports port, uint8_t pin, uint8_t newValue)
{
    GPIO_TypeDef *currPort;

    switch(port)
    {
        case HAL_GPIOA:
            currPort = GPIOA;
            break;

        case HAL_GPIOB:
            currPort = GPIOB;
            break;

        case HAL_GPIOC:
            currPort = GPIOC;
            break;

        case HAL_GPIOD:
            currPort = GPIOD;
            break;

        case HAL_GPIOE:
            currPort = GPIOE;
            break;

        case HAL_GPIOF:
            currPort = GPIOF;
            break;

        default:
            currPort = NULL;
    }

    if(currPort != NULL)
    {
        if(newValue)
        {
            currPort->BSRR = (1 << (pin));
        }
        else
        {
            currPort->BRR = (1 << (pin));
        }
    }
}



uint8_t HAL_Plat_readGPIOPin(HAL_GPIO_Ports port, uint8_t pin)
{
    uint8_t pinValue = 0;

    GPIO_TypeDef *currPort;

    switch(port)
    {
        case HAL_GPIOA:
            currPort = GPIOA;
            break;

        case HAL_GPIOB:
            currPort = GPIOB;
            break;

        case HAL_GPIOC:
            currPort = GPIOC;
            break;

        case HAL_GPIOD:
            currPort = GPIOD;
            break;

        case HAL_GPIOE:
            currPort = GPIOE;
            break;

        case HAL_GPIOF:
            currPort = GPIOF;
            break;

        default:
            currPort = NULL;
    }

    if(currPort != NULL)
    {
        pinValue = CHECK_BIT(currPort->IDR, pin);
    }

    return pinValue;
}



bool HAL_Plat_isGPIOPinReserved(HAL_GPIO_Ports port, uint8_t pin)
{
    bool reserved = true;

    /* Sanity checks */
    if(!VALIDATE_PORT(port, HAL_GPIO_Min, HAL_GPIO_Max)) return reserved;
    if(!VALIDATE_PIN(pin, 0, PLAT_PORT_MAX_PINS)) return reserved;

    switch(port)
    {
        case HAL_GPIOA:
            reserved = CHECK_BIT(reservedPins[0], pin);
            break;

        case HAL_GPIOB:
            reserved = CHECK_BIT(reservedPins[1], pin);
            break;

        case HAL_GPIOC:
            reserved = CHECK_BIT(reservedPins[2], pin);
            break;

        case HAL_GPIOD:
            reserved = CHECK_BIT(reservedPins[3], pin);
            break;

        case HAL_GPIOE:
            reserved = CHECK_BIT(reservedPins[4], pin);
            break;

        case HAL_GPIOF:
            reserved = CHECK_BIT(reservedPins[5], pin);
            break;

        default:
            reserved = true;
    }

    return reserved;
}


