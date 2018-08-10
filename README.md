# dmb_delay_systick

Projekt zawiera prostπ biblioteke obs≥ugujπcπ timer Systick w mikrokontrolerach z rdzeniami Mx. UdostÍpnie najczÍúciej wykorzystywane rzeczy. Pisana by≥a z myúlπ o wykorzystaniu dla STM32F0/F3, ale dziÍki wykorzystaniu makra gdzie podajemy jakie biblioteki zaleøne od platformy majπ zostaÊ dodane zyska≥a na uniwersalnoúci.

# Koncepcja uøycia biblioteki w projekcie

Pliki èrÛd≥owe moøemy skopiowaÊ bezpoúrednio do swojego projektu, daÊ je gdziÍ osobono i odpowiednio podlinkowaÊ, a najlepiej ca≥e repozytorium podciπgnπÊ jako submodu≥ gita. Biblioteka zak≥ada istnienie w projekcie katalogu "libs_config" w úrodku ktÛrego znajdzie sie plik "dmb_systick_settings.h" - tam zamieszczone bÍdπ ustawienia zaleøne od danego projektu. Przyk≥adowy plik konfiguracyjny takøe zosta≥ tutaj umieszczony.

# ZawartoúÊ repozytorium

W repozytorium znajdziemy:
* pliki bilioteki w katalogu "dmb_delay_systick"
* przyk≥adowy plik konfiguracyjny
* #todo - przyk≥adowy projekt z wykorzystaniem tej biblioteki, aczkolwiek raczej opis jest wyczerpujπcy
* instrukcja w postaci tego pliku

### Zasada dzia≥ania i moøliwoúci biblioteki

Zacznijmy moze czym jest SysTick - jest to 24-bitowy timer wbudowany w rdzenie Cortex-M. Jest taki sam dla wszystkich + niezaleøny od producenta uk≥adu. PodliczaÊ czas, wiÍc idealnie nadaje siÍ do implementacji na nim timerÛw softwarowych, a sprzÍtowe timery moøemy wtedy wykorzystaÊ do bardziej rozbudowanych zadaÒ.

WstÍpnie zak≥adam, øe bÍdzie on wykorzystywany do "tykania" co milisekundÍ, ale nic nie stoi na przeszkodzie, zeby to zmieniÊ.

Moøliwoúci biblioteki:
* udostÍpnia funkcjÍ "_delay_ms()" znanπ z AVRek - zwyk≥y blokujπcy delay, z tym, øe moøemy podaÊ do niego 32bitowπ zmiennπ (co nie oznacza, øe powinniúmy/wypada uøywaÊ jej tak :p )
* generowanie co tykniÍcie zarejestrowanego callbacka
* odliczanie czasu dzia≥ania systemu - co moøe byÊ wykorzystane do wyznaczania czasu, gdy wystπpi≥ jakiú event
* moøliwoúÊ ustawienia i sprawdzania blokujπcych timeoutÛw - dla prostych aplikacji

Wykorzystanie biblioteki:
* Jako pierwszy krok inicjalizujemy bibliotekÍ podajπc jej z jakπ czÍstotliowúciπ jest taktowany SysTick:
```c
// inicjalizacja SysTicka z aktualna predkoscia zegara
dmb_delay_systick_init(48000000);
```
* Jeúli chcemy wykorzystywaÊ callback wywo≥ywany co 1 ms musimy go zarejestrowaÊ:
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
// tu wejdziemy, gdy  gdy dostaniemy odpowiedü, lub minie timeout
```
* wykorzystanie uptime - czyli zwyk≥e wywo≥anie funkcji:
```
uint32_t aktualna_ms = systick_get_system_uptime();
```

# Parametry do ustawienia

Raczej nie ma co opisywaÊ dodatkowo - tak wyglπda plik ustawieÒ:
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

Systick ca≥y czas pracuje w tle, wiÍc dok≥adnoúÊ funkcji to +/- jedno tykniÍcie - raczej zbyt czÍsto nie utrafimy z wywo≥anie _delay_ms() "idealnie podczas tykniÍcia" - wiÍc to nie jest biblioteka do mega precyzyjnych rzeczy!

## Autor
* **dambo** - [Blog](http://www.projektydmb.blogspot.com)