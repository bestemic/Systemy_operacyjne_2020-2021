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

    // Otworzenie pliku wejściowego
    int wejscie = open(argv[1], 0444);

    // Obsługa błędu otwarcia pliku wejściowego
    if (wejscie == -1)
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
    printf("    PRODUCENT: adres semafora %s: %p\n", argv[2], (void *)adresprod);
    printf("    PRODUCENT: adres semafora %s: %p\n", argv[3], (void *)adreskons);

    // Zmianna do przechowywania deskryptora pamięci dzielonej
    int memorydes;

    // Wywołanie funkcji otwierającej pamięć dzieloną i zwracającej jej deskryptor
    memorydes = mem_open(argv[4]);
    printf("    PRODUCENT: deskryptor pamięci dzielonej: %d\n", memorydes);

    // Zmianna do przechowywania adresu odwzorowania pamięci dzelonej
    SegmentPD *addr;

    // Wywołanie funkcji odwzorowującej pamięc dzeloną
    addr = mem_map(sizeof(SegmentPD), memorydes);

    // Zmienna do przechowywania ilości odczytanych bajtów
    int dataProd;

    // Wczytywnie danych z pliku
    while (1)
    {
        // Wywołanie funkcji opuszczającej semafor producenta
        semafor_wait(adresprod);

        // Pobranie kilku bajtów danych i zapis ich do wspólnego bufora
        dataProd = read(wejscie, addr->bufor[addr->wstaw], sizeof(addr->bufor[addr->wstaw]));

        // Obsługa błędu funkcji read
        if (dataProd == -1)
        {
            perror("read error");
            exit(3);
        }

        if (dataProd >= 0)
        {
            // Wypisywanie do konsoli przesyłanego tekstu i informacji o programie
            printf("PRODUCENT - semprod: ");
            semafor_value(adresprod);
            printf(", semkons: ");
            semafor_value(adreskons);
            printf(", indeks buforu: %d, ilosc bajtow: %d, %.*s\n", addr->wstaw, dataProd, dataProd, addr->bufor[addr->wstaw]);

            // Zakończenie pobierania gdy koniec pliku
            if (dataProd < NELE)
            {
                // Zapisanie na koniec pobierania danych znaku \0
                addr->bufor[addr->wstaw][dataProd] = '\0';

                // Wpisanie do struktury ilości zapisanych ostatnich danych
                addr->end = dataProd;

                // Wywołanie funkcji podnoszącej semafor konsumenta
                semafor_post(adreskons);

                // Zakończenie pętli
                break;
            }

            // Przesunięcie pozycji wstawiania
            addr->wstaw = (addr->wstaw + 1) % NBUF;
        }

        // Wywołanie funkcji podnoszącej semafor konsumenta
        semafor_post(adreskons);
    }

    // Zamknięcie semaforów nazwanych
    semafor_close(adresprod);
    semafor_close(adreskons);

    // Zamknięcie odwzorowania pamięci dzielonej
    mem_unmap(addr, sizeof(SegmentPD));

    // Zamknięcie deskryptorów
    mem_close(memorydes);
    mem_close(wejscie);

    return 0;
}