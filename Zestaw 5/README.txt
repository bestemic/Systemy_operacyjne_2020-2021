========================================================================
Autor: Przemysław Pawlik,                                DATA 10.04.2021
========================================================================

* Zawartosc:
============

Katalog zawiera programy realizujące cwiczenie 5:
------------------------------------------------------------------------

I.  Program realizuje problem producenta i konsumenta przy użyciu potoku
    nazwanego. Potok jest tworzony wewnątrz programu, a następnie program
    uruchamia program producenta który otwiera przy użyciu funkcji open 
    plik wejściowy oraz potok nazwany i pobiera funkcją read porcję danych
    którą następnie wypisuje do konsoli i przekazuje do potoku nazwanego 
    przy użyciu funkcji write. Uruchamiany jest również program konsumenta
    który funkcją read odczytuje z wcześniej otwartego potoku nazwanego 
    dane, wypisuje je na konsolę i zapisuje funkcją write do otwartego 
    wcześniej pliku wyjściowego. W programie producenta i konsumenta użyta
    jest funkcja sleep z losowym czasem usypiająca pracę procesów co ma 
    za zadanie symulować różną szybkość działania programów. Program główny
    czeka na zakończenie pracy konsumenta i producenta a następnie w funkcji
    wywoływanej funkcją atexit usuwa potok nazwany. W programie głównym 
    zaimplementowana jest funkcja obsługująca sygnał SIGINT w razie 
    przerwania programu dzięki czemu można usunąć potok nazwany.
    Program składa sie z trzech modułów głównych
    1) main.c           - program glowny tworzący potok nazwany, uruchamiający
                          program producenta i konsumenta a następnie usuwający
                          potok nazwany
    2) producent.c      - program obsługujący pracę producenta
    3) konsument.c      - program obsługujący pracę konsumenta
    Oraz zawiera opcjonalne (przykładowe) pliki wejścia i wyjścia
    1) in.txt           - plik wejściowy z porcją danych
    2) out.txt          - plik wyjściowy (pusty)

II. Program realizuje problem producenta i konsumenta przy użyciu potoku
    nazwanego. Potok nazwany tworzony jest w konsoli, a nie w programie. 
    W oddzielnych terminalach przy użyciu xterm uruchamiany jest program
    producenta i konsumenta. Program producenta otwiera przy użyciu funkcji
    open plik wejściowy oraz potok nazwany i pobiera funkcją read porcję 
    danych którą następnie wypisuje do konsoli i przekazuje do potoku 
    nazwanego przy użyciu funkcji write. Program konsumenta funkcją
    read odczytuje z wcześniej otwartego potoku nazwanego dane, wypisuje 
    je na konsolę i zapisuje funkcją write do otwartego wcześniej pliku 
    wyjściowego. W programie producenta i konsumenta użyta jest funkcja 
    sleep z losowym czasem usypiająca pracę procesów co ma za zadanie 
    symulować różną szybkość działania programów.
    Program składa sie z dwóch modułów głównych
    1) producent.c      - program obsługujący pracę producenta
    2) konsument.c      - program obsługujący pracę konsumenta
    Oraz zawiera opcjonalne (przykładowe) pliki wejścia i wyjścia
    1) in.txt           - plik wejściowy z porcją danych
    2) out.txt          - plik wyjściowy (pusty)

------------------------------------------------------------------------

* Jak uruchomic programy:
=========================

Katalog zawiera program Makefile do kompilacji, linkowania
i uruchamiania powyzszych programow, a takze czyszczenia katalogu 
i jego archiwizacji.

I.  Są zaimplementowane 3 sposoby uruchamiania programu pierwszego:

a). Budowanie programu i ręczne uruchamianie z podaniem plików
    Aby zbudować program należy użyć komendy:
        make run
    Następnie aby go uruchomić należy zastosować następujący schemat 
    (gdzie plik_wejsciowy to nazwa pliku który zawiera dane do odczytania,
    a plik_wyjsciowy to nazwa pliku do którego dane zostaną zapisane):
        ./main.x plik_wejsciowy plik_wyjsciowy
    
b). Budowanie i uruchamianie z domyślnymi plikami
    Aby uruchomic program, nalezy wykonac komende:
       make rund
    Program zostanie uruchomiony z domyślnymi plikami "in.txt" oraz "out.txt"

c). Jak w b) ale z porównaniem plików po zakończeniu pracy 
    Aby uruchomic program, nalezy wykonac komende:
       make runc
    Po zakończeniu programu z domyslnymi plikami nastąpi ich porównanie

II. Są zaimplementowane 3 sposoby uruchamiania programu drugiego:

a). Budowanie i uruchamianie z domyślnymi plikami w oddzielnych terminalach
    (bez tworzenia potoku i jego usuwania, aby to zrobić udaj się do punktu
    III o opcjach dodatkowych)
    Aby uruchomic program, nalezy wykonac komende:
       make runt
    Program zostanie uruchomiony z domyślnymi plikami "in.txt" oraz "out.txt"

b). Jak w a) ale z tworzeniem potoku nazwanego, usuwaniem go i porównaniem
    plików po zakończeniu pracy 
    Aby uruchomic program, nalezy wykonac komende:
       make runfull
    Po zakończeniu programu z domyslnymi plikami nastąpi ich porównanie

III.Dodatkowe opcje

->  Aby utworzyć potok nazwany z nazwą "potok", nalezy wykonac:
       make createfifo

->  Aby usunąć potok nazwany z nazwą "potok", nalezy wykonac:
       make removefifo

->  Aby porównać pliki z danymi nazeży użyć komendy w jedej z dwóch opcji:
       1) make compare  - porównanie domyslnych plików "in.txt" i "out.txt"
       
       2) make compare ARG1="wejscie" ARG2="wyjscie" - porównanie plików które 
            zostaną wpisane w miejsce wejscie (plik wejściowy) i wyjście (plik wyjściowy)
            UWAGA! Należy zachować cudzysłowy i wpisywać pliki z rozszerzeniami

->  Aby wyczyscic zawartosc katalogu (usunac zbedne pliki), nalezy wykonac:
       make clean

->  W celu archiwizacji oraz kompresji katalogu nalezy wykonac:
       make tar
