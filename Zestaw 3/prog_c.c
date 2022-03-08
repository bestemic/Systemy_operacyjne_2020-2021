#define _POSIX_C_SOURCE 200112L
#define _XOPEN_SOURCE 500

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

// Obsługa błędu funkcji getpgid()
pid_t getpgid_check(pid_t pid)
{
    pid_t processg_id = getpgid(pid);
    if (processg_id == -1)
    {
        perror("getpgid error");
        exit(EXIT_FAILURE);
    }
    else
        return processg_id;
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

    int status;

    // Stworzenie procesu potomnego
    pid_t pid = fork();
    switch (pid)
    {
    case -1:
        perror("fork error");
        exit(1);
    case 0:
        // Ignorowanie sygnału
        if (atoi(argv[1]) != 9 && atoi(argv[1]) != 19)
        {
            if (signal(atoi(argv[1]), SIG_IGN) == SIG_ERR)
            {
                perror("signal error");
                exit(EXIT_FAILURE);
            }
        }
        else //Obsługa sygnału KILL i STOP
        {
            printf("Sygnalu SIGKILL oraz SIGSTOP nie mozna ignorowac, po odebraniu sygnalu zostanie wykonana jego operacja domyslna\n");
        }

        // Ustawienie lidera nowej grupy procesów
        if (setpgid(0, 0) == -1)
        {
            perror("setpgid error");
            exit(1);
        }

        // Utworzenie kilku nowych procesów
        for (int i = 0; i < 3; i++)
        {
            switch (fork())
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
                break;
            }
        }

        // Oczekiwanie na zakończenie procesów i wypisanie ich statusu zakończenia
        printf("Statusy zakonczenia procesow potomnych:\n");
        wait(&status);
        printf("%d\n", WEXITSTATUS(status));
        wait(&status);
        printf("%d\n", WEXITSTATUS(status));
        wait(&status);
        printf("%d\n", WEXITSTATUS(status));

        _exit(0);
    default:
        sleep(3);

        // Sprawdzenie czy proces do któego wysyłamy sygnał istnieje
        if (kill(-getpgid_check(pid), 0) == -1)
        {
            perror("kill error");
            exit(1);
        }

        // Wysłanie sygnału do procesu, obsłóga błędu w razie niepowodzenia
        if (kill(-getpgid_check(pid), atoi(argv[1])) == -1)
        {
            perror("kill error");
            exit(1);
        }

        wait(NULL);
    }

    return 0;
}