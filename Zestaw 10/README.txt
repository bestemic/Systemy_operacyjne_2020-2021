========================================================================
Autor: Przemysław Pawlik,                                DATA 13.05.2021
========================================================================

* Zawartosc:
============

Katalog zawiera programy realizujące cwiczenie 10:
------------------------------------------------------------------------

I.  Program realizuje algorytm piekarni przy użyciu P-wątków. Wątek główny
    inicjalizuje zmienne dzielone wartoścami i tworzy zdefiniowaną ilość
    wątków oraz wypisuje ich numer i identyfikator. Następnie oczekuje 
    na ich zakończenie, wypisuje wartość globalnego licznika i sprawdza
    czy jest to oczekiwana wartość. Utworzone wątki natomiast wykonują
    swoje sekcjie zdefiniowaną ilość razy. Po lewej stronie konsoli
    wypisywane są informacje o sekcji prywatej, następnie po upływie
    kilku sekund wątek próbuje wejść do sekcji krytycznej. W tym celu
    zaznacza że chce wejść, otrzymuje największy numer z puli. Następnie
    czeka jeśli inne procesy są w fazie przydzielania numeru. Dalej
    sprawdza czy inne wątki mają numer mniejszy lub równy, a jeśli równy
    to czy ich numer wątku jest mniejszy od obecnego. Jeśli tak to czeka
    aż one skończą pracę sekcji krytycznej. Gdy do niej wejdzie pobiera do
    zmiennej tymczasowej wartość globalnego licznika i po upływie kilku
    sekund inkrementuje wartość i zwraca ją do licznika globalnego. Wypisuje
    też po prawej stronie informacje o sekcji krytycznej i liczniku. Wychodząc
    z sekcji krytycznej wątek zeruje otrzymany numer.
    Program kompilowany jest bez flagi -O żaby uniknąć optymalizacji podczas
    kompilacji co może powodować niepoprawne działanie programu (wynika to
    z architektury noweoczesnych procesorów).
    Program składa sie z jednego modułu głównego
    1) main.c                     - program główny

------------------------------------------------------------------------

* Jak uruchomic programy:
=========================

Katalog zawiera program Makefile do kompilacji, linkowania
i uruchamiania powyzszych programow, a takze czyszczenia katalogu 
i jego archiwizacji.

->  Aby uruchomić program należy wykonać:
        make run
    Aby zmienić ilość wątków i sekcji krytycznych wystarczy zmienić wartość makr THREADS i CRITIC
    
->  Aby wyczyscic zawartosc katalogu (usunac zbedne pliki), nalezy wykonac:
       make clean

->  W celu archiwizacji oraz kompresji katalogu nalezy wykonac:
       make tar
