# **Systemy operacyjne** <br/> **Zestaw 6**
<br>
<div style="text-align: right"><b>Przemysław Pawlik</b></div>

## **Treść**
Przy pomocy semaforów nazwanych standardu `POSIX` zaimplementować zadanie wzajemnego wykluczania dla procesów podane w pseudokodzie na końcu podrozdziału 5.1.

Czas operacji na wspólnym zasobie symulować używając np. funkcji `sleep`.

Dla demonstracji poprawności działania programu użyć odpowiednich komunikatów wypisywanych przez poszczególne procesy przed, w trakcie i po sekcji krytycznej oraz funkcji podającej wartość semafora.

Pamiętać o zainicjowaniu semafora odpowiednią wartością zaraz po jego utworzeniu.

- Stworzyć własną bibliotekę prostych w użyciu funkcji do tworzenia, otwierania, uzyskiwania wartości, operowania, zamykania i usuwania semafora — korzystających z odpowiednich funkcji systemowych/bibliotecznych i zawierających obsługę błędów.
- Napisać specjalny program do powielania procesów realizujących wzajemne wykluczanie - w oparciu o funkcje fork i exec (nazwę programu do inicjowania procesów, liczbę procesów oraz liczbę sekcji krytycznych/prywatnych każdego procesu przekazywać przez argumenty programu `powielacza`).
  
  *Program ten powinien na początku utworzyć i zainicjować semafor, a na końcu - kiedy wszystkie jego procesy potomne zakończą swoje działanie — usunąć go.*
- Semafor usuwać w funkcji rejestrowanej przez funkcję `atexit` (zwrócić uwagę, kiedy należy wywołać funkcję `exit`, a kiedy `_exit`).  
Dodać również możliwość usuwania semafora w funkcji obsługi sygnału `SIGINT`, na wypadek gdyby program trzeba było zakończyć sekwencją klawiszy `Ctrl-C`.
- W celu weryfikacji poprawności wzajemnego wykluczania procesów niech program `powielacz` na samym początku stworzy plik tekstowy `numer.txt` i wpisze w nim numer o wartości 0 (zero), a program implementujący wzajemne wykluczanie w swojej sekcji krytycznej odczytuje wartość zapisanego w tym pliku numeru, następnie zwiększa go o `1` i po losowej (np. funkcja `rand`) chwili czasu zapisuje z powrotem do pliku.
Po zakończeniu działania wszystkich procesów realizujących wzajemne wykluczanie proces `powielacz` powinien sprawdzić poprawność końcowego numeru zapisanego w pliku i wypisać odpowiedni komunikat.

*Sprawdzić, jaka będzie końcowa wartość numeru bez użycia sekcji krytycznej.*

----------
<br>
