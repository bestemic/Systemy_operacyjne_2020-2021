#include "sem_bib.h"

// Funkcja tworząca semafor o podanej nazwie i wartości
void semafor_create(const char *name, int value)
{
    // Zmienna do przechowywania adresu semafora
    sema adres;

    // Utworzenie semafora z wartością podaną przez użytkownika
    adres = sem_open(name, O_CREAT | O_EXCL, 0644, value);

    // Obsługa błędów funkcji sem_open
    if (adres == SEM_FAILED)
    {
        perror("sem_open error");
        exit(5);
    }

    // Wywołanie funkcji zamykającej semafor
    semafor_close(adres);
}

// Funkcja usuwająca semafor o podanej nazwie
void semafor_delate(const char *name)
{
    // Usunięcie semafora i obsługa błędu funkcji unlink
    if (sem_unlink(name) == -1)
    {
        perror("sem_unlink error");
    }
    else
    {
        printf("Poprawnie usunieto semafor\n");
    }
}

// Funkcja otwiwrająca semafor o podanej nazwie, zwraca typ sema i przechowyje adres semafora
sema semafor_open(const char *name)
{
    // Zmienna do przechowywania adresu semafora
    sema adres;

    // Otworzenie semafora o podanej nazwie
    adres = sem_open(name, 0);

    // Obsługa błędów funkcji sem_open
    if (adres == SEM_FAILED)
    {
        perror("sem_open error");
        exit(5);
    }

    // Zwrócenie adresu semafora
    return adres;
}

// Funkcja zamykająca semafor o podanym adresie
void semafor_close(sema sem)
{
    // Zamknięcie semafora i obsłyga błędu funkcji sem_close
    if (sem_close(sem) == -1)
    {
        perror("sem_close error");
        exit(5);
    }
}

// Funkcja wypisująca wartość semafora o podanym adresie
void semafor_value(sema sem)
{
    // Zadeklarowanie zmiennej do przechowywania wartości semafora
    int value;

    // Pobranie wartość semafora i obsługa błędów funkcji sem_getvalue
    if (sem_getvalue(sem, &value) == -1)
    {
        perror("sem_getvalue error");
        exit(5);
    }

    // Wypisanie wartości semafora
    printf("%d", value);
}

// Funkcja podnosząca semafor o podanym adresie
void semafor_post(sema sem)
{
    // Podniesienie semafora i obsługa błędów funkcji sem_post
    if (sem_post(sem) == -1)
    {
        perror("sem_post error");
        exit(5);
    }
}

// Funkcja opuszczająca semafor o podanym adresie
void semafor_wait(sema sem)
{
    // Opuszczenie semafora i obsługa błędów funkcji sem_wait
    if (sem_wait(sem) == -1)
    {
        perror("sem_wait error");
        exit(5);
    }
}
