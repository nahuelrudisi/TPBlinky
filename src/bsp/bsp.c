/*
 * bsp.c
 *
 *  Created on: 11 de ago. de 2016
 *      Author: LCSR-AF
 */
#include "bsp.h"
#include "stm32f4xx.h"
#include "stm32f4_discovery.h"

extern void APP_1ms(void);

TIM_HandleTypeDef TIM2_Handle;
TIM_HandleTypeDef TIM4_Handle;


uint32_t* const leds_pwm[] = { &TIM4->CCR1, &TIM4->CCR3, &TIM4->CCR2,&TIM4->CCR4 };

void BSP_Init(void) {
	RCC_OscInitTypeDef RCC_OscInitStruct;
	RCC_ClkInitTypeDef RCC_ClkInitStruct;

	__PWR_CLK_ENABLE()
	;

	__HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

	RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
	RCC_OscInitStruct.HSEState = RCC_HSE_ON;
	RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
	RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
	RCC_OscInitStruct.PLL.PLLM = 8;
	RCC_OscInitStruct.PLL.PLLN = 336;
	RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
	RCC_OscInitStruct.PLL.PLLQ = 7;
	HAL_RCC_OscConfig(&RCC_OscInitStruct);

	RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_PCLK1
			| RCC_CLOCKTYPE_PCLK2;
	RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
	RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
	RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
	RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;
	HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5);

	__GPIOB_CLK_ENABLE()
	;

	GPIO_InitTypeDef GPIO_Init;
/*
	GPIO_Init.Mode = GPIO_MODE_AF_PP;
	GPIO_Init.Pull = GPIO_NOPULL;
	GPIO_Init.Speed = GPIO_SPEED_FAST;
	GPIO_Init.Alternate = GPIO_AF2_TIM4;				// El timer 4 es para PWM
	GPIO_Init.Pin = RGB_RED | RGB_GREEN | RGB_BLUE;		// Pines de los leds
	HAL_GPIO_Init(GPIOB, &GPIO_Init);
*/
	GPIO_Init.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_Init.Pull = GPIO_NOPULL;
	GPIO_Init.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	GPIO_Init.Pin = RGB_RED | RGB_GREEN | RGB_BLUE;		// Pines de los leds
	HAL_GPIO_Init(GPIOB, &GPIO_Init);

	__TIM2_CLK_ENABLE()
	;

	TIM2_Handle.Instance = TIM2;
	TIM2_Handle.Init.Period = 1000 - 1;
	TIM2_Handle.Init.Prescaler = 84 - 1;			// 84 MHz / 84 = 1 MHz
	TIM2_Handle.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
	TIM2_Handle.Init.CounterMode = TIM_COUNTERMODE_UP;

	HAL_TIM_Base_Init(&TIM2_Handle);
	HAL_TIM_Base_Start_IT(&TIM2_Handle);

	HAL_NVIC_SetPriority(TIM2_IRQn, 0, 1);
	HAL_NVIC_EnableIRQ(TIM2_IRQn);

	__GPIOA_CLK_ENABLE()
	;

	GPIO_InitTypeDef GPIO_Init1;
	GPIO_Init1.Mode = GPIO_MODE_INPUT;
	GPIO_Init1.Pull = GPIO_NOPULL;
	GPIO_Init1.Speed = GPIO_SPEED_FAST;
	GPIO_Init1.Pin = GPIO_PIN_0;
	HAL_GPIO_Init(GPIOA, &GPIO_Init1);		// Inicializa puerto A para usar el boton

	__TIM3_CLK_ENABLE()
	;

	TIM_MasterConfigTypeDef TIM_MasterConfig;
	TIM_OC_InitTypeDef TIM_OC_Init;

	__TIM4_CLK_ENABLE();

	TIM4_Handle.Instance = TIM4;
	TIM4_Handle.Init.Prescaler = 84 -1;
	;
	TIM4_Handle.Init.CounterMode = TIM_COUNTERMODE_UP;
	TIM4_Handle.Init.Period = 1500;
	TIM4_Handle.Init.ClockDivision = TIM_CLOCKDIVISION_DIV2;
	HAL_TIM_PWM_Init(&TIM4_Handle);

	TIM_MasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
	TIM_MasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
	HAL_TIMEx_MasterConfigSynchronization(&TIM4_Handle, &TIM_MasterConfig);

	TIM_OC_Init.OCMode = TIM_OCMODE_PWM2;
	TIM_OC_Init.Pulse = 0;
	TIM_OC_Init.OCPolarity = TIM_OCPOLARITY_LOW;	// Para que el 0 del ciclo de trabajo sea bajo
	TIM_OC_Init.OCFastMode = TIM_OCFAST_ENABLE;

	HAL_TIM_PWM_ConfigChannel(&TIM4_Handle, &TIM_OC_Init, TIM_CHANNEL_1);
	HAL_TIM_PWM_ConfigChannel(&TIM4_Handle, &TIM_OC_Init, TIM_CHANNEL_2);
	HAL_TIM_PWM_ConfigChannel(&TIM4_Handle, &TIM_OC_Init, TIM_CHANNEL_3);
	HAL_TIM_PWM_ConfigChannel(&TIM4_Handle, &TIM_OC_Init, TIM_CHANNEL_4);

	HAL_TIM_PWM_Start(&TIM4_Handle, TIM_CHANNEL_1);
	HAL_TIM_PWM_Start(&TIM4_Handle, TIM_CHANNEL_2);
	HAL_TIM_PWM_Start(&TIM4_Handle, TIM_CHANNEL_3);
	HAL_TIM_PWM_Start(&TIM4_Handle, TIM_CHANNEL_4);
}

uint32_t Get_SW_State(void) {
	return HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0);
}

void led_setBright(uint8_t led, uint8_t value) {
	*leds_pwm[led] = 1000 * value / 100;
}

void TIM2_IRQHandler(void) {

	__HAL_TIM_CLEAR_FLAG(&TIM2_Handle, TIM_FLAG_UPDATE);
	APP_1ms();
}

void BSP_Encender(uint16_t LED)
{
	HAL_GPIO_WritePin(GPIOB,LED,GPIO_PIN_RESET);	// Con Reset se enciende el led
}

void BSP_Apagar(uint16_t LED)
{
	HAL_GPIO_WritePin(GPIOB,LED,GPIO_PIN_SET);	// Con Reset se enciende el led
}


