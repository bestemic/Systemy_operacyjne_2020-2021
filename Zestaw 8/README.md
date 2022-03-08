# **Systemy operacyjne** <br/> **Zestaw 8**
<br>
<div style="text-align: right"><b>Przemysław Pawlik</b></div>

## **Treść**
Proces klienta wysyła do procesu serwera żądanie wykonania działania arytmetycznego na dwóch liczbach postaci: liczba o liczba, gdzie operator o należy do `{+,-,*,/}`, np. `2 + 3`.
Serwer wykonuje odpowiednie działanie i odsyła wynik do klienta.

Klient odbiera ten wynik i wypisuje go na ekranie.

Posługując się mechanizmem kolejek komunikatów standardu `POSIX` zaimplementować powyższe zadanie typu klient-serwer z możliwością obsługi przez serwerawielu klientów naraz.

Niech serwer utworzy kolejkę komunikatów w trybie do odbierania o nazwie zdefiniowanej we wspólnym pliku nagłówkowym włączanym w plikach źródłowych programów serwera i klienta.

Do tej kolejki klient będzie wysyłał swoje komunikaty, a serwer będzie je z niej odbierał.

Klient z kolei niech utworzy kolejkę komunikatów w trybie do odbierania o nazwie `/PID`, gdzie PID jest jego identyfikatorem procesu PID, np. `/17895` (do utworzenia tej nazwy użyć np. funkcji `sprintf`).

Następnie niech klient otworzy kolejkę serwera w trybie do nadawania komunikatów i w pętli wczytuje z klawiatury żądane działanie (np. używając funkcji `fgets`), tworzy komunikat umieszczając na początku swój PID, a po nim wczytane wyrażenie (np. przy pomocy funkcji `sprintf`), po czym wysyła taki komunikat do kolejki serwera.

Pętlę można zakończyć znakiem końca pliku `EOF` (z klawiatury wysyła się go sekwencją klawiszy `Ctrl+D`), po czym klient powinien zamknąć i usunąć własną kolejkę oraz zamknąć kolejkę serwera - czynności te umieścić w funkcji rejestrowanej przez `atexit` oraz w obsłudze sygnału `SIGINT`.

Serwer niech działa w pętli nieskończonej (proces `demon`), próbując odbierać komunikaty ze swojej kolejki.

Po otrzymaniu komunikatu od klienta, serwer powinien odczytać z niego PID klienta (np. funkcją `atoi`) i otworzyć kolejkę klienta w trybie do nadawania komunikatów o nazwie postaci `/PID` (użyć np. funkcji `sprintf`).

Następnie z komunikatu powinien odczytać odpowiednie działanie (można użyć np. funkcji `sscanf`), wykonać je i odesłać wynik w komunikacie (użyć np. funkcji `sprintf`) do kolejki klienta, po czym zamknąć tę kolejkę.

Proces serwera można zakończyć np. sygnałem `SIGINT` (z klawiatury sekwencją klawiszy `Ctrl+C`), z tym że serwer powinien przechwycić ten sygnał i wykonać jego obsługę w postaci zamknięcia i usunięcia własnej kolejki komunikatów - czynności te umieścić w funkcji rejestrowanej przez `atexit`.

Niech procesy serwera i klienta wypisują na ekranie odpowiednie komunikaty, w szczególności atrybuty kolejek komunikatów zaraz po ich utworzeniu.

Uruchamiać każdy proces z innego terminala, np. użyć polecenia:

```
xterm -hold -title SERWER -bg red -e ./serwer.x &
xterm -hold -title KLIENT1 -bg green -e ./klient.x &
xterm -hold -title KLIENT2 -bg green -e ./klient.x &
...
```

w pliku `Makefile` do uruchomienia serwera i kilku klientów (więcej szczegółów można znaleźć w man `xterm`).

Podobnie jak dla semaforów i pamięci dzielonej, stworzyć własną bibliotekę funkcji do obsługi kolejek komunikatów.

----------
<br>
