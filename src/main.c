#include "bsp/bsp.h"

int main(void)
{
	int bandera;
	float potenciometro;
	uint8_t valor_ROJO = 0, valor_VERDE = 0, valor_AZUL = 0;
	BSP_Init();

	while (1)
	{
		potenciometro = BSP_GetBrightness();
		if(potenciometro <= 14,28571429)
			bandera = 0;
		if((potenciometro > 14,28571429) && (potenciometro <= 28,57142858))
			bandera = 1;
		if((potenciometro > 28,57142858) && (potenciometro <= 42,85714287))
			bandera = 2;
		if((potenciometro > 42,85714287) && (potenciometro <= 57,14285716))
			bandera = 3;
		if((potenciometro > 57,14285716) && (potenciometro <= 71,42857145))
			bandera = 4;
		if((potenciometro > 71,42857145) && (potenciometro <= 85,71428574))
			bandera = 5;
		if((potenciometro > 85,71428574) && (potenciometro <= 100))
			bandera = 6;

		switch(bandera)
		{
			case 0:
					valor_ROJO = 0;
					valor_VERDE = 0;
					valor_AZUL = (uint8_t) 6,9999999979 * potenciometro;
					break;
			case 1:
					valor_ROJO = 0;
					valor_VERDE = (uint8_t) 6,9999999979 * potenciometro - 100;
					valor_AZUL = 0;
					break;
			case 2:
					valor_ROJO = 0;
					valor_VERDE = 100;
					valor_AZUL = (uint8_t) 6,9999999979 * potenciometro - 200;
					break;
			case 3:
					valor_ROJO = (uint8_t) 6,9999999979 * potenciometro - 300;
					valor_VERDE = 0;
					valor_AZUL = 0;
					break;
			case 4:
					valor_ROJO = 100;
					valor_VERDE = 0;
					valor_AZUL = (uint8_t) 6,9999999979 * potenciometro - 400;
					break;
			case 5:
					valor_ROJO = 100;
					valor_VERDE = (uint8_t) 6,9999999979 * potenciometro - 500;
					valor_AZUL = 0;
					break;
			case 6:
					valor_ROJO = 100;
					valor_VERDE = 100;
					valor_AZUL = (uint8_t) 6,9999999979 * potenciometro - 600;
					break;
			default:
					break;
		}
		 RGB_PWM(RGB_ROJO, valor_ROJO);
		 RGB_PWM(RGB_VERDE, valor_VERDE);
		 RGB_PWM(RGB_AZUL, valor_AZUL);
	}
}


