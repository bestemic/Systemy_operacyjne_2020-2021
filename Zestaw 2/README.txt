========================================================================
Autor: Przemysław Pawlik,                                DATA 13.03.2021
========================================================================

* Zawartosc:
============

Katalog zawiera program realizujący cwiczenie 2:
------------------------------------------------------------------------

I.  Program uzywający trzy razy fork do stworzenia procesow potomnych
    i urochamiający przy uzyciu exec drugiego programu ktory wypisuje
    identyfikatory UID, GID, PID, PPID i PGID procesow potomnych.
    Program składa sie z dwoch modułow
    1) main.c           - program glowny, 
    3) procinfo.c       - program wypisujacy identyfikatory procesow 

------------------------------------------------------------------------

* Jak uruchomic programy:
=========================

Katalog zawiera program Makefile do kompilacji, linkowania
i uruchamiania powyzszych programow, a takze czyszczenia katalogu 
i jego archiwizacji.

-> Aby uruchomic program, nalezy wykonac komende:
       make run

-> Aby wyczyscic zawartosc katalogu (usunac zbedne pliki), nalezy wykonac:
       make clean

-> W celu archiwizacji oraz kompresji katalogu nalezy wykonac:
       make tar


* Odpowiedzi do pytan:
=====================

Przy n-krotnym wywolaniu funkcji fork-exec powstanie n procesow. Dzieje 
sie tak poniewaz po wywolaniu funkcji exec dalsza czesc programu nie 
zostaje wykonywana. W takiej systuacji podczas kolejnych obiegow petli
potomkowie nie tworza juz swoich potomkow. Odbywa sie tylko n-krotne 
obejscie pentli w procesie macierzystym.

========================================================================
