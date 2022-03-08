#include "mes_bib.h"
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>
#include <time.h>

// Zmienna na deskrytory kolejek serwera
mqd_t serwdes;

void koniec(void)
{
    // Zamknięcie kolejki komunikatów serwera
    mes_close(serwdes);

    // Usunięcie kolejki komunikatów serwera
    mes_delate(SERWER);

    printf("\nKoniec procesu!\n\n");
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

    // Zmienna na deskrytory kolejek serwera
    mqd_t konsdes;

    // Bufory na wiadomość i nazwę kolejki klienta
    char message[30];
    char nazwa[6];

    // Zmienne na dane pobrane z wiadomości
    int pid;
    int iterator;
    char *tmp;
    int a = 0, b = 0;
    char znak[1] = {0};
    int result = 0;
    int zero = 0;

    // Utworenie kolejki komunikatów serwera
    mes_create(SERWER);

    // Otworzenie kolejki komunikatów serwera
    serwdes = mes_open(SERWER, O_RDONLY);

    // Pobranie informacji o kolejce
    printf("Utworzono kolejkę o nazwie: %s i deskryptorze %d\n", SERWER, serwdes);
    mes_getattr(serwdes);
    printf("\n");

    // Obsługa wiadomości
    while (1)
    {
        // Odczytanie wiadomości z kolejki serwera
        mes_get(serwdes, message, sizeof(message) / sizeof(char));
        printf("Otrzymana wiadomosc: %s\n", message);

        // Oddzielenie pierwszej części wiadomosci po napotkaniu spacji
        tmp = strtok(message, " ");

        // Pobranie fragmentu nazwy kolejki klienta
        pid = atoi(tmp);

        iterator = 1;

        // Dzielenie reszty wiadomości
        while (tmp != NULL)
        {
            // Podział gdy spacja
            tmp = strtok(NULL, " ");

            if (iterator == 1)
            {
                // Pobranie pierwszej liczby
                a = atoi(tmp);
            }
            if (iterator == 2)
            {
                // Pobranie znaku
                strcpy(znak, tmp);
            }
            if (iterator == 3)
            {
                // Pobranie drugiej liczby
                b = atoi(tmp);
            }

            iterator++;
        }

        //  Wykonywanie działań
        switch (znak[0])
        {
        case '+':
            result = a + b;
            break;
        case '-':
            result = a - b;
            break;
        case '*':
            result = a * b;
            break;
        case '/':
            if (b == 0)
            {
                // Obsługa błędu dzielenia przez 0
                printf("Dzielenie przez 0\n");

                // Utworzenie treści komunikatu i obsługa błędu funkcji sprintf
                if (sprintf(message, "divide by 0") < 0)
                {
                    perror("sprintf error");
                    exit(5);
                }

                zero = 1;
            }
            else
            {
                result = a / b;
            }

            break;
        }

        if (!zero)
        {
            // Utworzenie treści komunikatu i obsługa błędu funkcji sprintf
            if (sprintf(message, "%d", result) < 0)
            {
                perror("sprintf error");
                exit(5);
            }
        }

        // Wypisanie wysyłanej wiadomości
        printf("Wysylam wiadomosc: %s\n", message);

        // Utworzenie nazwy kolejki klienta
        if (sprintf(nazwa, "/%d", pid) < 0)
        {
            perror("sprintf error");
            exit(5);
        }

        // Losowe uśpienie
        sleep(czas());

        // Otworzenie kolejki komunikatów klienta
        konsdes = mes_open(nazwa, O_WRONLY);

        // Wysłanie wiadomości do kolejki komunikatów klienta
        mes_put(konsdes, message, sizeof(message) / sizeof(char));

        // Zamknięcie kolejki komunikatów klienta
        mes_close(konsdes);

        // Wyczyszczenie buforów
        memset(message, 0, strlen(message));
    }

    return 0;
}