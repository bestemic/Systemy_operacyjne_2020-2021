# **Systemy operacyjne** <br/> **Zestaw 9**
<br>
<div style="text-align: right"><b>Przemysław Pawlik</b></div>

## **Treść**
Przy pomocy muteksów zaimplementować zadanie wzajemnego wykluczania dla wątków.

Do demonstracji działania programu można użyć sekwencji sterujących konsoli (patrz np. plik `hello.c` w katalogu StartSO).

Niech na przykład wątek wykonując swoją sekcję prywatną wypisuje odpowiedni komunikat po lewej stronie okna konsoli, natomiast będąc w sekcji krytycznej drukuje informacje po prawej stronie (w tym samym wierszu).

Każdy wątek może kilka razy powtarzać powyższy cykl.

Przy poprawnie zrealizowanym zadaniu wzajemnego wykluczania, po prawej stronie okna konsoli w danym momencie powinien zgłaszać się co najwyżej jeden wątek, pozostałe natomiast powinny zgłaszać się po lewej stronie.

Do zademonstrowania operacji na zasobie dzielonym użyć np. wspólnej (globalnej) zmiennej licznikowej, zainicjowanej wartością 0.

Niech każdy z wątków na początku sekcji krytycznej przypisuje jej wartość swojemu prywatnemu licznikowi, następnie zwiększa wartość tego prywatnego licznika o 1, a po pewnym czasie (użyć np. funkcji `sleep`) przypisuje jego wartość wspólnemu licznikowi.

Sprawdzić, czy po zakończeniu działania wszystkich wątków wartość tego wspólnego licznika jest taka jaka powinna być.

----------
<br>
