#define _REENTRANT
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>

// Globalny licznik
int licznik = 0;

// Struktura argumentów dla funkcji pthread_create
struct arg_struct
{
    pthread_mutex_t mutex;
    int critic;
    int thread;
    int sleep;
};

// Funkcja losująca ile sekund ma oczekiwać proces (od 2 do 6)
unsigned int czas(void)
{
    return 2 + rand() % 5;
}

// Funkcja do obsługi wzajemnego wykluczenia wykonywana przez wątki
void *wyklucz(void *arg)
{

    // Zmienna na licznik tymczasowy i nr wątku
    int tmp;
    int thread;

    // Pobranie struktury argumentów
    struct arg_struct *args = arg;

    // Pobranie numeru wątku
    thread = args->thread;

    // Oczekiwanie na utwrzenie wszystkich wątków
    sleep(args->sleep);

    for (int i = 0; i < args->critic; i++)
    {
        // Ustawienie kursora dla sekcji prywatnej i jej wypisanie
        printf("\033[%d;%dH", thread + args->sleep + 1, 1);
        printf("Sekcja prywatna nr %d wątku: %d\n", i + 1, thread);

        // Losowe uśpienie programu
        sleep(czas());

        // Zamknięcie muteksu
        pthread_mutex_lock(&(args->mutex));

        //-------    SEKCJA KRYTYCZNA    -------//

        // Pobranie wartości z globlanego licznika
        tmp = licznik;

        // Wyczyszczenie napisu sekcji prywatnej
        printf("\033[%d;%dH\033[2K", thread + args->sleep + 1, 1);

        // Przesunięcie kursora do wypisania sekcji publicznej i jej wypisanie
        printf("\033[%d;%dH", args->sleep + 3, 100);
        printf("Sekcja publiczna nr %d wątku: %d\n", i + 1, thread);

        // Przesunięcie kursora do wypisania sekcji publicznej i jej wypisanie
        printf("\033[%d;%dH", args->sleep + 4, 100);
        printf("Odczytano: %d, zapisze: %d\n", tmp, tmp + 1);

        // Losowe uśpienie programu
        sleep(czas());

        // Zwiększenie wartości licznika tymczasowego
        tmp++;

        // Zapisanie wartości licznika tymczasowego do globalnego
        licznik = tmp;

        // Wyczyszczenie napisów sekcji publicznej
        printf("\033[%d;%dH", args->sleep + 3, 100);
        printf("                                       ");
        printf("\033[%d;%dH", args->sleep + 4, 100);
        printf("                                       ");

        //----    KONIEC SEKCJI KRYTYCZNEJ    ----//

        // Otworzenie muteksu
        pthread_mutex_unlock(&(args->mutex));
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

    // Sprawdzenie poprawnosci parametrów
    if (argc != 3)
    {
        printf("Nieprawidlowa ilosc argumentow, nie mozna uruchomic programu\n");
        exit(EXIT_FAILURE);
    }

    // Aktywowanie generatora liczb pseudolosowych
    srand(time(NULL));

    // Zmienna do przechowywania wartości ewentualnych błędów
    int test;

    // Tablica do przechowywania identyfikatorów wątków
    pthread_t idtab[atoi(argv[1])];

    // Zmienna do przechowywania muteksu
    pthread_mutex_t mutex;

    // Inicjalizacja muteksu wartością domyślną
    test = pthread_mutex_init(&mutex, NULL);

    // Wyszyszczenie ekranu
    printf("\033c");

    // Wypisanie adresu muteksu
    printf("Adres muteksu: %p\n", (void *)&mutex);

    // Obsługa błędu funkcji pthread_mutex_init
    if (test != 0)
    {
        printf("pthread_mutex_init error: %d\n", test);
        exit(5);
    }

    // Utworzenie struktury argumantów i ich inicjalizacja
    static struct arg_struct args;
    args.mutex = mutex;
    args.critic = atoi(argv[2]);
    args.sleep = atoi(argv[1]);

    // Tworzenie wątków
    for (int i = 1; i <= atoi(argv[1]); i++)
    {
        // Wpisanie nr wątku w argumenty
        args.thread = i;

        // Utworzenie wątku z domyślnymi atrybutami
        test = pthread_create(&(idtab[i - 1]), NULL, &wyklucz, &args);

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
    for (int i = 0; i < atoi(argv[1]); i++)
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

    // Usunięcie muteksu
    test = pthread_mutex_destroy(&mutex);

    // Obsługa błędu funkcji pthread_mutex_destroy
    if (test != 0)
    {
        printf("pthread_mutex_destroy error: %d\n", test);
        exit(7);
    }

    // Zmienna do przechowywania wartości oczekiwanego wyniku
    int oczekiwana = atoi(argv[1]) * atoi(argv[2]);

    // Przywrócenie miejca wypisywania
    printf("\033[%d;%dH", atoi(argv[1]) + 3, 1);

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