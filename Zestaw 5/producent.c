#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <time.h>

// Funkcja losująca ile sekund ma oczekiwać proces (od 0 do 4)
unsigned int czas(void)
{
    return rand() % 5;
}

int main(int argc, char *argv[])
{
    // Sprawdzenie czy podano plik wejsciowy i nazwę potoku
    if (argc != 3)
    {
        printf("Nie podano argumentow wywolania \n");
        exit(1);
    }

    // Aktywowanie generatora liczb pseudolosowych
    srand(time(NULL));

    // Otworzenie pliku wejściowego
    int wejscie = open(argv[1], 0444);

    // Obsługa błędu otwarcia pliku wejściowego
    if (wejscie == -1)
    {
        perror("opening file error");
        exit(1);
    }

    // Otworzenie potoku nazwanego do zapisu
    int fd = open(argv[2], 0222);

    // Obsługa błędu otwarcia potoku nazwanego
    if (fd == -1)
    {
        perror("opening named pipe file error");
        exit(1);
    }

    // Zmienne pomocnicze
    int dataProd;
    char inBuff[3];
    char infoProd[30] = "\nProducent pobral i wysyla: ";

    // Wczytywnie danych z pliku
    while (1)
    {
        // Pobranie kilku bajtów danych
        dataProd = read(wejscie, inBuff, sizeof(inBuff));

        // Obsługa błędu funkcji read
        if (dataProd == -1)
        {
            perror("read error");
            exit(3);
        }

        // Wysyłanie do potoku nazwanego
        if (dataProd > 0)
        {
            sleep(czas());

            // Wypisywanie do konsoli przesyłanego tekstu i obsługa funkcji write
            if (write(0, infoProd, sizeof(infoProd)) == -1)
            {
                perror("write error");
                exit(4);
            }
            if (write(0, inBuff, sizeof(char) * dataProd) == -1)
            {
                perror("write error");
                exit(4);
            }

            // Wysyłanie tekstu do potoku nazwanego i obsługa funkcji write
            if (write(fd, inBuff, sizeof(char) * dataProd) == -1)
            {
                perror("write error");
                exit(4);
            }
        }

        // Zakończenie pobierania gdy koniec pliku
        if (dataProd == 0)
        {
            break;
        }
    }

    // Zamknięcie zapisywania do potoku nazwanego
    close(fd);

    // Zamknięcie pliku wejściowego
    close(wejscie);

    return 0;
}