# **Systemy operacyjne** <br/> **Zestaw 5**
<br>
<div style="text-align: right"><b>Przemysław Pawlik</b></div>

## **a)**
Utworzyć potok FIFO z poziomu programu, a następnie uruchomić procesy Producenta i Konsumenta w tym samym programie (w procesie macierzystym i potomnym lub w dwóch potomnych).

*Potok usuwać w funkcji zarejestrowanej przez `atexit`.*

----------
<br>

## **b)**
Sprawdzić, że potoki FIFO działają dla niezależnych procesów przez utworzenie potoku FIFO z linii komend oraz uruchomienie procesów Producenta i Konsumenta niezależnie z poziomu powłoki, np. w różnych terminalach — można użyć polecenia:

```
xterm -hold -title nazwa okna -e nazwa_programu & ...
```

dla każdego z tych procesów w pliku Makefile (jak też tworzenie/usuwanie potoku).

----------
<br>
