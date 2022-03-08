# **Systemy operacyjne** <br/> **Zestaw 3**
<br>
<div style="text-align: right"><b>Przemysław Pawlik</b></div>

## **a)**
Napisać program do obsługi sygnałów z możliwościami:

- (1) wykonania operacji domyślnej
- (2) ignorowania oraz
- (3) przechwycenia i własnej obsługi sygnału.

Do oczekiwania na sygnał użyć funkcji `pause`.

Uruchomić program i wysyłać do niego sygnały przy pomocy sekwencji klawiszy oraz przy pomocy polecenia `kill` z poziomu powłoki.

----------
<br>

## **b)**
Uruchomić powyższy program poprzez funkcję `exec` w procesie potomnym innego procesu i wysyłać do niego sygnały poprzez funkcję systemową kill z procesu macierzystego.

*Uwaga: Przed wysłaniem sygnału sprawdzić, czy proces istnieje.*

----------
<br>

## **c)**
W procesie macierzystym utworzyć proces potomny i sprawić, aby stał się liderem nowej grupy procesów (funkcja `setpgid`), a następnie uruchomić w nim kilka procesów potomnych wykonujących program do obsługi sygnałów.

Z pierwszego procesu macierzystego wysyłać sygnały do całej grupy procesów potomnych po uprzednim sprawdzeniu jej istnienia (jak wyżej).

Identyfikator tej grupy procesów uzyskać przy pomocy funkcji `getpgid`.

Proces będący liderem grupy procesów niech ignoruje sygnały, a na końcu czeka na zakończenie wszystkich swoich procesów potomnych i wypisuje ich status zakończenia zwracany przez funkcję `wait`.

Numer sygnału oraz opcję obsługi we wszystkich powyższych programach przekazywać za pomocą argumentów wywołania programu - sprawdzać ich liczbę i wypisywać odpowiedni komunikat w przypadku błędnego uruchomienia.

----------
<br>

