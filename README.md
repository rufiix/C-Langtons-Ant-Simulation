Mrówka Langtona

Program wypisuje 1000 ostatnich iteracji algorytmu mrówki langtona do folderu "out". Wywołuje się ten algorytm przez terminal wspisując odpowiedną formułkę.

Wywołanie:
  ./bin/mrowka [n] [m] [i] [dir] [%]

  n - liczba wierszy
  m - liczba kolumn
  i - liczba iteracji
  dir - kierunek początkowy mrówki (0 - góra, 1 - prawo, 2 - dół, 3 - lewo)
  % - procent zamalowanych na czarno pól planszy(przy starcie programu)
  
Przykład:
  ./bin/mrowka 10 20 2000 0 25
  To wywołanie stworzy 1000 plików nazwanych od "1001.txt" do "2000.txt" w każdym plikuj "n.txt" będzie znajdowało się odpowiednio n wywołanie alogrytmu mrówki langtona, na planszy o 10 wierszach i 20 kolumnach. 
  Pierwsza iteracja będzie zaczynała na planszy wypełnionej czarnymi polami w 25%. Mrówka na początku będzie obrócona w górę. 
