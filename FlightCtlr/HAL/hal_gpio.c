/**
 ******************************************************************************
 * @file    hal_gpio.c
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
#include "hal_base.h"
#include "hal_gpio.h"

/* ---- File-scope typedefs ----------------------------- */

/* ---- File-scope defines ------------------------------ */
#define DEF_GPIO_MODE           HAL_GPIO_Input
#define DEF_GPIO_PUPD           HAL_GPIO_PullUp
#define DEF_GPIO_OUTTYPE        HAL_GPIO_PushPull
#define DEF_GPIO_SPEED          HAL_GPIO_LowSpeed


/* ---- File-scope macros ------------------------------- */

/* ---- Extern visible variables ------------------------ */

/* ---- Extern visible functions ------------------------ */
HAL_Errors HAL_GPIO_Pin_Init(HAL_GPIO_Pin *gpio_pin, HAL_GPIO_Ports port, uint8_t pin);

/* ---- File-scope variables ---------------------------- */

/* ---- File-scope functions ---------------------------- */

/**
 * @brief Configure the GPIO with the default configuration set
 *
 * The default configuration is defined by the following define
 * macros:
 *
 * #DEF_GPIO_MODE, #DEF_GPIO_PUPD, #DEF_GPIO_OUTTYPE, #DEF_GPIO_SPEED
 *
 * @param inst  Pointer to the GPIO object to be configured
 */
static void Def_Config(struct HAL_GPIO_Pin *inst);

/**
 * @brief Configure a GPIO object with the given settings
 *
 * Use this GPIO configuration function when the GPIO needs to be
 * configured with settings different from that of the default
 * settings (see: Def_Config() )
 *
 * @param inst   Pointer to the GPIO object to be configured
 * @param mode   Mode the GPIO should be configured in as defined by #HAL_GPIO_Modes
 * @param pupd   Pull-Up / Pull-Down specification (defined in #HAL_GPIO_PuPd)
 * @param oType  Output type specification (defined in #HAL_GPIO_OutType)
 * @param speed  GPIO Speed (defined in #HAL_GPIO_Speed)
 * @return       Indicates whether the configuration was successful or not
 */
static HAL_Errors Config(struct HAL_GPIO_Pin *inst, HAL_GPIO_Modes mode, HAL_GPIO_PuPd pupd, HAL_GPIO_OutType oType, HAL_GPIO_Speed speed);

/**
 * @brief Write a value to a specific GPIO object
 *
 * Set or Reset a GPIO pin by using this function
 *
 * @param inst      Pointer to the GPIO object (basically a pointer to self)
 * @param newValue  New value to set the GPIO to (1 or 0)
 */
static void WritePin(struct HAL_GPIO_Pin *inst, uint8_t newValue);

/**
 * @brief Read the state of a GPIO object
 *
 * For GPIOs configured as inputs, this function returns the current state
 * of the pin. For GPIOs ocnfigured as outputs, this function returns the
 * last value written to the pin
 *
 * @param inst      Pointer to the GPIO object (basically a pointer to self)
 * @return          Current value of the GPIO pin
 */
static uint8_t ReadPin(struct HAL_GPIO_Pin *inst);
/* ------------------------------------------------------ */

HAL_Errors HAL_GPIO_Pin_Init(HAL_GPIO_Pin *gpio_pin, HAL_GPIO_Ports port, uint8_t pin)
{
    if(!gpio_pin) return HAL_INVALID_CFG;

    gpio_pin->initOK = false;

    if((port < HAL_GPIO_Min) || (port > HAL_GPIO_Max)) return HAL_INVALID_PORT;
    if((pin < 0) || (pin > PLAT_PORT_MAX_PINS)) return HAL_INVALID_PIN;

    if(HAL_Plat_isGPIOPinReserved(port, pin)) return HAL_PIN_RESERVED;

    gpio_pin->port = port;
    gpio_pin->pin = pin;

    gpio_pin->initOK = true;
    gpio_pin->isConfigured = false;
    gpio_pin->isInput = true;

    gpio_pin->Def_Config = Def_Config;
    gpio_pin->Config = Config;
    gpio_pin->WritePin = WritePin;
    gpio_pin->ReadPin = ReadPin;

    return HAL_OK;
}



void Def_Config(struct HAL_GPIO_Pin *inst)
{
    if(!inst) return;

    HAL_Errors result = HAL_OK;

    if(inst->initOK)
    {
        result = HAL_Plat_configGPIO(inst->port, inst->pin, DEF_GPIO_MODE, DEF_GPIO_PUPD, DEF_GPIO_OUTTYPE, DEF_GPIO_SPEED);

        if(result == HAL_OK)
        {
            inst->isConfigured = true;
            inst->isInput = true;
        }
        else
        {
            inst->isConfigured = false;
            inst->isInput = true;
        }
    }
}



HAL_Errors Config(struct HAL_GPIO_Pin *inst, HAL_GPIO_Modes mode, HAL_GPIO_PuPd pupd, HAL_GPIO_OutType oType, HAL_GPIO_Speed speed)
{
    if(!inst) return HAL_INVALID_CFG;
    if((mode < HAL_GPIO_Mode_Min) || (mode > HAL_GPIO_Mode_Max)) return HAL_INVALID_CFG;
    if((pupd < HAL_GPIO_PuPd_Min) || (pupd > HAL_GPIO_PuPd_Max)) return HAL_INVALID_CFG;
    if((oType < HAL_GPIO_OutType_Min) || (oType > HAL_GPIO_OutType_Max)) return HAL_INVALID_CFG;
    if((speed < HAL_GPIO_Speed_Min) || (speed > HAL_GPIO_Speed_Max)) return HAL_INVALID_CFG;

    if(!(inst->initOK)) return HAL_INVALID_CFG;

    HAL_Errors result = HAL_OK;

    result = HAL_Plat_configGPIO(inst->port, inst->pin, mode, pupd, oType, speed);

    if(result == HAL_OK)
    {
        inst->isConfigured = true;
        inst->isInput = (mode == HAL_GPIO_Input);
    }
    else
    {
        inst->isConfigured = false;
        inst->isInput = true;
    }

    return result;
}



void WritePin(struct HAL_GPIO_Pin *inst, uint8_t newValue)
{
    if(!inst) return;
    if(!(inst->isConfigured)) return;
    if(inst->isInput) return;

    HAL_Plat_writeGPIOPin(inst->port, inst->pin, newValue);
}



uint8_t ReadPin(struct HAL_GPIO_Pin *inst)
{
    uint8_t pinValue = 0;

    if(!inst) return pinValue;
    if(!(inst->isConfigured)) return pinValue;
    if(!(inst->isInput)) return pinValue;

    pinValue = HAL_Plat_readGPIOPin(inst->port, inst->pin);

    return pinValue;
}
