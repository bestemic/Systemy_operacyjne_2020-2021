#include "mem_bib.h"
#include "sem_bib.h"
#include <wait.h>
#include <signal.h>
#include <sys/types.h>

// Zdefiniowanie makr z nazwami
#define SEM_NAME_PROD "/semaforprod"
#define SEM_NAME_KONS "/semaforkons"
#define MEMORY "/memory"

// Zmienna do przechowywania ilości stworzonych plików
int test = 0;

void koniec(void)
{
    printf("\n");

    // Wywolanie funkcji usuwającej semafory i pamięć dzieloną
    if (test != 0)
    {
        semafor_delate(SEM_NAME_PROD);
        if (test != 1)
        {
            semafor_delate(SEM_NAME_KONS);
            if (test != 2)
            {
                mem_delate(MEMORY);
            }
        }
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
    if (argc != 5)
    {
        printf("Zla ilosc argumentow wywolania programu \n");
        _exit(1);
    }

    // Zmienne do przechowywania adresów semaforów
    sema adresprod;
    sema adreskons;

    // Wywołanie funkcji tworzącej semafor nazwany dla producenta
    semafor_create(SEM_NAME_PROD, NBUF);
    test++;

    printf("Semafor producenta zostal utworzony\n");
    printf("------------------------\n");
    printf("Nazwa semafora: ");
    printf(SEM_NAME_PROD);

    // Wywołanie funkcji otwierającej semafor nazwany i zwracającej jego adres
    adresprod = semafor_open(SEM_NAME_PROD);
    printf("\nAdres semafora: %p\n", (void *)adresprod);

    // Wywołanie funkcji wypisującej wartość semafora
    semafor_value(adresprod);

    printf("------------------------\n");

    // Wywołanie funkcji tworzącej semafor nazwany dla konsumenta
    semafor_create(SEM_NAME_KONS, 0);
    test++;

    printf("Semafor konsumenta zostal utworzony\n");
    printf("------------------------\n");
    printf("Nazwa semafora: ");
    printf(SEM_NAME_KONS);

    // Wywołanie funkcji otwierającej semafor nazwany i zwracającej jego adres
    adreskons = semafor_open(SEM_NAME_KONS);
    printf("\nAdres semafora: %p\n", (void *)adreskons);

    // Wywołanie funkcji wypisującej wartość semafora
    semafor_value(adreskons);

    printf("------------------------\n");

    // Zmianna do przechowywania deskryptora pamięci dzielonej
    int memorydes;

    // Wywołanie funkcji tworzącej pamięć dzieloną
    mem_create(MEMORY, sizeof(SegmentPD));
    test++;

    printf("Pamiec dzelona zostala utworzona\n");
    printf("------------------------\n");
    printf("Nazwa pamieci dzielonej: ");
    printf(MEMORY);

    // Wywołanie funkcji otwierającej pamięć dzieloną i zwracającej jej deskryptor
    memorydes = mem_open(MEMORY);

    printf("\nDeskryptor pamięci dzielonej: %d\n", memorydes);
    printf("Rozmiar pamięci dzielonej: %ld\n", sizeof(SegmentPD));
    printf("------------------------\n\n");

    // Zmianna do przechowywania adresu odwzorowania pamięci dzelonej
    SegmentPD *addr;

    // Wywołanie funkcji odwzorowującej pamięc dzeloną
    addr = mem_map(sizeof(SegmentPD), memorydes);

    // Zainicjowanie iteratorów struktury początkowymi wartoścami
    addr->wstaw = 0;
    addr->wyjmij = 0;

    // Przechwycenie sygnału
    if (signal(SIGINT, my_sighandler) == SIG_ERR)
    {
        perror("signal error");
        exit(EXIT_FAILURE);
    }

    // Utworzenie dwóch procesów potomnych
    for (int i = 0; i < 2; i++)
    {

        switch (fork())
        {
        case -1:
            perror("fork error");
            exit(2);
        case 0:
            // Uruchomienie producenta
            if (i == 0)
            {
                execl(argv[1], argv[1], argv[3], SEM_NAME_PROD, SEM_NAME_KONS, MEMORY, NULL);
                perror("execl error");
                _exit(2);
            }

            // Uruchomienie konsumenta
            if (i == 1)
            {
                execl(argv[2], argv[2], argv[4], SEM_NAME_PROD, SEM_NAME_KONS, MEMORY, NULL);
                perror("execl error");
                _exit(2);
            }
        }
    }

    // Oczekiwanie na zakończenie się pracy producenta i konsumanta
    wait(NULL);
    wait(NULL);

    // Zamknięcie semaforów nazwanych
    semafor_close(adresprod);
    semafor_close(adreskons);

    // Zamknięcie odwzorowania pamięci dzielonej
    mem_unmap(addr, sizeof(SegmentPD));

    // Zamknięcie deskryptora pamięci dzielonej
    mem_close(memorydes);

    return 0;
}