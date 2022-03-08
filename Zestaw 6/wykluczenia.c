#include "biblioteka.h"
#include "time.h"

// Funkcja losująca ile sekund ma oczekiwać proces (od 0 do 4)
unsigned int czas(void)
{
    return rand() % 5;
}

int main(int argc, char *argv[])
{
    // Sprawdzenie czy podano odpowiednią ilość argumentów
    if (argc != 4)
    {
        printf("Zla ilosc argumentow wywolania programu \n");
        _exit(1);
    }

    // Inicjacja generatora liczb pseudolosowych
    srand(time(NULL));

    // Zmienne do przechowywania adresu semafra, zawartości pliku i jego deskryptora oraz liczby
    sema adres;
    char zawartosc[20];
    int fd;
    int liczba;

    // Wywołanie funkcji otwierającej semafor nazwany i zwracającej jego adres
    adres = semafor_open(argv[1]);

    // Pętla symulująca różną ilość sekcji prywatnych i krytycznych
    for (int i = 1; i <= atoi(argv[2]); i++)
    {
        // Wypisanie informacji o obecnej sekcji
        printf("Sekcja prywatna przed sekcją krytyczną prosecu: %d. ", getpid());

        // Wywołanie funkcji wypisującej wartość semafora
        semafor_value(adres);

        // Losowe uśpienie przed sekcją krytyczną
        sleep(czas());

        // Wywołanie funkcji opuszczającej semafor
        semafor_wait(adres);

        //-------    SEKCJA KRYTYCZNA    -------//
        
        // Wypisanie informacji o obecnej sekcji
        printf("        Sekcja krytyczna nr %d, procesu: %d. ", i, getpid());
        
        // Wywołanie funkcji wypisującej wartość semafora
        semafor_value(adres);

        // Otworzenie pliku numer.txt do odczytu
        fd = open(argv[3], 0444);

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

        // Symulacja pracy sekcji krytycznej
        sleep(czas());

        // Konwersja tekstu na liczbę i jej zwiększenie
        liczba = atoi(zawartosc);
        printf("        Liczba odczytana w procesie %d z pliku: %d\n", getpid(), liczba);
        liczba++;

        // Zamiana sformtowanych danych na napis i obsłyga błędu funkcji sprintf
        if(sprintf(zawartosc, "%d", liczba)<0){
            perror("sprintf error");
            exit(2);
        }

        // Otworzenie pliku numer.txt do zapisu
        fd = open(argv[3], 0222);

        // Obsługa błędów funkcji open
        if (fd == -1)
        {
            perror("opening file error");
            exit(4);
        }

        // Wpisanie do pliku numer.txt wartości i obsługa błędu funkcji write
        if (write(fd, zawartosc, sizeof(zawartosc)) == -1)
        {
            perror("write error");
            exit(4);
        }

        // Zamknięcie pliku
        close(fd);

        //----    KONIEC SEKCJI KRYTYCZNEJ    ----//

        // Wywołanie funkcji podnoszącej semafor
        semafor_post(adres);

        // Wypisanie informacji o obecnej sekcji
        printf("Sekcja prywatna po sekcji krytycznej prosecu: %d. ", getpid());

        // Wywołanie funkcji wypisującej wartość semafora
        semafor_value(adres);
    }

    // Wywołanie funkcji zamykającej semafor nazwany
    semafor_close(adres);

    return 0;
}