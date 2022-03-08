========================================================================
Autor: Przemysław Pawlik,                                DATA 13.05.2021
========================================================================

* Zawartosc:
============

Katalog zawiera programy realizujące cwiczenie 9:
------------------------------------------------------------------------

I.  Program realizuje problem wzajemnego wykluczenia przy użyciu wątków 
    i muteksów. Program tworzy muteks i wypisuje jego adres. Następnie
    tworzy wątki w ilości podanej podczas uruchamiania programu i wypisują
    numer wątku oraz identyfikator wątku. Wątki wykonują wykluczenia, przy
    użyciu muteksu. Wątek ma tyle sekcji krytycznych/prywatnych ile podano
    podczas uruchomienia programu. Aby pokazać że wszystko działa poprawnie
    w sekcji krytycznej program pobiera do zmiennej tymczasowej wartość globalnego
    licznika i po kilku sekundach inkrementuje ją i zapisuje z powrotem do 
    licznika. Wątek główny czeka na zakończenie utworzonych wątków, usuwa 
    muteks i na końcu wypisuję wartość licznika i potównuje z oczekiwaną 
    wartością. Wątki wypisują swoje sekcjie - prywatne po lewej stronie 
    konsoli a publiczne po prawej stronie.
    Program składa sie z jednego modułu głównego
    1) main.c                     - program główny

------------------------------------------------------------------------

* Jak uruchomic programy:
=========================

Katalog zawiera program Makefile do kompilacji, linkowania
i uruchamiania powyzszych programow, a takze czyszczenia katalogu 
i jego archiwizacji.

->  Aby zbudować program należy wykonać:
        make build
    Aby uruchomić należy wykonać:
        ./main.x a b    a - ilość wątków,    b - ilość sekcji krytycznych
    
->  Aby wyczyscic zawartosc katalogu (usunac zbedne pliki), nalezy wykonac:
       make clean

->  W celu archiwizacji oraz kompresji katalogu nalezy wykonac:
       make tar
