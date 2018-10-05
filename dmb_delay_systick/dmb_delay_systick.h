/*
 * delay_systick.h
 *
 *  Created on: 25 wrz 2016
 *      Author: Przemek
 */

#ifndef DMB_DELAY_SYSTICK_H_
#define DMB_DELAY_SYSTICK_H_

#include <inttypes.h>

/**
 * \brief typ dla callbacka wywolywanego z poziomu przerwania Systicka
 */
typedef void (*dmb_delay_systick_callback_t)();

/**
 * \brief Inicjalizuje Systick na przerwanie co 1ms.
 *
 * @param clock_speed clock_speed predkosc taktowania timera SysTick
 */
void dmb_delay_systick_init( uint32_t clock_speed);

/**
 * \brief Rejestracja callbacka, ktory wykonuje sie co wywolanie timera.
 * Mozemy tez wpisac NULL/0 zeby wylaczyc callback.
 *
 * \attention Uruchamiany jest na poziomie przerwania!
 *
 * @param user_callback callback do uruchamiania
 */
void dmb_delay_systick_register_callback(dmb_delay_systick_callback_t user_callback);

/**
 * \brief Podstawowa funkcja delaya oczekujacego zadana ilosc milisekund. Delay moze byc mniejszy o 1ms niz podany.
 *
 * \attention Blokujaca!
 *
 * @param delay czas w milisekundach
 */
void _delay_ms( uint32_t delay );

/**
 * \brief Ustawienie punktu od ktorego bedzie zliczany timeout. Zastosowanie np w komunikacji I2C.
 *
 * @param timeout czas timeoutu
 */
void systick_set_timeout(uint32_t timeout);

/**
 * \brief Sprawdzenie timeoutu. Zwraca 0 jesli minal juz timeout.
 *
 * \return
 * 		@arg 0: Timeout minal
 * 		@arg 1: Timeout jeszcze nie minal
 */
uint8_t systick_check_timeout();

/**
 * \brief Pobranie czasu dzialania urzadzenia w milisekundach. Przepelnia sie po ~49dniach.
 * @return
 */
uint32_t systick_get_system_uptime();

/**
 * \brief Obsluga przerwania od timera SysTick.
 */
void SysTick_Handler(void);



#endif /* DMB_DELAY_SYSTICK_H_ */
