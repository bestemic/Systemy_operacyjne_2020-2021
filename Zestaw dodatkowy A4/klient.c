#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

// Bufor na nazwę kolejki klienta
char nazwa[6];

// Zmienne na deskryptry potoków
int konsdes;
int serwdes;

#define SERWER "serwer"

void koniec(void)
{
    // Zamknięcie deskryptorów potoków
    close(konsdes);
    close(serwdes);

    // Usunięcię potoku nazwanego konsumanta
    unlink(nazwa);

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

    // Czas na utworzenie się potoku nazwanego serwera
    sleep(1);

    // PID obecnego procesu
    pid_t pid = getpid();

    // Bufory na wiadomość i pobrane dane
    char wiersz[24];
    char message[30];

    // Utworzenie nazwy potoku nazwanego klienta i obsługa błędu funkcji sprintf
    if (sprintf(nazwa, "%d", pid) < 0)
    {
        perror("sprintf error");
        exit(5);
    }

    // Tworzenie potoku nazwanego klienta
    if (mkfifo(nazwa, 0644) == -1)
    {
        perror("mkfifo error");
        exit(1);
    }

    // Otworzenie potoku nazwanego serwera
    serwdes = open(SERWER, 0222);

    // Obsługa błędu otwarcia potoku nazwanego
    if (serwdes == -1)
    {
        perror("opening named pipe file error");
        exit(1);
    }

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

        // Wysłanie wiadomości do potoku serwera
        if (write(serwdes, message, sizeof(message)) == -1)
        {
            perror("write error");
            exit(4);
        }

        // Wyczyszczenie buforu wiadomości
        memset(message, 0, strlen(message));

        // Losowe uśpienie
        sleep(czas());

        // Otworzenie potoku nazwanego klienta
        konsdes = open(nazwa, 0444);

        // Obsługa błędu otwarcia potoku nazwanego
        if (konsdes == -1)
        {
            perror("opening named pipe file error");
            exit(1);
        }

        // Odczytanie wiadomości z potoku klienta i onsługa błedu funkcji read
        if (read(konsdes, message, sizeof(message)) == -1)
        {
            perror("read error");
            exit(3);
        }

        printf("Otrzymany wynik: %s\n", message);

        // Wyczyszczenie buforów
        memset(wiersz, 0, strlen(wiersz));
        memset(message, 0, strlen(message));

        printf("Prosze podac dzialanie - oddzielic spacjami: ");
    }

    printf("Zakonczono wczytywanie polecen\n");

    return 0;
}