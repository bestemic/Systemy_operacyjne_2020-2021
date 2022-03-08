#define _POSIX_C_SOURCE 200112L

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>

void koniec(void)
{
    printf("\nKoniec programu głównego\n");
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

    // Stworzenie procesu potomnego
    pid_t pid = fork();
    switch (pid)
    {
    case -1:
        perror("fork error");
        exit(1);
    case 0:
        // Wywołanie programu który obsługuje sygnały
        execl("./prog_a.x", "prog_a.x", argv[1], argv[2], NULL);
        perror("execl error");
        _exit(2);
    default:
        sleep(1);

        // Sprawdzenie czy proces do któego wysyłamy sygnał istnieje
        if (kill(pid, 0) == -1)
        {
            perror("kill error");
            exit(1);
        }

        // Wysłanie sygnału do procesu, obsłóga błędu w razie niepowodzenia
        if (kill(pid, atoi(argv[1])) == -1)
        {
            perror("kill error");
            exit(1);
        }

        wait(NULL);
    }

    return 0;
}