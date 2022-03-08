#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <time.h>

void koniec(void)
{
    printf("\nKoniec procesu główego!\n\n");
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

    // Sprawdzenie czy podano nazwy plikówe wejściowych i wyjściowych
    if (argc != 3)
    {
        printf("Nie podano plikow wejsciowych i wyjsciowych \n");
        exit(1);
    }

    // Aktywowanie generatora liczb pseudolosowych
    srand(time(NULL));

    // Utworzenie zmiennej na przechowywanie deskryptorów
    int fd[2];

    // Utworzenie potoku
    if (pipe(fd) == -1)
    {
        perror("pipe error");
        exit(1);
    }

    // Utworzenie procesu potomengo
    switch (fork())
    {
    case -1:
        perror("fork error");
        exit(2);
    case 0:
        // Konsument

        // Zamknięcie zapisywania do potoku
        close(fd[1]);

        // Otworzenie pliku wyjściowego
        int wyjscie = open(argv[2], O_RDWR | O_TRUNC, 0666);

        // Obsługa błędu otwarcia pliku wyjściowego
        if (wyjscie == -1)
        {
            perror("opening file error");
            _exit(1);
        }

        // Zmienne pomocnicze
        int dataKons;
        char outBuff[3];
        char infoKons[40] = "\nKonsument odczytal i zapisuje: ";

        // Odczytywanie danych z potoku
        while (1)
        {
            // Pobranie danych z potoku
            dataKons = read(fd[0], outBuff, sizeof(outBuff));

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

        // Zamknięcie oczytywania z potoku
        close(fd[0]);

        // Zamknięcie pliku wejściowego
        close(wyjscie);

        _exit(0);
    default:
        // Producent

        // Zamknięcie odczytywania z potoku
        close(fd[0]);

        // Otworzenie pliku wejściowego
        int wejscie = open(argv[1], 0444);

        // Obsługa błędu otwarcia pliku wejściowego
        if (wejscie == -1)
        {
            perror("opening file error");
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

            // Wysyłanie do potoku
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

                // Wysyłanie tekstu do potoku i obsługa funkcji write
                if (write(fd[1], inBuff, sizeof(char) * dataProd) == -1)
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

        // Zamknięcie zapisywania do potoku
        close(fd[1]);

        // Zamknięcie pliku wejściowego
        close(wejscie);

        // Oczekiwanie na zakończenie pracy konsumenta
        wait(NULL);
    }

    return 0;
}