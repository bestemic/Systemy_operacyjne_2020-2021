#include "mes_bib.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <time.h>

// Bufor na nazwę kolejki klienta
char nazwa[6];

// Zmienne na deskryptry kolejek
mqd_t konsdes;
mqd_t serwdes;

void koniec(void)
{
    // Zamknięcie kolejek komunikatów
    mes_close(konsdes);
    mes_close(serwdes);

    // Usunięcię kolejki komunkatów konsumanta
    mes_delate(nazwa);

    printf("\nKoniec procesu!\n");
}

// Funkcja własnej obsługi sygnału przerwania programu
void my_sighandler(int sygnal)
{
    printf("\nOtrzymalem sygnal przerwania");
    exit(0);
}

// Funkcja losująca ile sekund ma oczekiwać proces (od 0 do 4)
unsigned int czas(void)
{
    return rand() % 5;
}

int main(int argc, char *argv[])
{

    // Rejestracja funkcji wywołanych przez exit()
    if (atexit(koniec) != 0)
    {
        perror("atexit error");
        exit(EXIT_FAILURE);
    }

    // Przechwycenie sygnału
    if (signal(SIGINT, my_sighandler) == SIG_ERR)
    {
        perror("signal error");
        exit(EXIT_FAILURE);
    }

    // Aktywowanie generatora liczb pseudolosowych
    srand(time(NULL));

    // Czas na utworzenie się kolejki serwera
    sleep(1);

    // PID obecnego procesu
    pid_t pid = getpid();

    // Bufory na wiadomość i pobrane dane
    char wiersz[24];
    char message[30];

    // Utworzenie nazwy kolejki komunikatów klienta i obsługa błędu funkcji sprintf
    if (sprintf(nazwa, "/%d", pid) < 0)
    {
        perror("sprintf error");
        exit(5);
    }

    // Utworenie kolejki komunikatów klienta
    mes_create(nazwa);

    // Otworzenie kolejki komunikatów klienta
    konsdes = mes_open(nazwa, O_RDONLY);

    // Pobranie informacji o kolejce
    printf("Utworzono kolejkę o nazwie: %s i deskryptorze %d\n", nazwa, konsdes);
    mes_getattr(konsdes);
    printf("\n");

    // Otworzenie kolejki komunikatów serwera
    serwdes = mes_open(SERWER, O_WRONLY);

    printf("Prosze podac dzialanie - oddzielic spacjami: ");

    // Wczytywanie działań
    while (fgets(wiersz, sizeof(wiersz) / sizeof(char), stdin) != NULL)
    {
        // Usunięcie znaku nowej linni z końca wiadomości
        wiersz[strcspn(wiersz, "\n")] = 0;

        // Utworzenie treści komunikatu i obsługa błędu funkcji sprintf
        if (sprintf(message, "%d %s", pid, wiersz) < 0)
        {
            perror("sprintf error");
            exit(5);
        }

        // Wypisanie wysyłanej wiadomości
        printf("Wysylam wiadomosc: %s\n", message);

        // Wysłanie wiadomości do kolejki komunikatów serwera
        mes_put(serwdes, message, sizeof(message) / sizeof(char));

        // Wyczyszczenie buforu wiadomości
        memset(message, 0, strlen(message));

        // Losowe uśpienie
        sleep(czas());

        // Odczytanie wiadomości z kolejki klienta
        mes_get(konsdes, message, sizeof(message) / sizeof(char));
        printf("Otrzymany wynik: %s\n", message);

        // Wyczyszczenie buforów
        memset(wiersz, 0, strlen(wiersz));
        memset(message, 0, strlen(message));

        printf("Prosze podac dzialanie - oddzielic spacjami: ");
    }

    printf("Zakonczono wczytywanie polecen\n");

    return 0;
}