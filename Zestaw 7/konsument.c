#include "mem_bib.h"
#include "sem_bib.h"

int main(int argc, char *argv[])
{
    // Sprawdzenie czy podano odpowiednią ilość argumentów
    if (argc != 5)
    {
        printf("Nie podano argumentow wywolania \n");
        exit(1);
    }

    // Otworzenie pliku wyjściowego
    int wyjscie = open(argv[1], O_RDWR | O_TRUNC, 0666);

    // Obsługa błędu otwarcia pliku wyjściowego
    if (wyjscie == -1)
    {
        perror("opening file error");
        exit(1);
    }

    // Zmienne do przechowywania adresów semaforów
    sema adresprod;
    sema adreskons;

    // Wywołanie funkcji otwierających semafory nazwane i zwracających ich adresy
    adresprod = semafor_open(argv[2]);
    adreskons = semafor_open(argv[3]);
    printf("    KONSUMENT: adres semafora %s: %p\n", argv[2], (void *)adresprod);
    printf("    KONSUMENT: adres semafora %s: %p\n", argv[3], (void *)adreskons);

    // Zmianna do przechowywania deskryptora pamięci dzielonej
    int memorydes;

    // Wywołanie funkcji otwierającej pamięć dzieloną i zwracającej jej deskryptor
    memorydes = mem_open(argv[4]);
    printf("    KONSUMENT: deskryptor pamięci dzielonej: %d\n", memorydes);

    // Zmianna do przechowywania adresu odwzorowania pamięci dzelonej
    SegmentPD *addr;

    // Wywołanie funkcji odwzorowującej pamięc dzeloną
    addr = mem_map(sizeof(SegmentPD), memorydes);

    // Wczytywnie danych z pamięci dzelonej
    while (1)
    {
        // Wywołanie funkcji opuszczającej semafor konsumenta
        semafor_wait(adreskons);

        // Sprawdzenie czy znak końca przesyłania danych
        if (addr->bufor[addr->wyjmij][addr->end] == '\0')
        {
            // Wypisanie na konsolę ostatniej porcji danych i informacji o programie
            printf("KONSUMENT - semprod: ");
            semafor_value(adresprod);
            printf(", semkons: ");
            semafor_value(adreskons);
            printf(", indeks buforu: %d, ilosc bajtow: %d, %.*s\n", addr->wyjmij, addr->end, addr->end, addr->bufor[addr->wyjmij]);

            // Zapisanie ostatniej porcji tekstu do pliku i obsługa błędu funkcji write
            if (write(wyjscie, addr->bufor[addr->wyjmij], sizeof(char) * addr->end) == -1)
            {
                perror("write error");
                exit(4);
            }

            // Przerwanie pętli
            break;
        }
        else
        {

            // Wypisanie na konsolę przesyłanej porcji danych i informacji o programie
            printf("KONSUMENT - semprod: ");
            semafor_value(adresprod);
            printf(", semkons: ");
            semafor_value(adreskons);
            printf(", indeks buforu: %d, ilosc bajtow: %d, %.*s\n", addr->wyjmij, NELE, NELE, addr->bufor[addr->wyjmij]);

            // Zapisanie tekstu do pliku i obsługa błędu funkcji write
            if (write(wyjscie, addr->bufor[addr->wyjmij], sizeof(addr->bufor[addr->wyjmij])) == -1)
            {
                perror("write error");
                exit(4);
            }

            // Przesunięcie pozycji odczytu
            addr->wyjmij = (addr->wyjmij + 1) % NBUF;
        }

        // Wywołanie funkcji podnoszącej semafor producenta
        semafor_post(adresprod);
    }

    // Zamknięcie semaforów nazwanych
    semafor_close(adresprod);
    semafor_close(adreskons);

    // Zamknięcie odwzorowania pamięci dzielonej
    mem_unmap(addr, sizeof(SegmentPD));

    // Zamknięcie deskryptorów
    mem_close(memorydes);
    mem_close(wyjscie);

    return 0;
}