#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define SERWER "serwer"

// Zmienne na deskryptor kolejki
int serwdes;

void koniec(void)
{
    // Zamknięcie deskryptora serwera
    close(serwdes);

    // Usunięcie potoku nazwanego serwera
    unlink(SERWER);

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

    // Bufory na wiadomość i nazwę potoku nazwanego klienta
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

    // Tworzenie potoku nazwanego serwera
    if (mkfifo(SERWER, 0644) == -1)
    {
        perror("mkfifo error");
        exit(1);
    }

    // Otworzenie potoku nazwanego serwera
    serwdes = open(SERWER, 0444);

    // Obsługa błędu otwarcia potoku nazwanego
    if (serwdes == -1)
    {
        perror("opening named pipe file error");
        exit(1);
    }

    // Obsługa wiadomości
    while (1)
    {
        // Odczytanie wiadomości z potoku serwera i bsługa błędu funkcji open
        if (read(serwdes, message, sizeof(message)) == -1)
        {
            perror("read error");
            exit(3);
        }

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

        // Utworzenie nazwy potoku klienta
        if (sprintf(nazwa, "%d", pid) < 0)
        {
            perror("sprintf error");
            exit(5);
        }

        // Losowe uśpienie
        sleep(czas());

        // Otworzenie potoku nazwanego klienta
        int konsdes = open(nazwa, 0222);

        // Obsługa błędu otwarcia potoku nazwanego
        if (konsdes == -1)
        {
            perror("opening named pipe file error");
            exit(1);
        }

        // Wysłanie wiadomości do potoku klienta
        if (write(konsdes, message, sizeof(message)) == -1)
        {
            perror("write error");
            exit(4);
        }

        // Zamknięcie potoku klienta
        close(konsdes);

        // Wyczyszczenie buforów
        memset(message, 0, strlen(message));
    }

    return 0;
}