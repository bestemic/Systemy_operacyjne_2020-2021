# **Systemy operacyjne** <br/> **Zestaw 4**
<br>
<div style="text-align: right"><b>Przemysław Pawlik</b></div>

## **Treść**
Przy pomocy potoków nienazwanych systemu UNIX zaimplementować problem "Producenta i konsumenta".

Dla zademonstrowania, że nie doszło do utraty ani zwielokrotnienia towaru, niech Producent pobiera "surowiec" (np. porcje bajtów) z pliku tekstowego i wstawia go jako towar do potoku, a Konsument niech umieszcza pobrany z potoku towar w innym pliku tekstowym (porcje danych Producenta i Konsumenta nie muszą być równe).

Po zakończeniu działania programów (wyczerpaniu zasobów "surowca") oba pliki tekstowe powinny być identyczne (można to sprawdzić poleceniem `diff -s`, które najlepiej umieścić w pliku Makefile po poleceniu uruchomienia programu).

Oba procesy niech drukują odpowiednie komunikaty na ekranie, w tym towar, który przesyłają. Do zasymulowania różnych szybkości działania programów użyć funkcji `sleep`, np. z losowym czasem usypiania. Do czytania/pisania danych z/do pliku tekstowego, jak również wypisywania ich na ekran użyć funkcji `read` i `write`.

- Dane do potoku przesyłać/pobierać małymi porcjami (po kilka bajtów, nie wszystko naraz!) i wypisywać na ekranie dane przesyłane za każdym razem producenta i konsumenta; w ogólności porcje danych producenta i konsumenta mogą być różne, dlatego powinny zostać zdefiniowane oddzielnie.
- Nazwy plików danych i wyników przekazywać przez argumenty wywołania programu.
- Do czytania/pisania danych z/do pliku użyć funkcji `read()` i `write()`.
- Do wypisywania danych na ekranie również użyć funkcji `write()` z odpowiednim deskryptorem.
- Do symulowania różnych szybkości działania procesów użyć funkcji `sleep()` z losowym czasem usypiania generowanym np. przez funkcję `rand()` (patrz: `man 3 rand`).

*UWAGA*: Fukcją `write()` wpisywać liczbę faktycznie wczytanych przez `read()` bajtów (zwracaną prze nią).*

Kompilacja/linkowanie z flagami: `-Wall -std=c99 -pedantic`

----------
<br>


