#include "pseudo_pwm.h"

static uint32_t on_counter = 0;
volatile uint32_t overflow_counter_on = 0;
static uint32_t off_counter = 0;
volatile uint32_t overflow_counter_off = 0;
uint32_t ticks_on;
uint32_t ticks_off;
static uint8_t	flag_on = 1;

void pseudo_callback( void )
{
	switch( flag_on )
	{
		case 0:
			if ( overflow_counter_off > 0 )
			{
				overflow_counter_off--;
			}
			else
			{
				flag_on = 1;
				overflow_counter_off = off_counter;
				Dio_WriteChannel( PF1, HIGH );
				SysTick_StartTimer( on_counter > 0 ? MAXIMUM_TICKS : ticks_on );
			}
			break;
		case 1:
			if ( overflow_counter_on > 0 )
			{
				overflow_counter_on--;
			}
			else
			{
				flag_on = 0;
				overflow_counter_on = on_counter;
				Dio_WriteChannel( PF1, LOW );
				SysTick_StartTimer( off_counter > 0 ? MAXIMUM_TICKS : ticks_off );
			}
			break;
	}
}

void pseudoPWM_init( float t_on, float t_off )
{
	uint32_t ticks = 0;
	SysTick_StopTimer();
	
	on_counter = 0;
	off_counter = 0;
	
	SysTick_RegisterCallback(pseudo_callback);
	switch( SYSTICK_CLOCK_SRC )
	{
		case PIOSC:
			ticks_on = ( t_on * PIOSC_FREQUENCY );
			ticks_off = ( t_off * PIOSC_FREQUENCY );
			break;
		
		case SYSCLOCK:
			ticks_on = ( uint32_t )( t_on * SYSCLOCK_FREQUENCY );
			ticks_off = ( uint32_t )( t_off * SYSCLOCK_FREQUENCY );
			break;
	}
	if ( ticks_on >= MAXIMUM_TICKS )
	{
		on_counter = ticks_on / MAXIMUM_TICKS;
		overflow_counter_on = on_counter;
		ticks = MAXIMUM_TICKS;
	}
	else
	{
		ticks = ticks_on;
	}
	
	if ( ticks_off >= MAXIMUM_TICKS )
	{
		off_counter = ticks_off / MAXIMUM_TICKS;
		overflow_counter_off = off_counter;
	}
	Dio_WriteChannel( PF1, HIGH );
	SysTick_StartTimer( ticks );
}
