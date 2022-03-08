#include "mes_bib.h"

// Funkcja do tworzenia kolejki komiunikatów o podanej nazwie
void mes_create(const char *name)
{
    // Zmienna do przechowania deskryptora kolejki komunikatów
    mqd_t des;

    // Struktura atrybutów
    struct mq_attr attr;

    // Zainicjowanie wartośEci struktury atrybutów
    attr.mq_flags = 0;
    attr.mq_maxmsg = 10;
    attr.mq_msgsize = 30;
    attr.mq_curmsgs = 0;

    // Utworzenie kolejki komunikatów
    des = mq_open(name, O_RDWR | O_CREAT | O_EXCL, 0644, &attr);

    // Obsługa błędu funkcji mq_open
    if (des == (mqd_t)-1)
    {
        perror("mq_open error");
        exit(5);
    }

    // Zamknięcie deskryptora kolejki komunikatów
    mes_close(des);
}

// Funkcja do otwierania kolejki komunikatów o podanej nazwie, opcji dosępu i zwracająca jej deskryptor
mqd_t mes_open(const char *name, int flag)
{
    // Zmienna do przechowania deskryptora kolejki komunikatów
    mqd_t des;

    // Otworzenie kolejki komunikatów
    des = mq_open(name, flag);

    // Obsługa błędu funkcji mq_open
    if (des == (mqd_t)-1)
    {
        perror("mq_open error");
        exit(5);
    }

    // Zwrócenie deskryptora kolejki komunikatów
    return des;
}

// Funkcja do zamykania kolejki komunikatów o podanym deskryptorze
void mes_close(mqd_t des)
{
    // Zamykanie kolejki komunikatów i obsługa błedu funkcji mq_close
    if (mq_close(des) == -1)
    {
        perror("mq_close error");
        exit(5);
    }
}

// Funkcja do usuwania kolejki komunikatów o podanej nazwie
void mes_delate(const char *name)
{
    // Usuwanie kolejki komunikatów i obłsuga błędu funkcji mq_unlink
    if (mq_unlink(name) == -1)
    {
        perror("mq_unlink error");
        exit(5);
    }
}

// Funkcja do umieszczania wiadomości w kolejce komunikatów
void mes_put(mqd_t des, char *buffor, int rozmiar)
{
    // Umieszczenie wiadomości w kolejce komunikatów i obsługa błędu funkcji mq_send
    if (mq_send(des, buffor, rozmiar, 0) == -1)

    {
        perror("mq_send error");
        exit(5);
    }
}

// Funkcja do odbierania wiadomości z kolejki komunikatów
void mes_get(mqd_t des, char *buffor, int rozmiar)
{
    // Odebranie wiadomości z kolejki komunikatów i obsługa błędu funkcji mq_receive
    if (mq_receive(des, buffor, rozmiar, NULL) == -1)
    {
        perror("mq_receive error");
        exit(5);
    }
}

// Funkcja wypisująca wartości atrybutów kolejki o podanym deskryptorze
void mes_getattr(mqd_t des)
{
    // Tymczasowa struktura atrybutów
    struct mq_attr attr;

    // Pobranie struktury atrybutów i ogsługa błędu funkcji mq_getattr
    if (mq_getattr(des, &attr) == -1)
    {
        perror("error");
        exit(5);
    }

    // Wypisanie informacji
    printf("Flaga: %ld\n", attr.mq_flags);
    printf("Maksmalna ilosc komunikatow: %ld\n", attr.mq_maxmsg);
    printf("Maksmalna wielkosc komunikatu: %ld\n", attr.mq_msgsize);
    printf("Obecna ilosc komunikatow: %ld\n", attr.mq_curmsgs);
}

