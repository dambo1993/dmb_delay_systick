/*
 * delay_systick.c
 *
 *  Created on: 25 wrz 2016
 *      Author: Przemek
 */

#include "dmb_delay_systick.h"
#include <libs_config/dmb_systick_settings.h>
#include DMB_SYSTICK_SYSTEM_INCLUDE
#include <inttypes.h>

static volatile uint32_t delay_counter;

static volatile dmb_delay_systick_callback_t callback;

static volatile uint32_t system_up_time;

static volatile uint32_t timeout_counter;

/**
 * \brief Inicjalizuje Systick na przerwanie co 1ms.
 *
 * @param clock_speed clock_speed predkosc taktowania timera SysTick
 */
void dmb_delay_systick_init( uint32_t clock_speed )
{
	SysTick_Config( clock_speed / 1000 );
	NVIC_SetPriority( SysTick_IRQn, DMB_SYSTICK_INTERRUPT_PRIORITY );
}

/**
 * \brief Rejestracja callbacka, ktory wykonuje sie co wywolanie timera.
 * Mozemy tez wpisac NULL/0 zeby wylaczyc callback.
 *
 * \attention Uruchamiany jest na poziomie przerwania!
 *
 * @param user_callback callback do uruchamiania
 */
void dmb_delay_systick_register_callback(dmb_delay_systick_callback_t user_callback)
{
	callback = user_callback;
}

/**
 * \brief Podstawowa funkcja delaya oczekujacego zadana ilosc milisekund. Delay moze byc mniejszy o 1ms niz podany.
 *
 * \attention Blokujaca!
 *
 * @param delay czas w milisekundach
 */
void _delay_ms( uint32_t delay )
{
	delay_counter = delay;
	while( delay_counter )
	{
#if DMB_SYSTICK_ENABLE_WFI
		__WFI(); // delikatne uspienie urzadzenia
#endif
	}
}

/**
 * \brief Pobranie czasu dzialania urzadzenia w milisekundach. Przepelnia sie po ~49dniach.
 * @return
 */
uint32_t systick_get_system_uptime()
{
	return system_up_time;
}

/**
 * \brief Ustawienie punktu od ktorego bedzie zliczany timeout. Zastosowanie np w komunikacji I2C.
 *
 * @param timeout czas timeoutu
 */
void systick_set_timeout(uint32_t timeout)
{
	timeout_counter = timeout;
}

/**
 * \brief Sprawdzenie timeoutu. Zwraca 0 jesli minal juz timeout.
 *
 * \return
 * 		@arg 0: Timeout minal
 * 		@arg 1: Timeout jeszcze nie minal
 */
uint8_t systick_check_timeout()
{
	if(timeout_counter > 0)
	{
		return 1;
	}
	return 0;
}

/**
 * \brief Obsluga przerwania od timera SysTick.
 */
void SysTick_Handler(void)
{
	system_up_time++;

	// dekrementacja licznika odpowiadajacego za prosty delay
	if( delay_counter )
	{
		delay_counter--;
	}

	// dekrementacja licznika timeoutu
	if(timeout_counter)
	{
		timeout_counter--;
	}

	// jesli mamy podpiety callback - wywolujemy go
	if(callback)
	{
		callback();
	}
}
