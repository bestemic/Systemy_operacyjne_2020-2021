#ifndef SEM_BIB_H
#define SEM_BIB_H

#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <semaphore.h>
#include <sys/mman.h>
#include <unistd.h>

// Zmiana nazwy typu sem_t* na sema
typedef sem_t *sema;

// Funkcja tworząca semafor o podanej nazwie i wartości
void semafor_create(const char *name, int value);

// Funkcja usuwająca semafor o podanej nazwie
void semafor_delate(const char *name);

// Funkcja otwiwrająca semafor o podanej nazwie, zwraca typ sema i przechowyje adres semafora
sema semafor_open(const char *name);

// Funkcja zamykająca semafor o podanym adresie
void semafor_close(sema sem);

// Funkcja wypisująca wartość semafora o podanym adresie
void semafor_value(sema sem);

// Funkcja podnosząca semafor o podanym adresie
void semafor_post(sema sem);

// Funkcja opuszczająca semafor o podanym adresie
void semafor_wait(sema sem);

#endif