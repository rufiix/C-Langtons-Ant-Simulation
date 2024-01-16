# Mrówka Langtona

## Opis
Ten program oblicza i wizualizuje kolejne etapy mrówki Langtona, prostego automatu komórkowego, który porusza się po dwuwymiarowej siatce zgodnie z następującymi zasadami:

- Mrówka znajduje się w komórce białej, wykonuje: obrót o 90 stopni w prawo, zmienia kolor komórki na przeciwny,  przesuwa się o jedną komórkę do przodu
- Mrówka znajduje się w komórce czarnej, wykonuje: obrót o 90 stopni w lewo, zmienia kolor komórki na przeciwny,  przesuwa się o jedną komórkę do przodu

Program jest napisany w języku C i używa znaków Unicode do rysowania mapy.

## Sposób użycia
Aby uruchomić program, należy skompilować plik `ant.c` za pomocą kompilatora C, np. `gcc ant.c -o ant`, a następnie uruchomić plik wykonywalny `ant`, np. `./ant`.

Program poprosi użytkownika o podanie następujących parametrów wejściowych:

- Liczbę wierszy planszy m
- Liczbę kolumn planszy n
- Liczbę iteracji i
- Początkowy kierunek mrówki (0 - góra, 1 - prawo, 2 - dół, 3 - lewo)

Po wprowadzeniu parametrów, program wyświetli planszę na stdout, umieszczając mrówkę na środku planszy i wykonując podaną liczbę iteracji, rysując planszę po każdym kroku mrówki.

## Wymagania
Program wymaga systemu operacyjnego, który obsługuje znaki Unicode i kompilatora C, który wspiera standard C99 lub nowszy. Program nie używa żadnych zewnętrznych bibliotek ani zasobów.
