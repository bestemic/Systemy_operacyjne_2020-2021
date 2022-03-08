#include "biblioteka.h"
#include <wait.h>
#include <signal.h>
#include <sys/types.h>

// Zdefiniowanie makr z nazwami
#define SEM_NAME "/semafor"
#define NUM "numer.txt"

void koniec(void)
{
    // Wywolanie funkcji usuwającej semafor
    semafor_delate(SEM_NAME);

    // Usunięcie pliku numer.txt i obsługa błędu funkcji unlink
    if (unlink(NUM) == 0)
    {
        printf("Poprawnie usunieto plik");
    }
    else
    {
        perror("file delating error");
    }

    printf("\nKoniec procesu!\n\n");
}

// Funkcja własnej obsługi sygnału przerwania programu
void my_sighandler(int sygnal)
{
    printf("\nOtrzymalem sygnal przerwania");
    exit(0);
}

int main(int argc, char *argv[])
{

    // Rejestracja funkcji wywołanych przez exit()
    if (atexit(koniec) != 0)
    {
        perror("atexit error");
        exit(EXIT_FAILURE);
    }

    // Sprawdzenie czy podano odpowiednią ilość argumentów
    if (argc != 4)
    {
        printf("Zla ilosc argumentow wywolania programu \n");
        _exit(1);
    }

    // Utworzenie pliku numer.txt i otworzenie go
    int fd = open(NUM, O_CREAT | O_EXCL | O_RDWR | O_TRUNC, 0644);

    // Obługa błędu funkcji open
    if (fd == -1)
    {
        perror("creating and opening file error");
        _exit(4);
    }

    // Wpisanie do pliku numer.txt wartości '0' i obsługa błędu funkcji write
    if (write(fd, "0", sizeof(char)) == -1)
    {
        perror("write error");
        _exit(4);
    }

    // Zamknięcie pliku
    close(fd);

    // Zmienna do przechowywania adresu semafora
    sema adres;

    // Tablica znaków do przechowywania wartości odczytenej z pliku numer.txt
    char zawartosc[20];

    // Wywołanie funkcji tworzącej semafor nazwany
    semafor_create(SEM_NAME);

    printf("Semafor został utworzony\n");
    printf("------------------------\n");
    printf("Nazwa semafora: ");
    printf(SEM_NAME);

    // Wywołanie funkcji otwierającej semafor nazwany i zwracającej jego adres
    adres = semafor_open(SEM_NAME);
    printf("\nAdres semafora: %lx\n", (long int)adres);

    // Wywołanie funkcji wypisującej wartość semafora
    semafor_value(adres);

    printf("------------------------\n\n");

    // Przechwycenie sygnału
    if (signal(SIGINT, my_sighandler) == SIG_ERR)
    {
        perror("signal error");
        exit(EXIT_FAILURE);
    }

    // Utworzenie procesów potomnych
    for (int i = 0; i < atoi(argv[2]); i++)
    {
        switch (fork())
        {
        case -1:
            perror("fork error");
            exit(1);
        case 0:
            // Uruchomienie programu wzajemnego wykluczania
            execl(argv[1], argv[1], SEM_NAME, argv[3], NUM, NULL);
            perror("execl error");
            _exit(1);
        }
    }

    // Oczekiwanie na zakończenie się wszystkich procesów potomnych
    for (int i = 0; i < atoi(argv[2]); i++)
    {
        wait(NULL);
    }

    // Otworzenie pliku numer.txt do odczytu
    fd = open(NUM, 0444);

    // Obsługa błędów funkcji open
    if (fd == -1)
    {
        perror("opening file error");
        exit(4);
    }

    // Pobranie danych z pliku i obsługa błędów funkcji read
    if (read(fd, zawartosc, sizeof(zawartosc)) == -1)
    {
        perror("read error");
        exit(3);
    }

    // Zamknięcie pliku
    close(fd);

    // Wypisanie liczby z pliku
    printf("\n------------------------\n");
    printf("Liczba w pliku to: %s\n", zawartosc);

    // Porównanie czy liczba w pliku jest taka jak oczekiwana wartość
    if (atoi(zawartosc) == (atoi(argv[2]) * atoi(argv[3])))
    {
        printf("Liczba z pliku zgadza sie z oczekiwana liczba");
    }
    else
    {
        printf("Liczba z pliku nie zgadza sie z oczekiwana liczba");
    }

    return 0;
}