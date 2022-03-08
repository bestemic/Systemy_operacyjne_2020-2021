#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

void koniec(void)
{
    printf("Koniec programu!\n");
}

// Funkcja własnej obsługi sygnału
void my_sighandler(int sygnal)
{
    printf("Przechwycilem sygnal numer: %d\n", sygnal);
}

int main(int argc, char *argv[])
{
    // Rejestracja funkcji wywołanych przez exit()
    if (atexit(koniec) != 0)
    {
        perror("atexit error");
        exit(EXIT_FAILURE);
    }

    // Sprawdzenie poprawnosci parametrów
    if ((argc != 3) && (argc != 2))
    {
        printf("Nieprawidlowa ilosc argumentow, nie mozna uruchomic programu\n");
        exit(EXIT_FAILURE);
    }

    // Wypisanie PID pomocnego przy korzystaniu z kill()
    // Usunąć poniższy komentarz aby widzieć jaki mamy proces
    //printf("PID obecnego procesu: %d\n\n", getpid());

    // Konwersja na int numeru sygnalu
    int sygnal = atoi(argv[1]);

    // Obsługa sygnałów różnych od SIGKILL i SIGSTOP
    if ((sygnal != 9) && (sygnal != 19))
    {
        // Obsługa domyślna sygnału gdy nie podano jego sposobó obsługi
        if (argc == 2)
        {
            printf("Nie podano opcji obslugi dla podanego sygnalu, wykonam opcje domyslna po przechwyceniu sygnalu\n");
            if (signal(sygnal, SIG_DFL) == SIG_ERR)
            {
                perror("signal error");
                exit(EXIT_FAILURE);
            }
        }

        // Obsługa sygnałów gdy podano sposób obługi
        if (argc == 3)
        {
            switch (atoi(argv[2]))
            {
            case 1:
                // Wykonanie operacji domyślnej
                if (signal(sygnal, SIG_DFL) == SIG_ERR)
                {
                    perror("signal error");
                    exit(EXIT_FAILURE);
                }
                break;
            case 2:
                // Ignorowanie sygnału
                if (signal(sygnal, SIG_IGN) == SIG_ERR)
                {
                    perror("signal error");
                    exit(EXIT_FAILURE);
                }
                break;
            case 3:
                // Przechwycenie sygnału
                if (signal(sygnal, my_sighandler) == SIG_ERR)
                {
                    perror("signal error");
                    exit(EXIT_FAILURE);
                }
                break;
            default:
                printf("Podano niepoprawna opcje obslugi\n");
                exit(EXIT_FAILURE);
            }
        }
    }
    else    // Obsługa sygnału SIGKILL i SIGSTOP
    {
        printf("Sygnalu SIGKILL oraz SIGSTOP nie mozna obslugiwac funkcją signal(), ");
        printf("po odebraniu sygnalu zostanie wykonana jego operacja domyslna\n");
    }

    // Oczekiwanie na sygnał
    printf("Czekam na sygnal...\n");
    pause();

    return 0;
}