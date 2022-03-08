#ifndef MES_BIB_H
#define MES_BIB_H

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <mqueue.h>

#define SERWER "/serwer"

// Funkcja do tworzenia kolejki komiunikatów o podanej nazwie
void mes_create(const char *name);

// Funkcja do otwierania kolejki komunikatów o podanej nazwie, opcji dosępu i zwracająca jej deskryptor
mqd_t mes_open(const char *name, int flag);

// Funkcja do zamykania kolejki komunikatów o podanym deskryptorze
void mes_close(mqd_t des);

// Funkcja do usuwania kolejki komunikatów o podanej nazwie
void mes_delate(const char *name);

// Funkcja do umieszczania wiadomości w kolejce komunikatów
void mes_put(mqd_t des, char *buffor, int rozmiar);

// Funkcja do odbierania wiadomości z kolejki komunikatów
void mes_get(mqd_t des, char *buffor, int rozm);

// Funkcja wypisująca wartości atrybutów kolejki o podanym deskryptorze
void mes_getattr(mqd_t des);

#endif