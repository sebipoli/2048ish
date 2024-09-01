# 2048ish

## Cerința 1

Am creat un meniu care conține opțiunile: `New Game`, `Resume`, și `Quit`.

- **Navigarea prin meniu** se face cu ajutorul tastelor `Săgeată Sus` sau `Săgeată Jos`.
- Dacă este selectată opțiunea `New Game`:
  - Se inițializează o tablă de joc nouă.
  - Noua tablă de joc conține **2 numere aleatorii** din mulțimea `{2, 4}` pe poziții random.
  - Dacă se apasă tasta `q`, se afișează un mesaj și se iese din joc.
- Dacă este selectată opțiunea `Resume`:
  - Jocul începe de la ultima tablă de joc folosind fișierul `resume.txt`.
  - Se afișează ultimul punctaj obținut.
  - Jocul continuă în mod obișnuit.
  - Se afișează **data și ora curentă**, tabla, și punctajul actual.
  - Dacă se apasă tasta `q`, se afișează un mesaj și se iese din joc.
- Dacă este selectată opțiunea `Quit`, se iese din joc.

## Cerința 2

- Tablă de joc este o matrice 4x4 de numere întregi.
- Noua tablă de joc conține **2 numere aleatorii** din mulțimea `{2, 4}` pe poziții random.
- Punctajul inițial este 0 și se actualizează în timpul jocului.
- Se afișează o legendă a comenzilor valide.
- Se afișează **data și ora curentă**, tabla, și punctajul actual.

## Cerința 3

- **Dacă se apasă `Săgeată Sus`**:
  - Se verifică dacă există spațiu liber deasupra unui număr.
  - Dacă există spațiu liber (numărul de deasupra este `0`), se face o interschimbare.
  - Acest proces se repetă de 3 ori pentru a urca toate elementele până sus.
  - Apoi, se verifică dacă mai există spațiu liber pe tablă (există un `0`).
  - Dacă există cel puțin un `0`, se generează un număr aleatoriu din mulțimea `{2, 4}` pe o poziție disponibilă.
  - Dacă numărul de deasupra este egal cu numărul curent, numărul de deasupra se dublează, iar cel de jos devine `0`.
  - Numărul obținut prin dublare este adăugat la variabila de punctaj, care este inițializată cu 0 la început.
  - Punctajul se afișează după fiecare comandă.
  - În fișierul `punctaj.txt` se păstrează istoricul punctajelor.
  - Aceste procese se aplică pentru întreaga matrice după fiecare apăsare de tastă validă.
  - Fiecare număr din mulțimea `{2, 4, ..., 2048}` are culori diferite.
- **Analog pentru celelalte comenzi**.
- Dacă se apasă o tastă invalidă, nu se întâmplă nimic; se așteaptă apăsarea unei taste valide.

## Cerința 5

- Jocul se termină atunci când nu mai sunt alte mutări posibile:
  - Matricea nu conține niciun `0` și niciun element identic unul lângă altul.
  - Sau când pe tablă se află numărul `2048`.
- În momentul în care ai pierdut sau ai câștigat, se afișează un mesaj corespunzător.
