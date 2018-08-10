# dmb_delay_systick

Projekt zawiera prost� biblioteke obs�uguj�c� timer Systick w mikrokontrolerach z rdzeniami Mx. Udost�pnie najcz�ciej wykorzystywane rzeczy. Pisana by�a z my�l� o wykorzystaniu dla STM32F0/F3, ale dzi�ki wykorzystaniu makra gdzie podajemy jakie biblioteki zale�ne od platformy maj� zosta� dodane zyska�a na uniwersalno�ci.

# Koncepcja u�ycia biblioteki w projekcie

Pliki �r�d�owe mo�emy skopiowa� bezpo�rednio do swojego projektu, da� je gdzi� osobono i odpowiednio podlinkowa�, a najlepiej ca�e repozytorium podci�gn�� jako submodu� gita. Biblioteka zak�ada istnienie w projekcie katalogu "libs_config" w �rodku kt�rego znajdzie sie plik "dmb_systick_settings.h" - tam zamieszczone b�d� ustawienia zale�ne od danego projektu. Przyk�adowy plik konfiguracyjny tak�e zosta� tutaj umieszczony.

# Zawarto�� repozytorium

W repozytorium znajdziemy:
* pliki bilioteki w katalogu "dmb_delay_systick"
* przyk�adowy plik konfiguracyjny
* #todo - przyk�adowy projekt z wykorzystaniem tej biblioteki, aczkolwiek raczej opis jest wyczerpuj�cy
* instrukcja w postaci tego pliku

### Zasada dzia�ania i mo�liwo�ci biblioteki

Zacznijmy moze czym jest SysTick - jest to 24-bitowy timer wbudowany w rdzenie Cortex-M. Jest taki sam dla wszystkich + niezale�ny od producenta uk�adu. Podlicza� czas, wi�c idealnie nadaje si� do implementacji na nim timer�w softwarowych, a sprz�towe timery mo�emy wtedy wykorzysta� do bardziej rozbudowanych zada�.

Wst�pnie zak�adam, �e b�dzie on wykorzystywany do "tykania" co milisekund�, ale nic nie stoi na przeszkodzie, zeby to zmieni�.

Mo�liwo�ci biblioteki:
* udost�pnia funkcj� "_delay_ms()" znan� z AVRek - zwyk�y blokuj�cy delay, z tym, �e mo�emy poda� do niego 32bitow� zmienn� (co nie oznacza, �e powinni�my/wypada u�ywa� jej tak :p )
* generowanie co tykni�cie zarejestrowanego callbacka
* odliczanie czasu dzia�ania systemu - co mo�e by� wykorzystane do wyznaczania czasu, gdy wyst�pi� jaki� event
* mo�liwo�� ustawienia i sprawdzania blokuj�cych timeout�w - dla prostych aplikacji

Wykorzystanie biblioteki:
* Jako pierwszy krok inicjalizujemy bibliotek� podaj�c jej z jak� cz�stotliow�ci� jest taktowany SysTick:
```c
// inicjalizacja SysTicka z aktualna predkoscia zegara
dmb_delay_systick_init(48000000);
```
* Je�li chcemy wykorzystywa� callback wywo�ywany co 1 ms musimy go zarejestrowa�:
```c
/*
 * Miganie ledkiem co milisekunde.
 */
void toogle_1ms()
{
	DEBUG_LED1_TOG;
}

...

// podpiecie callbacka, ktory wykona sie co milisekunde
dmb_delay_systick_register_callback( toogle_1ms );

```
* Wykorzystanie timeoutu:
```c
wyslij_do_ukladu_i_czekaj_za_odp();
systick_set_timeout(300);
while( !odebrano_odpowiedz() && systick_check_timeout() );
// tu wejdziemy, gdy  gdy dostaniemy odpowied�, lub minie timeout
```
* wykorzystanie uptime - czyli zwyk�e wywo�anie funkcji:
```
uint32_t aktualna_ms = systick_get_system_uptime();
```

# Parametry do ustawienia

Raczej nie ma co opisywa� dodatkowo - tak wygl�da plik ustawie�:
```c
// Plik "systemowy" zalezny od plaftormy na jaka piszemy
#define DMB_SYSTICK_SYSTEM_INCLUDE 		"stm32f0xx.h"

// Priorytet przerwania do SysTicka
#define DMB_SYSTICK_INTERRUPT_PRIORITY	5

// Wybor, czy w czasie deleya mamy uspic mikrokontroler
// nie zawsze chcemy to robic, np RTT ma problemy z uruchomiona ta opcja
#define DMB_SYSTICK_ENABLE_WFI 1
```

# UWAGA

Systick ca�y czas pracuje w tle, wi�c dok�adno�� funkcji to +/- jedno tykni�cie - raczej zbyt cz�sto nie utrafimy z wywo�anie _delay_ms() "idealnie podczas tykni�cia" - wi�c to nie jest biblioteka do mega precyzyjnych rzeczy!

## Autor
* **dambo** - [Blog](http://www.projektydmb.blogspot.com)