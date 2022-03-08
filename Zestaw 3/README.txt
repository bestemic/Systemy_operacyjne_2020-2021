========================================================================
Autor: Przemysław Pawlik,                                DATA 23.03.2021
========================================================================

* Zawartosc:
============

Katalog zawiera programy realizujące ćwiczenie 3:
-------------------------------------------------------------------------

I.  Program obsługujący sygnał podany przez użytkownika za pośrednistwem 
    paramtrów, przez parametry podawany jest też sposób obsługi. Możliwe
    jest wykonanie domyślej obsługi, ignorowanie oraz przejęcie sygnału
    i wykonanie własej jego obsługi. Program czeka na sygnał podany 
    z konsoli przy użyciu kill lub klawiatury przy pomocy funkcji pause().
    Program składa sie z jednego modułu
    1) prog_a.c           - program glowny,  

II. Program tworzy swój proces potomny i uruchamia z niego przy użyciu 
    funkcji exec program pierwszy, zajmujący się obsługą sygnałów. 
    Główny program natomiast sprawdza czy istnieje proces potomny i przy 
    użyciu funkcji kill wysyła do niego sygnał.
    Numer sygnału i sposób jego obsługi przekazujemy przy użyciu
    parametrów programu.
    Program składa sie z dwóch modułów
    1) prog_b.c           - program glowny,
    2) prog_a.c           - program wywoływany przez proces potomny

III.Program tworzy swój proces potomny i ustawia go jako lidera nowej
    grupy procesów. Następnie proces ten tworzy kilka swoich potomków 
    i uruchamia z nich przy użyciu funkcji exec program pierwszy, 
    zajmujący się obsługą sygnałów. Proces który jest liderem grupy 
    nowych procesów ignoruje sygnały i czeka na zakończenie swoich potomków,
    przy użyciu fnkcji wait() zwraca ich status zakończenia.
    Główny program natomiast sprawdza czy istnieją procesy potomny i wysyła 
    do całeg grupy sygnał przy użyciu funkcji kill.
    Numer sygnału i sposób jego obsługi przekazujemy przy użyciu
    parametrów programu.
    Program składa sie z dwóch modułów
    1) prog_c.c           - program glowny,
    2) prog_a.c           - program wywoływany przez proces potomny

-------------------------------------------------------------------------

* Jak uruchomic programy:
=========================

Katalog zawiera program Makefile do kompilacji, linkowania a takze 
czyszczenia katalogu i jego archiwizacji.

-> Aby uruchomic pierwszy program, nalezy wykonac komende:
       make build1  -> kompilowanie i budowanie programu
    następnie wywołac w konsoli przy użyciu komendy:
        ./prog_a.x a b      gdzie a to nr sygnału, b to sposób obsługi
                            (1-domyślny, 2-ignorowanie, 3-przechwycenie)
                            pominięcie parametru b wykona domyślną obsługę

    Pomocne do używania funkcji kill z powłoki może być usunięcie komentarza
    z linii 35 w pliku prog_a.c. Dzięki temu zabiegowi wyświetlać się będzie
    PID procesu.


-> Aby uruchomic drugi program, nalezy wykonac komende:
       make build2  -> kompilowanie i budowanie programu
    następnie wywołac w konsoli przy użyciu komendy:
        ./prog_b.x a b      gdzie a to nr sygnału, b to sposób obsługi
                            (1-domyślny, 2-ignorowanie, 3-przechwycenie)
                            pominięcie parametru b wykona domyślną obsługę

-> Aby uruchomic trzeci program, nalezy wykonac komende:
       make build2  -> kompilowanie i budowanie programu
    następnie wywołac w konsoli przy użyciu komendy:
        ./prog_b.x a b      gdzie a to nr sygnału, b to sposób obsługi
                            (1-domyślny, 2-ignorowanie, 3-przechwycenie)
                            pominięcie parametru b wykona domyślną obsługę

-> Aby wyczyscic zawartosc katalogu (usunac zbedne pliki), nalezy wykonac:
       make clean

-> W celu archiwizacji oraz kompresji katalogu nalezy wykonac:
       make tar
