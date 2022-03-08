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

    // Sprawdzenie czy podano plik wyjściowy i nazwę potoku
    if (argc != 3)
    {
        printf("Nie podano argumentow wywolania \n");
        exit(1);
    }

    // Aktywowanie generatora liczb pseudolosowych
    srand(time(NULL));

    // Otworzenie pliku wyjściowego
    int wyjscie = open(argv[1], O_RDWR | O_TRUNC, 0666);

    // Obsługa błędu otwarcia pliku wyjściowego
    if (wyjscie == -1)
    {
        perror("opening file error");
        _exit(1);
    }

    // Otworzenie potoku nazwanego do odczytu
    int fd = open(argv[2], 0444);

    // Obsługa błędu otwarcia potoku nazwanego
    if (fd == -1)
    {
        perror("opening named pipe file error");
        exit(1);
    }

    // Zmienne pomocnicze
    int dataKons;
    char outBuff[3];
    char infoKons[40] = "\nKonsument odczytal i zapisuje: ";

    // Odczytywanie danych z potoku nazwanego
    while (1)
    {
        // Pobranie danych z potoku nazwanego
        dataKons = read(fd, outBuff, sizeof(outBuff));

        // Obsługa błędu funkcji read
        if (dataKons == -1)
        {
            perror("read error");
            exit(3);
        }

        // Zapisanie do pliku
        if (dataKons > 0)
        {
            // Wypisywanie do konsoli odebranego tekstu i obsługa funkcji write
            if (write(0, infoKons, sizeof(infoKons)) == -1)
            {
                perror("write error");
                exit(4);
            }
            if (write(0, outBuff, sizeof(char) * dataKons) == -1)
            {
                perror("write error");
                exit(4);
            }

            // Zapisanie tekstu do pliku i obsługa błędu funkcji write
            if (write(wyjscie, outBuff, sizeof(char) * dataKons) == -1)
            {
                perror("write error");
                exit(4);
            }

            sleep(czas());
        }

        // Zakończenie pobierania gdy brak danych w potoku
        if (dataKons == 0)
        {
            break;
        }
    }

    // Zamknięcie oczytywania z potoku nazwanego
    close(fd);

    // Zamknięcie pliku wejściowego
    close(wyjscie);

    return 0;
}