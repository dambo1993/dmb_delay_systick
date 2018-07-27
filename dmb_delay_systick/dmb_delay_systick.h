/*
 * delay_systick.h
 *
 *  Created on: 25 wrz 2016
 *      Author: Przemek
 */

#ifndef DMB_DELAY_SYSTICK_H_
#define DMB_DELAY_SYSTICK_H_

#include <inttypes.h>

//! typ dla callbacka wywolywanego z poziomu przerwania Systicka
typedef void (*dmb_delay_systick_callback_t)();

/*
 * Inicjalizuje Systick na przerwanie co 1ms.
 *
 * @param clock_speed predkosc taktowania timera SysTick
 */
void dmb_delay_systick_init( uint32_t clock_speed);

/*
 * Rejestracja callbacka, ktory wykonuje sie co wywolanie timera.
 * Mozemy tez wpisac NULL/0 zeby wylaczyc callback.
 * UWAGA - uruchamiany jest na poziomie przerwania!
 */
void dmb_delay_systick_register_callback(dmb_delay_systick_callback_t);

/*
 * Podstawowa funkcja delaya oczekujacego zadana ilosc milisekund. Delay moze byc mniejszy o 1ms niz podany.
 * UWAGA - BLOKUJACA!
 *
 * @param delay - czas w milisekundach,
 */
void _delay_ms( uint32_t delay );

/*
 * Ustawienie punktu od ktorego bedzie zliczany timeout. Zastosowanie np w komunikacji I2C.
 */
void systick_set_timeout(uint32_t timeout);

/*
 * Sprawdzenie timeoutu. Zwraca 0 jesli minal juz timeout.
 *
 * \return 0 jesli minal juz timeout w przeciwnym razie zwraca 1 "timeout trwa-tyka".
 */
uint8_t systick_check_timeout();

/*
 * Pobranie czasu dzialania urzadzenia w milisekundach. Przepelnia sie po ~49dniach.
 */
uint32_t systick_get_system_uptime();

/*
 * Obsluga przerwania od timera SysTick.
 */
void SysTick_Handler(void);



#endif /* DMB_DELAY_SYSTICK_H_ */
