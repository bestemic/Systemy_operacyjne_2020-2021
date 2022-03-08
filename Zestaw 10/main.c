#define _REENTRANT
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>

#define THREADS 4
#define CRITIC 3

int numer[THREADS];
int wybieranie[THREADS];

// Globalny licznik
int licznik = 0;

// Funkcja losująca ile sekund ma oczekiwać proces (od 2 do 6)
unsigned int czas(void)
{
    return 2 + rand() % 5;
}

void *wyklucz(void *arg)
{
    // Pobranie numeru wątku z przekazanego argumentu
    int thread = *((int *)arg);

    // Zmienne tymczasowe
    int tmp;
    int max;

    // Oczekiwanie na utworzenie wszystkich wątków
    sleep(THREADS);

    for (int c = 1; c <= CRITIC; c++)
    {
        // Ustawienie kursora dla sekcji prywatnej i jej wypisanie
        printf("\033[%d;%dH", thread + THREADS, 1);
        printf("Sekcja prywatna nr %d wątku: %d\n", c, thread);

        // Losowe uśpienie
        sleep(czas());

        // Poinformowanie innych wątów o wybieraniu
        wybieranie[thread - 1] = 1;

        // Wyzerowanie liczby maksymalnej
        max = 0;

        // Wybranie największej liczby spośród danych
        for (int i = 0; i < THREADS; i++)
        {
            if (max < numer[i])
            {
                max = numer[i];
            }
        }

        // Przypisanie wątkowi liczby o 1 większej niż dotychczasowa maksymalna
        numer[thread - 1] = max + 1;

        // Poinformowanie innych wątów o końcu wybierania
        wybieranie[thread - 1] = 0;

        for (int j = 0; j < THREADS; j++)
        {
            // Sprawdzenie czy inny wątek nie wybiera liczby
            while (wybieranie[j])
            {
                // Czekanie na zakończenie wybierania innego wątku
            }

            // Sprawdzenie czy inne wątki mające numer mniejszy lub równy (ale z wyższym priorytetem) zakończyły swoją sekcję krytyczną
            while (numer[j] != 0 && (numer[j] < numer[thread - 1] || (numer[j] == numer[thread - 1] && j < thread - 1)))
            {
                // Czekanie na zakończenie sekcji krytycznych wątków opisanych wyżej
            }
        }

        // Wejście do sekcji krytycznej

        //-------    SEKCJA KRYTYCZNA    -------//

        // Pobranie do zmiennej lokalnej wartości licznika
        tmp = licznik;

        // Wyczyszczenie napisu sekcji prywatnej
        printf("\033[%d;%dH\033[2K", thread + THREADS, 1);

        // Przesunięcie kursora do wypisania sekcji krytycznej i jej wypisanie
        printf("\033[%d;%dH", THREADS + 1, 100);
        printf("Sekcja krytyczna nr %d wątku: %d\n", c, thread);

        // Przesunięcie kursora do wypisania sekcji krytycznej i jej wypisanie
        printf("\033[%d;%dH", THREADS + 2, 100);
        printf("Odczytano: %d, zapisze: %d\n", tmp, tmp + 1);

        // Losowe uśpienie programu
        sleep(czas());

        // Zwiększenie wartości licznika tymczasowego
        tmp++;

        // Zapisanie wartości licznika tymczasowego do globalnego
        licznik = tmp;

        // Wyczyszczenie napisów sekcji publicznej
        printf("\033[%d;%dH", THREADS + 1, 100);
        printf("                                       ");
        printf("\033[%d;%dH", THREADS + 2, 100);
        printf("                                       ");

        //----    KONIEC SEKCJI KRYTYCZNEJ    ----//
        // Poinformowanie o wyjściu z sekcji krytycznej
        numer[thread - 1] = 0;
    }

    // Wyjście z wątku
    pthread_exit(NULL);
}

void koniec(void)
{
    printf("\nKoniec procesu!\n\n");
}

int main(int argc, char *argv[])
{
    // Rejestracja funkcji wywołanych przez exit()
    if (atexit(koniec) != 0)
    {
        perror("atexit error");
        exit(EXIT_FAILURE);
    }

    // Aktywowanie generatora liczb pseudolosowych
    srand(time(NULL));

    // Zmienna do przechowywania wartości ewentualnych błędów
    int test;

    // Tablica do przechowywania identyfikatorów wątków
    pthread_t idtab[5];

    // Zainicjalizowanie zmiennych dzielonych
    for (int i = 0; i < THREADS; i++)
    {
        wybieranie[i] = 0;
        numer[i] = 0;
    }

    // Wyszyszczenie ekranu
    printf("\033c");

    // Tworzenie wątków
    for (int i = 1; i <= THREADS; i++)
    {
        // Utworzenie wątku z domyślnymi atrybutami
        test = pthread_create(&(idtab[i - 1]), NULL, &wyklucz, (void *)&(i));

        // Obsługa błędu funkcji pthread_create
        if (test != 0)
        {
            printf("pthread_create error: %d\n", test);
        }

        // Wyisanie informacji o wątkach
        printf("Watek o nr %d ma identyfkator %ld\n", i, idtab[i - 1]);

        sleep(1);
    }

    // Czekanie na wątki
    for (int i = 0; i < THREADS; i++)
    {
        // Oczekiwanie na zakończenie się wątków
        test = pthread_join(idtab[i], NULL);

        // Obsługa błędu funkcji pthread_join
        if (test != 0)
        {
            printf("pthread_join error: %d\n", test);
            exit(6);
        }
    }

    // Zmienna do przechowywania wartości oczekiwanego wyniku
    int oczekiwana = THREADS * CRITIC;

    // Przywrócenie miejca wypisywania
    printf("\033[%d;%dH", THREADS + 2, 1);

    // Wypisanie informacji o wyniku
    printf("Wartosc licznika globalnego: %d, oczekiwana wartosc %d\n", licznik, oczekiwana);
    if (licznik == oczekiwana)
    {
        printf("Wartosc zgodna z oczekiwana\n");
    }
    else
    {
        printf("Wartosc niezgodna z oczekiwana\n");
    }

    return 0;
}