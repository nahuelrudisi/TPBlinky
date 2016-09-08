//	TABLA DE VERDAD Y SECUENCIA EN QUE ENCIENDEN LOS LEDS
//	R	G	B
//	0	0	0
//	0	0	1
//	0	1	1
//	1	1	1
//	1	1	0
//	1	0	0
//	1	0	1
//	0	1	0

#include "bsp/bsp.h"

#define multiplicador 1000000

int main(void)
{
	int i;
	float adc[5],menor,calculo;
	uint32_t potenciometro = 0;
	uint32_t valor_ROJO = 0, valor_VERDE = 0, valor_AZUL = 0;
	BSP_Init();

	while (1)
	{
		for(i=0;i<=5;i++)
		{
			adc[i] = BSP_GetBrightness();
			if ((i == 0) || (adc[i] < menor))
				menor = adc[i];
		}
		menor = menor * multiplicador;
		potenciometro = (uint32_t) menor;

		if(potenciometro <= 14285714)
		{
			calculo = 0.000007 * potenciometro;
			valor_ROJO  = 0;
			valor_VERDE = 0;
			valor_AZUL  = (uint32_t) calculo;
		}

		if((potenciometro > 14285714) && (potenciometro <= 28571428))
		{
			calculo = 0.000007 * potenciometro - 100;
			valor_ROJO  = 0;
			valor_VERDE = (uint32_t) calculo;
			valor_AZUL  = 100;
		}

		if((potenciometro > 28571428) && (potenciometro <= 42857142))
		{
			calculo = 0.000007 * potenciometro - 200;
			valor_ROJO  = (uint32_t) calculo;
			valor_VERDE = 100;
			valor_AZUL  = 100;
		}

		if((potenciometro > 42857142) && (potenciometro <= 57142857))
		{
			calculo = -0.000007 * potenciometro + 400;
			valor_ROJO  = 100;
			valor_VERDE = 100;
			valor_AZUL  = (uint32_t) calculo;
		}

		if((potenciometro > 57142857) && (potenciometro <= 71428571))
		{
			calculo = -0.000007 * potenciometro + 500;
			valor_ROJO  = 100;
			valor_VERDE = (uint32_t) calculo;
			valor_AZUL  = 0;
		}

		if((potenciometro > 71428571) && (potenciometro <= 85714286))
		{
			calculo = 0.000007 * potenciometro - 500;
			valor_ROJO  = 100;
			valor_VERDE = 0;
			valor_AZUL  = (uint32_t) calculo;
		}

		if((potenciometro > 85714286) && (potenciometro <= 100000000))
		{
			calculo = -0.000007 * potenciometro + 700;
			valor_ROJO  = (uint32_t) calculo;
			calculo = 0.000007 * potenciometro - 600;
			valor_VERDE = (uint32_t) calculo;
			calculo = -0.000007 * potenciometro + 700;
			valor_AZUL  = (uint32_t) calculo;
		}

		RGB_PWM(RGB_AZUL, valor_AZUL);
		RGB_PWM(RGB_ROJO, valor_ROJO);
		RGB_PWM(RGB_VERDE, valor_VERDE);
	}
}


