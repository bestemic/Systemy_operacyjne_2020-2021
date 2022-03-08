========================================================================
Autor: Przemysław Pawlik,                                DATA 04.05.2021
========================================================================

* Zawartosc:
============

Katalog zawiera programy realizujące cwiczenie 7:
------------------------------------------------------------------------

I.  Program realizuje problem producenta i komsumenta przy użyciu pamięci
    dzielonej. Do przesyłania danych używamy bufora cyklicznego umieszczonego
    w pamięci dzielonej. Umieszczanie i odczytywanie danych jest kontrolowane
    przy pomocy semaforów. Program główny tworzy semafory i pamięć dzieloną.
    Następnie uruchamia przy użyciu funkcji fork-exec program producenta
    i komsumenta, czeka na ich zakończenie i usuwa semafory oraz pamięć
    dzieloną. Program główny ma również zaimplementowaną obsługę sygnału
    SIGINT aby po przerwaniu przez użytkownika programu usunąć semafory
    i pamięć dzieloną. Program producenta pobiera dane z pliku i wstawia je 
    do buforu który jest w odwzorowanej pamięci dzielonej. Wypisuje też
    informacje o wartościach semaforów a także ilości przesyłanych bajtów
    i tekstu który przesyłamy. Porgram konsumenta odczytuje dane z bufora
    i wpisuje je do pliku wyjściowego. Wypisuje też informacje o wartościach
    semaforów a także przesyłanym tekście.
    Program składa sie z sześciu modułów głównych
    1) main.c                       - program glowny tworzący semafory,
                                      pamięć dzieloną, a po zakończeniu
                                      pracy usuwa je. Program uruchamia
                                      też program producenta i komsumenta.
    2) producent.c                  - program zajmujący się pracą producenta
    3) konsument.c                  - program zajmujący się pracą konsumenta
    4) sem_bib.c, sem_bib.h         - własne funkcje obsługujące semafory
    5) mem_bib.c, mem_bib.h         - własne funkcje obsługujące pamięć dzieloną
    6) in.txt, out.txt              - pliki wejście i wyjścia

------------------------------------------------------------------------

* Jak uruchomic programy:
=========================

Katalog zawiera program Makefile do kompilacji, linkowania
i uruchamiania powyzszych programow, a takze czyszczenia katalogu 
i jego archiwizacji.

->  Aby uruchomić program z użyciem biblioteki statycznej należy wykonać:
        make runs

->  Aby uruchomić program z użyciem biblioteki dynamicznej należy wykonać:
        make rund1      - pierwszy sposób
        make rund2      - drugi sposób

->  Aby porównać pliki tekstowe, nalezy wykonac:
       make compare

->  Aby wyczyscic zawartosc katalogu (usunac zbedne pliki), nalezy wykonac:
       make clean

->  W celu archiwizacji oraz kompresji katalogu nalezy wykonac:
       make tar


* Pseudokod:
=========================================================================

#define N ?                             // Rozmiar bufora
typdef struct { ... } Towar;            // Definicja typu dla jednostek towaru
Towar bufor[N];                         // Bufor mogacy pomiescic N jednostek towaru
int wstaw = 0, wyjmij = 0;              // Pozycje wstawiania oraz wyjmowania towaru

semaphore PROD = N;                     // Semafor do wstrzymywania Producenta
semaphore KONS = 0;                     // Semafor do wstrzymywania Konsumenta
semaphore STRPROD = 1;                  // Semafor strażnik aby jednocześnie działał jeden producent
semaphore STRKONS = 1;                  // Semafor strażnik aby jednocześnie działał jeden konsument


// Proces Producent
// ----------------
   Towar towarProd;
   while (1) {
    // Produkcja towaru
    P(PROD);                            // Opusc semafor Konsumenta
    P(STRPROD);                         // Opusc semafor strażnika producenta
    bufor[wstaw] = towarProd;           // Umiesc towar w buforze
    wstaw = (wstaw + 1) % N;            // Przesun pozycje wstawiania o 1 dalej
    V(STRPROD);                         // Podniesc semafor strażnika producenta
    V(KONS);                            // Podniesc semafor Konsumenta
   }


// Proces konsument
// ----------------
   Towar towarKons;
   while (1) {
    P(KONS);                            // Opusc semafor Konsumenta
    P(STRKONS);                         // Opusc semafor strażnika konsumenta
    towarKons = bufor[wyjmij];          // Umiesc towar w buforze
    wstaw = (wstaw + 1) % N;            // Przesun pozycje wyjmowania o 1 dalej
    V(STRKONS);                         // Podniesc semafor strażnika konsumenta
    V(PROD);                            // Podniesc semafor Konsumenta
    // Konsumpcja towaru
   }

=========================================================================
