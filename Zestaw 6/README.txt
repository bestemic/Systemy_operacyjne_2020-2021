========================================================================
Autor: Przemysław Pawlik,                                DATA 16.04.2021
========================================================================

* Zawartosc:
============

Katalog zawiera programy realizujące cwiczenie 6:
------------------------------------------------------------------------

I.  Program realizuje przy użyciu semaforów nazwanych problem wzajemnego 
    wykluczania się procesów. Program główny tworzy semafor nazwany, 
    wypisuje jego nazwę, adres i wartość oraz tworzy plik słożący do 
    sprawdzania poprawności działania programu. Następnie x razy (ilość 
    podana w argumencie programu) otwiera przy użyciu funkcji execl program 
    zajmujący się tworzeniem i obsługą wykluczeń. Przekazuje mu w parametrach 
    wywołania nazwę semafora, ilość sekcji krytycznych i nazwę pliku 
    sprawdzającego. Program czeka na wykonanie się wszystkich programów
    obsługujących wykluczenia i na końcu wypisuje wartość zapisaną w pliku
    i porównuje z spodziewaną wartością. Spodziewana wartość to ilość sekcji
    krytycznych we wszystkich programach (ilość programów * ilość sekcji).
    Program na zakończenie usuwa plik kontrolny i semafor. zaimplementowana
    jest też obsługa sygnału SIGINT która w razie przerwania usuwa plik
    i semafor.
    Programy zajmujące się wykluczeniami otwierają semafor następnie tyle
    razy ile przekazano przez argument wywołania wykonują sekcje prywatne
    i krytyczne. Informacja w której sekcji i jaka jest wartośc semafora 
    są wypisywane na ekran. W momencie wejścia do sekcji krytycznej opuszczany
    jest semafor a w momencie wyjścia podnoszony. W sekcji krytycznej otwierany
    jest plik kontrolny i zczytywana jest z niego liczba. Następnie po losowym
    uśpieniu jest ona zwiększana o 1 i ponownie otwierany jest plik a liczba
    jest do niego zapisywana. 
    Program składa sie z trzech modułów głównych
    1) main.c                       - program glowny tworzący plik kontrolny i semafor
                                      oraz usuwający plik i semafor
    2) wykluczenia.c                - program zajmujący się symulacją i obsługą wykluczeń
    3) biblioteka.c, biblioteka.h   - własne funkcje obsługujące semafory

------------------------------------------------------------------------

* Jak uruchomic programy:
=========================

Katalog zawiera program Makefile do kompilacji, linkowania
i uruchamiania powyzszych programow, a takze czyszczenia katalogu 
i jego archiwizacji.

->  Aby zbudować program z użyciem biblioteki statycznej należy wykonać:
        make run
    Aby uruchomić program należy wykonac:
        ./main.x wykluczenia.x a b 
        gdzie "a" to ilość procesów któe chcemy stworzyć, "b" to ilość
        sekcji krytycznych które chcemy mieć


->  Aby wyczyscic zawartosc katalogu (usunac zbedne pliki), nalezy wykonac:
       make clean

->  W celu archiwizacji oraz kompresji katalogu nalezy wykonac:
       make tar


* Odpowiedzi do pytań:
=========================================================================

Wartość kontrolna znajdująca się w pliku gdy nie korzystamy z semaforów
będzie mniejsza od spodziewanej. Dzieje się tak gdyż kilka procesów ma 
wtedy jednocześnie dostęp do sekcji krytycznej. I odczytują z pliku tę 
samą liczę.

=========================================================================
