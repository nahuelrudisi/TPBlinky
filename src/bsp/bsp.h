/*
 * bsp.h
 *
 *  Created on: 11 de ago. de 2016
 *      Author: LCSR-AF
 */

#ifndef BSP_BSP_H_
#define BSP_BSP_H_

#include "stdint.h"

void BSP_Init(void);

//void led_setBright(uint8_t led, uint8_t value);

uint32_t Get_SW_State(void);

void led_setBright(uint8_t led, uint8_t value);


// RGB
#define RGB_RED	  (uint16_t)0x0001U	// GPIO_PIN_0 no pongo asi porque sino tengo que poner las librerias del STM
#define RGB_GREEN (uint16_t)0x0002U	// GPIO_PIN_1 y no voy a poder independizar el main del bsp, porque el main.c
#define RGB_BLUE  (uint16_t)0x0010U	// GPIO_PIN_4 ve al bsp.h pero no al bsp.c


// POTENCIOMETRO
#define POTENCIOMETRO GPIO_PIN_2

void BSP_Init(void);
//void BSP_Init_RGB(void);
//void BSP_Init_ADC(void);
void BSP_Encender(uint16_t LED);
void BSP_Apagar(uint16_t LED);

#endif /* BSP_BSP_H_ */
