#ifndef CLOCK_INTERFACE_H
#define CLOCK_INTERFACE_H

void MCLOCK_voidDelayMS(int ms);

unsigned long int MCLOCK_u32GetSystemClock(void);

void my_delay_ms(unsigned int delay);
#endif

