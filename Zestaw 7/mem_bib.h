#ifndef MEM_BIB_H
#define MEM_BIB_H

#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>

// Zdefinowanie wymiarów bufora
#define NBUF 6
#define NELE 11

// Struktura bufora danych
typedef struct
{
    char bufor[NBUF][NELE];
    int wstaw, wyjmij, end;
} SegmentPD;

// Funkcja tworząca pamięć dzieloną i podanej nazwie i długości
void mem_create(const char *name, int length);

// Funkcja otwierająca obiekt pamięci dzielonej i zwracająca jej deskryptor
int mem_open(const char *name);

// Funkcja zamykająca podany deskryptor
void mem_close(int fd);

// Funkcja usuwająca pamięć dzieloną
void mem_delate(const char *name);

// Funkcja odwzorowująca pamięć dzieloną i zwracająca adres odwzorowanego obszaru
void *mem_map(int length, int fd);

// Funkcja usuwająca odwzorowanie pamięci dzielonej
void mem_unmap(void *addr, int length);

#endif