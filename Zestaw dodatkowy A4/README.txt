========================================================================
Autor: Przemysław Pawlik,                                DATA 20.05.2021
========================================================================

* Zawartosc:
============

Katalog zawiera programy realizujące cwiczenie A4:
------------------------------------------------------------------------

I.  Program realizuje działania klient-serwer przy użyciu potoków nazwanych. Proces 
    klienta wysyła działanie do obliczenia a serwer odsyła mu wynik. Serwer tworzy 
    swój potok nazwany i otwiera go. W pętli odczytuje ze swojego potoku nazwanego. 
    Następnie dzieli otrzymaną wiadomość i na jej podstawie ustala nazwę potoku 
    nazwanego klienta, otwiera go, wykonuje działanie i odsyła gotowy wynik umieszczając 
    go w potoku nazwanycm klienta. Na końcu go zamyka. Po otrzymaniu sygnału przerwania 
    [Ctrl C] w funkcji rejestrowanej przez atexit zamyka i usuwa potok nazwany serwera. 
    Konsument natomiast tworzy potok nazwany o nazwie takiej jak PID procesu w którym 
    się znajduje. Następnie otwiera swój potok nazwany i potok nazwany serwera. Pobiera 
    od użytkownika działanie postaci liczba1 znak liczba2 (więcej poniżej). Buduje 
    wiadomość umieszczając na początku PID procesu a następnie dzialanie oraz umieszcza 
    w potoku nazwanym serwera. Następnie pobiera rozwiązanie ze swojego potoku nazwanego. 
    Użykownik może zakończyć podawanie działań przy pomocy znaku końcu pliku [CTRL D], 
    wtedy klient w funkcji rejestrowanej przez atexit zamyka potok nazwany serwera 
    i konsumenta oraz usuwa potok nazwany klienta. 
    Program składa sie z trzech modułów głównych
    1) serwer.c                     - program zajmujący się pracą serwera
    2) klient.c                     - program zajmujący się pracą klienta

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
