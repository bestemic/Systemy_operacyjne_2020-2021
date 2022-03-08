========================================================================
Autor: Przemysław Pawlik,                                DATA 15.03.2021
========================================================================

* Zawartosc:
============

Katalog zawiera pięć programów realizujących ćwiczenie 1:
------------------------------------------------------------------------

I.  Program wypisujący identyfikatory UID, GID, PID, PPID i PGID procesu
    1) prog_a.c  - program glowny. 

II. Program tworzący 3 razy procesy potomne i wypisujący identyfikatory
    każdego potomka. Program każysta z finkcji wait() aby poczekać na 
    zakończenie wszystkich procesów potomnych.
    1) prog_b.c  - program glowny.

III.Program pozwalający na adopcję procesów sierot przez init dzięki
    użyciu funkcji sleep() i oczekiwaniu na zakończenie procesu głównego
    przed zakończeniem potomnych.
    1) prog_c.c  - program glowny.

IV. Program wypisujący pogrupowane procesy potomne od najstarszego do 
    najmłodszego. Funckja sleep() pozwala na uzyskanie takiego wyniku
    gdy dla potomków powstałych w każdej iteracji pętli będzie krótszy
    czas oczekiwania niż w poprzedniej pętli. 
    1) prog_d.c  - program glowny.

V.  Program ustawiający by każdy proces potomny stawał się liderem
    swojej grupy.
    1) prog_e.c  - program glowny.

------------------------------------------------------------------------

Katalog zawiera plik drzewo_genealogiczne.txt zawierajacy przykladowe 
drzewo genealogiczne procesow.

Plik adopcja.jpg zawiera strukturę zaadoptowanych procesów sierot przez
proces init.

------------------------------------------------------------------------

* Jak uruchomic programy:
=========================

Katalog zawiera program Makefile do kompilacji, linkowania
i uruchamiania powyzszych programow, a takze czyszczenia katalogu 
i jego archiwizacji.

-> Aby uruchomic pierwszy program, nalezy wykonac komende:
       make run1

-> Aby uruchomic drugi program, nalezy wykonac komende:
       make run2

-> Aby uruchomic trzeci program, nalezy wykonac komende:
       make run3

-> Aby uruchomic czwarty program, nalezy wykonac komende:
       make run4

-> Aby uruchomic piaty program, nalezy wykonac komende:
       make run5

-> Aby wyczyscic zawartosc katalogu (usunac zbedne pliki), nalezy wykonac:
       make clean

-> W celu archiwizacji oraz kompresji katalogu nalezy wykonac:
       make tar



* Odpowiedzi do pytan:
=========================================================================

Przy n-ktornym wywołaniu funkcji fork będziemy mieć 2^n procesów.
Natomast samych potomnych będzie (2^n)-1 (odrzucamy proces macierzysty).
Dzieje się tak gdyż każdy proces po użyciu funkcji fork tworzy swój
duplikat. Czyli mając jeden proces po forku będą dwa. I tak w każdym 
forku każdy proces się rozmnaża i mamy już 2 procesy z wyjściowego 
jednego. Takie powstawnie wyraża się wzorem 2^n gdzie n to liczba forków.

=========================================================================
