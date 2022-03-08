# **Systemy operacyjne** <br/> **Zestaw 7**
<br>
<div style="text-align: right"><b>Przemysław Pawlik</b></div>

## **Treść**
Przy pomocy pamięci dzielonej oraz semaforów standardu `POSIX` zaimplementować problem "producenta—konsumenta" z ćwiczenia 4 przedstawiony poniższym pseudokodem.

Zamiast potoku użyć N-elementowego bufora cyklicznego (tzn. po dojściu do końca bufora wracamy na jego początek) umieszczonego w pamięci dzielonej, gdzie elementem bufora jest pewna ustalona porcja bajtów.

Dostęp do wspólnego bufora synchronizować przy pomocy semaforów nazwanych standardu `POSIX`.

Programy producenta i konsumenta uruchamiać przez `exec` w procesach potomnych utworzonych przez `fork` w procesie macierzystym — proces ten powinien wcześniej utworzyć i zainicjować semafory i pamięć dzieloną, a po utworzeniu procesów potomnych zaczekać na ich zakończenie i zrobić odpowiednie porządki.

Podobnie jak w ćwiczeniu 6, usuwanie obiektu pamięci dzielonej oraz semaforów umieścić w funkcji rejestrowanej przez `atexit` oraz funkcji obsługi sygnału `SIGINT`.

Bufor jednostek towaru można zdefiniować jako tablicę dwuwymiarową i umieścić go wewnątrz struktury wraz z iteratorami dla producenta i konsumenta, np.

```c
#define NELE 20 // Rozmiar elementu bufora (jednostki towaru) w bajtach
#define NBUF 5 // liczba elementow bufora

// Segment pamieci dzielonej
typedef struct {
    char bufor[NBUF][NELE]; // Wspolny bufor danych
    int wstaw, wyjmij; // Pozycje wstawiania i wyjmowania z bufora
} SegmentPD;
```

Odwzorowując obszar pamięci dzielonej w wirtualną przestrzeń adresową procesu należy wykonać odpowiednie rzutowanie typu, np.

```c
SegmentPD *wpd = (SegmentPD *) mmap(NULL, sizeof(SegmentPD), PROT_READ, MAP_SHARED, des, 0);
```

Następnie, przy użyciu tak zdefiniowanego wskaźnika można wykonywać operacje na tym segmencie, np.

```c
wpd->wyjmij = (wpd->wyjmij + 1) % NBUF;
```

Podobnie jak dla semaforów, stworzyć własną bibliotekę funkcji do obsługi pamięci dzielonej.

- Z własnych bibliotek funkcji do obsługi semaforów i pamięci dzielonej stworzyć bibliotekę statyczną oraz bibliotekę dzieloną (ang. sharedlibrary);  
umieścić je w podkatalogu `./lib` (patrz przykład w StartSO).
- Podać w pseudokodzie uogólnienie rozwiązania tego problemu na przypadek wielu producentów i wielu konsumentów (kolejność przesyłanych porcji danych może być dowolna - dane potraktować tu jak np. wodę).

Przykład pseudokodu dla ćwiczenia 7:

```c
// Pseudokod dla problemu Producenta i Konsumenta z buforem cyklicznym.
// Wspolny bufor do przesylania danych znajduje sie w pamieci dzielonej.
// Dostep do bufora jest synchronizowany semaforami.

#define N ? // Rozmiar bufora

typdef struct { ... } Towar; // Definicja typu dla jednostek towaru
Towar bufor[N]; // Bufor mogacy pomiescic N jednostek towaru
int wstaw = 0, wyjmij = 0; // Pozycje wstawiania oraz wyjmowania towaru
    // z bufora (mozna umieścic w pamieci dzielonej)

semaphore PROD = N; // Semafor do wstrzymywania Producenta
semaphore KONS = 0; // Semafor do wstrzymywania Konsumenta

// Proces Producent
// ----------------
Towar towarProd;
while (1) {
    // Produkcja towaru
    P(PROD); // Opusc semafor Producenta
    bufor[wstaw] = towarProd; // Umiesc towar w buforze
    wstaw = (wstaw + 1) % N; // Przesun pozycje wstawiania o 1 dalej
    V(KONS); // Podniesc semafor Konsumenta
}

// Proces Konsument
// ----------------
Towar towarKons;
while (1) {
    P(KONS); // Opusc semafor Konsumenta
    towarKons = bufor[wyjmij]; // Umiesc towar w buforze
    wyjmij = (wyjmij + 1) % N; // Przesun pozycje wstawiania o 1 dalej
    V(PROD); // Podniesc semafor Producenta
    // Konsumpcja towaru
}
```

----------
<br>

