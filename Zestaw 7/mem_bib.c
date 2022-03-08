#include "mem_bib.h"

// Funkcja tworząca pamięć dzieloną i podanej nazwie i długości
void mem_create(const char *name, int length)
{
    // Zmienna do przechowywania deskryptora pamięci dzielonej
    int fd;

    // Utworzenie pamięci dzielonej
    fd = shm_open(name, O_CREAT | O_EXCL | O_RDWR, 0644);

    // Obsługa błędu funkcji shm_open
    if (fd == -1)
    {
        perror("shm_open error");
        exit(5);
    }

    // Ustawienie rozmiaru obiektu pamięci dzielonej i obsługa błędu funkcji ftruncate
    if (ftruncate(fd, length) == -1)
    {
        perror("ftruncate error");
        exit(5);
    }

    // Zamknięcie deskryptora pamięci dzielonej
    mem_close(fd);
}

// Funkcja otwierająca obiekt pamięci dzielonej i zwracająca jej deskryptor
int mem_open(const char *name)
{
    // Zmienna do przechowywania deskryptora pamięci dzielonej
    int fd;

    // Otwarcie obiektu pamięci dzielonej
    fd = shm_open(name, O_RDWR, 0644);

    // Obsługa błędu funkcji shm_open
    if (fd == -1)
    {
        perror("shm_open error");
        exit(5);
    }

    // Zwrócenie deskryptora pamiędzi dzielonej
    return fd;
}

// Funkcja zamykająca podany deskryptor
void mem_close(int fd)
{
    // Zamknięcie deskryptora i obsługa błędu funkcji close
    if (close(fd) == -1)
    {
        perror("close error");
        exit(5);
    }
}

// Funkcja usuwająca pamięć dzieloną
void mem_delate(const char *name)
{
    // Usunięcie pamięci dzielonej i obsługa błędu funkcji shm_unlink
    if (shm_unlink(name) == -1)
    {
        perror("shm_unlink error");
        exit(5);
    }
    else
    {
        printf("Poprawnie usunieto pamiec dzielona\n");
    }
}

// Funkcja odwzorowująca pamięć dzieloną i zwracająca adres odwzorowanego obszaru
void *mem_map(int length, int fd)
{
    // Odwzorowanie pamięci dzielonej
    SegmentPD *addr = (SegmentPD *)mmap(NULL, length, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);

    // Obsługa błędu funkcji mmap
    if (addr == MAP_FAILED)
    {
        perror("mmap error");
        exit(5);
    }

    // Zwrócenie adresu odwzorowania
    return addr;
}

// Funkcja usuwająca odwzorowanie pamięci dzielonej
void mem_unmap(void *addr, int length)
{
    // Usunięcie odwzorowania pamięci dzielonej i obsługa funkcji munmap
    if (munmap(addr, length) == -1)
    {
        perror("munmap error");
        exit(5);
    }
}