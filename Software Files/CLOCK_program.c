
#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "CLOCK_interface.h"
#include "CLOCK_config.h"



void MCLOCK_voidDelayMS(int ms){
	register int Ticks = (CLOCK_SYSTEM_FREQUENCY/7000)*ms - 10;
	while(Ticks--)
		__asm__ volatile("NOP");
}

u32 MCLOCK_u32GetSystemClock(void){
	return CLOCK_SYSTEM_FREQUENCY;
}
void my_delay_ms(unsigned int delay)
{
	unsigned int i;
	for (i=0; i<((int)(delay/10)); i++)
	{
		//_delay_ms(10);
		MCLOCK_voidDelayMS(10);
	}
	
}