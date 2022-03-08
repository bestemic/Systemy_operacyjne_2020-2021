# **Systemy operacyjne** <br/> **Zestaw 2**
<br>
<div style="text-align: right"><b>Przemysław Pawlik</b></div>

## **a)**
Napisać program wypisujący identyfikatory UID, GID, PID, PPID i PGID dla danego procesu.

----------
<br>

## **b)**
Wywołać funkcję fork trzy razy (najlepiej w pętli for) i wypisać powyższe identyfikatory dla procesu macierzystego oraz wszystkich procesów potomnych.
Przy pomocy funkcji wait sprawić, aby proces macierzysty zaczekał na zakończenie wszystkich procesów potomnych.

----------
<br>

## **c)**
Jak w (b), tylko przy użyciu funkcji sleep (nie używać funkcji wait) sprawiać by procesy potomne były adoptowane przez proces init lub systemd;
poleceniem pstree -p z poziomu powłoki wyswietlić drzewo procesów w danym systemie i zidentyfikować proces adoptujący osierocone procesy.

----------
<br>

## **d)**
Jak w (b), tylko wstawić funkcję sleep w takich miejscach programu, aby procesy pojawiały się na ekranie grupowane pokoleniami od najstarszego do najmłodszego, a proces macierzysty kończył się dopiero po procesach potomnych (nie używać funkcji wait).

Na podstawie wyników programu sporządzić (w pliku tekstowym) "drzewo genealogiczne" tworzonych procesów z zaznaczonymi identyfikatorami PID, PPID i PGID.

----------
<br>

## **e)**
Jak w (b), tylko przy użyciu fukcji `setpgid` sprawić by każdy proces potomny stawał się liderem swojej własnej grupy procesów.

Ile procesów powstanie przy n-krotnym wywołaniu funkcji fork i dlaczego?

W celu narysowania drzewa genealogicznego procesów, najpierw skopiować do pliku tekstowego wydruk na ekranie z przykładowego uruchomienia programu, a następnie w kolejnych liniach wypisać wartości(PID,PPID,PGID) procesów z kolejnych pokoleń i połączyć je kreskami, np.

```text
PID: 1030 PPID: 1029 PGID: 1029
    PID: 1031 PPID: 1030 PGID: 1029
        PID: 1032 PPID: 1031 PGID: 1029                    
            PID: 1033 PPID: 1032 PGID: 1029
    PID: 1035 PPID: 1030 PGID: 1029
        1036 PPID: 1035 PGID: 1029
```

----------
<br>

