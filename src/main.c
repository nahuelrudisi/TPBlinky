#include "bsp/bsp.h"

int main(void)
{
	BSP_Init();

	while (1)
	{
		RGB_PWM(RGB_ROJO,100);
		RGB_PWM(RGB_VERDE,100);
		RGB_PWM(RGB_AZUL,0);
	}
}


