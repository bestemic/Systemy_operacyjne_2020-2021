========================================================================
Autor: Przemysław Pawlik,                                DATA 29.03.2021
========================================================================

* Zawartosc:
============

Katalog zawiera program realizujący cwiczenie 4:
------------------------------------------------------------------------

I.  Program przy użyciu potoków nienazwanych realizuje problem "producenta
    i konsumenta". Producent otwiera przy użyciu funkcji open plik wejściowy
    i pobiera funkcją read porcję danych którą następnie wypisuje do konsoli
    i przekazuje do potoku przy użyciu funkcji write. Konsument funkcją read
    odczytuje z potoku dane, wypisuje je na konsolę i zapisuje funkcją
    write do otwartego wcześniej pliku wyjściowego. Po pobraniu wszystkich
    danych z pliku i zakończeniu zapisywania, oba pliki są zamykane a program
    kończy pracę. W programie użyta jest funkcja sleep z losowym czasem 
    usypiająca pracę procesów co ma za zadanie symulować różną szybkość
    działania programów.
    Program składa sie z jednego modułu głównego
    1) main.c           - program glowny
    Oraz zawiera opcjonalne (przykładowe) pliki wejścia i wyjścia
    1) in.txt           - plik wejściowy z porcją danych
    2) out.txt          - plik wyjściowy (pusty)

------------------------------------------------------------------------

* Jak uruchomic programy:
=========================

Katalog zawiera program Makefile do kompilacji, linkowania
i uruchamiania powyzszego programu, a takze czyszczenia katalogu 
i jego archiwizacji.

->  Są zaimplementowane 3 sposoby uruchamiania programów:

I.  Budowanie programu i ręczne uruchamianie z podaniem plików
    Aby zbudować program należy użyć komendy:
        make run
    Następnie aby go uruchomić należy zastosować następujący schemat 
    (gdzie plik_wejsciowy to nazwa pliku który zawiera dane do odczytania,
    a plik_wyjsciowy to nazwa pliku do którego dane zostaną zapisane):
        ./main.x plik_wejsciowy plik_wyjsciowy
    
II. Budowanie i uruchamianie z domyślnymi plikami
    Aby uruchomic program, nalezy wykonac komende:
       make rund
    Program zostanie uruchomiony z domyślnymi plikami "in.txt" oraz "out.txt"

III.Jak w II ale z porównaniem plików po zakończeniu pracy 
    Aby uruchomic program, nalezy wykonac komende:
       make runc
    Po zakończeniu programu z domyslnymi plikami nastąpi ich porównanie 

->  Aby porównać pliki z danymi nazeży użyć komendy w jedej z dwóch opcji:
       1) make compare  - porównanie domyslnych plików "in.txt" i "out.txt"
       
       2) make compare ARG1="wejscie" ARG2="wyjscie" - porównanie plików które 
            zostaną wpisane w miejsce wejscie (plik wejściowy) i wyjście (plik wyjściowy)
            UWAGA! Należy zachować cudzysłowy i wpisywać pliki z rozszerzeniami

->  Aby wyczyscic zawartosc katalogu (usunac zbedne pliki), nalezy wykonac:
       make clean

->  W celu archiwizacji oraz kompresji katalogu nalezy wykonac:
       make tar
