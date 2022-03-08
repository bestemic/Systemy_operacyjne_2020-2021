#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <signal.h>

// Zdefiniowanie nazwy potoku
#define FIFO "potok"

// Funkcja własnej obsługi sygnału przerwania programu
void my_sighandler(int sygnal)
{
    printf("\nOtrzymalem sygnal przerwania");
    exit(0);
}

void koniec(void)
{
    // Usuwanie potoku nazwanego
    if (unlink(FIFO) == 0)
    {
        printf("\nPoprawnie usunieto potok\n");
    }
    else
    {
        perror("\nfile delating error");
    }
    printf("\nKoniec procesu główego!\n\n");
}

int main(int argc, char *argv[])
{

    // Rejestracja funkcji wywołanych przez exit()
    if (atexit(koniec) != 0)
    {
        perror("atexit error");
        exit(EXIT_FAILURE);
    }

    // Sprawdzenie czy podano nazwy plików wejściowych i wyjściowych
    if (argc != 3)
    {
        printf("Nie podano plikow wejsciowych i wyjsciowych \n");
        _exit(1);
    }

    // Tworzenie potoku nazwanego
    if (mkfifo(FIFO, 0644) == -1)
    {
        perror("mkfifo error");
        exit(1);
    }

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
                execl("producent.x", "producent.x", argv[1], FIFO, NULL);
                perror("execl error");
                _exit(2);
            }

            // Uruchomienie konsumenta
            if (i == 1)
            {
                execl("konsument.x", "konsument.x", argv[2], FIFO, NULL);
                perror("execl error");
                _exit(2);
            }
        }
    }

    // Oczekiwanie na zakończenie pracy producenta i konsumenta
    wait(NULL);
    wait(NULL);

    return 0;
}