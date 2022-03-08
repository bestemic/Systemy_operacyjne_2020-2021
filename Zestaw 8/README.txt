========================================================================
Autor: Przemysław Pawlik,                                DATA 10.05.2021
========================================================================

* Zawartosc:
============

Katalog zawiera programy realizujące cwiczenie 8:
------------------------------------------------------------------------

I.  Program realizuje działania klient-serwer przy użyciu kolejke komunikatów.
    Proces klienta wysyła działanie do obliczenia a serwer odsyła mu wynik.
    Serwer tworzy swoją kolejkę komunikatów i otwiera ją. W pętli odczytuje
    ze swojej kolejki komunikatów. Następnie dzieli otrzymaną wiadomość
    i na jej podstawie ustala nazwę kolejki klienta, otwiera ją, wykonuje działanie
    i odsyła gotowy wynik umieszczając go w kolejce klienta. Na końcu ją zamyka.
    Po otrzymaniu sygnału przerwania [Ctrl C] w funkcji rejestrowanej przez atexit
    zamyka i usuwa kolejkę serwera. Konsument natomiast tworzy kolejkę komunikatów
    o nazwie takiej jak PID procesu w którym się znajduje. Następnie otwiera swoją 
    kolejkę i kolejkę serwera. Pobiera od użytkownika działanie postaci
    liczba1 znak liczba2 (więcej poniżej). Buduje wiadomość umieszczając na początku
    PID procesu a następnie dzialanie oraz umieszcza w kolejce serwera. Następnie
    pobiera rozwiązanie ze swojej kolejki komunikatów. Użykownik może zakończyć 
    podawanie działań przy pomocy znaku końcu pliku [CTRL D], wtedy klient w funkcji
    rejestrowanej przez atexit zamyka kolejkę serwera i konsumenta oraz usuwa kolejkę
    klienta. 
    Program składa sie z trzech modułów głównych
    1) serwer.c                     - program zajmujący się pracą serwera
    2) klient.c                     - program zajmujący się pracą klienta
    3) mes_bib.c, mes_bib.h         - własne funkcje obsługujące kolejki komunikatów

------------------------------------------------------------------------

* Jak uruchomic programy:
=========================

Katalog zawiera program Makefile do kompilacji, linkowania
i uruchamiania powyzszych programow, a takze czyszczenia katalogu 
i jego archiwizacji.

->  Aby uruchomić program należy wykonać:
        make run
    Dane podawać w postaci: liczba1_znak_liczba2 gdzoe znak należy do {+,-,*,/}
    a '_' oznacza spację. Zatwierdzić enterem
    Aby zakończyć wczytywanie działań należy użyć [CTRL D]
    Aby przerwać pracę serwera należy użyć [CTRL C]

->  Aby wyczyscic zawartosc katalogu (usunac zbedne pliki), nalezy wykonac:
       make clean

->  W celu archiwizacji oraz kompresji katalogu nalezy wykonac:
       make tar
