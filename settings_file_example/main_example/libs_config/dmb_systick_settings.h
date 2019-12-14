/*
 * dmb_systick_settings.h
 *
 *  Created on: 27.05.2018
 *      Author: Przemek
 */

#ifndef LIBS_CONFIG_DMB_SYSTICK_SETTINGS_H_
#define LIBS_CONFIG_DMB_SYSTICK_SETTINGS_H_

/** \addtogroup dmb_delay_systick
 *  @{
 */

/** \addtogroup settings
 *  @{
 */

/**
 * \brief Plik "systemowy" zalezny od plaftormy na jaka piszemy
 */
#include "stm32f0xx.h"

/**
 * \brief Priorytet przerwania do SysTicka
 */
#define DMB_SYSTICK_INTERRUPT_PRIORITY	5

/**
 * \brief Wybor, czy w czasie deleya mamy uspic mikrokontroler, nie zawsze chcemy to robic, np RTT ma problemy z uruchomiona ta opcja
 */
#define DMB_SYSTICK_ENABLE_WFI 1



/** @}*/

/** @}*/

#endif /* LIBS_CONFIG_DMB_SYSTICK_SETTINGS_H_ */
