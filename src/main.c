#include "bsp/bsp.h"

void APP_1ms(void);

uint8_t brightness = 0;		// Brillo
uint16_t counter = 0;
uint8_t color = 1;
uint8_t cambio = 0;

int main(void) {

	BSP_Init();

//	led_setBright(RGB_RED, 100);
//	led_setBright(RGB_GREEN, 0);
//	led_setBright(RGB_BLUE, 0);

	BSP_Apagar(RGB_RED);
	BSP_Apagar(RGB_GREEN);
	BSP_Encender(RGB_BLUE);

	while (1)
	{

/*		if(cambio == 1)
		{
			cambio = 2;
			if(Get_SW_State() == 0)	// Lee Boton
			{
				if (brightness < 50)
				{
					brightness ++;
				}
				else
				{
					color++;
					brightness = 0;
				}
			}
			else
			{
				if (brightness > 0)
					brightness --;
				else
				{
					color--;
					brightness = 50;
				}
			}
		}

		if(cambio == 2)
		{
			switch(color)
			{
				case 0:
						color = 4;
						led_setBright(RGB_RED, 50);
						led_setBright(RGB_GREEN, 50);
						led_setBright(RGB_BLUE, 50);
				case 1:
						led_setBright(RGB_RED, brightness);
						break;
				case 2:
						led_setBright(RGB_GREEN, brightness);
						break;
				case 3:
						led_setBright(RGB_BLUE, brightness);
						break;
				case 5:
						color=1;
						led_setBright(RGB_RED, 0);
						led_setBright(RGB_GREEN, 0);
						led_setBright(RGB_BLUE, 0);
				default:
						break;
			}
			cambio = 0;
		}
	}
	*/
}
}

void APP_1ms(void)
{
	if((counter == 10)&&(cambio == 0))
	{
		cambio  = 1;
		counter = 0;
	}
	counter++;
}


/*
int main(void)
{
	int bandera=0;
	BSP_Init_RGB();
	BSP_Init_ADC();

	while (1)
	{
		if(bandera == 0)
		{
			bandera = 1;
			BSP_Encender(RGB_GREEN);
			BSP_Apagar(RGB_RED);
			BSP_Apagar(RGB_BLUE);
		}
	}
}
*/

