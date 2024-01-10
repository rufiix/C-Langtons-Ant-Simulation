# Mrówka Langtona

Program symulujący mrówkę Langtona, prosty automat komórkowy, który chodzi po dwuwymiarowej siatce i zmienia kolor pól oraz swój kierunek według prostych zasad.

## Sposób użycia

Program można uruchomić z linii poleceń, podając następujące opcje i argumenty:

`langton [opcje] m n i name`

Opcje:

- `-h` wyświetla pomoc
- `-l plik` wczytuje planszę z pliku
- `-g fill` generuje planszę z losowymi polami czarnymi

Argumenty:

- `m` liczba wierszy planszy
- `n` liczba kolumn planszy
- `i` liczba iteracji
- `name` przedrostek plików wynikowych

Przykłady:

- `langton 10 10 100 langton` symuluje mrówkę Langtona na pustej planszy 10x10 przez 100 iteracji i zapisuje wyniki do plików `langton_1`, `langton_2`, ..., `langton_100`
- `langton -l board.txt 50 output` wczytuje planszę z pliku `board.txt` i symuluje mrówkę Langtona przez 50 iteracji i zapisuje wyniki do plików `output_1`, `output_2`, ..., `output_50`
- `langton -g 20 20 20 200 random` generuje planszę 20x20 z 20% polami czarnymi i symuluje mrówkę Langtona przez 200 iteracji i zapisuje wyniki do plików `random_1`, `random_2`, ..., `random_200`

## Wymagania

Program wymaga następujących bibliotek i narzędzi:

- kompilator języka C, np. gcc
- biblioteka standardowa języka C, np. stdlib.h, stdio.h, unistd.h
- biblioteka do obsługi znaków Unicode, np. wchar.h, locale.h
  
# Wnioski

Program mrówka Langtona jest prostym, ale interesującym przykładem automatu komórkowego, który pokazuje, jak proste zasady mogą prowadzić do złożonych zachowań. Program pozwala na symulację mrówki Langtona na różnych planszach, wczytywanych z pliku lub generowanych losowo, i zapisywanie lub wypisywanie wyników na bieżąco. Program jest napisany w języku C, z użyciem znaków Unicode do rysowania mapy, i korzysta z funkcji getopt do przetwarzania argumentów wywołania.

Program ma jednak pewne ograniczenia i możliwości rozwoju. Po pierwsze, program nie sprawdza poprawności znaków w pliku z planszą, co może prowadzić do błędów lub nieoczekiwanych wyników. Po drugie, program nie obsługuje innych wariantów mrówki Langtona, takich jak mrówka turmitowa, która ma więcej kolorów i kierunków. Po trzecie, program nie ma graficznego interfejsu użytkownika, co mogłoby ułatwić obsługę i wizualizację symulacji. Po czwarte, program nie ma funkcji do analizy i porównania wyników symulacji, takich jak liczba kroków, średnia odległość, entropia, itp.

Program mrówka Langtona jest więc ciekawym i edukacyjnym projektem, który pokazuje, jak z prostych zasad mogą powstawać złożone wzorce. Program może być używany do nauki i zabawy, ale także do dalszego rozwoju i badania własności i zachowań mrówki Langtona i innych automatów komórkowych.

# Autor

Tworzenie programu mrówka Langtona było dla mnie ciekawym i wyzwającym doświadczeniem. Nauczyłem się wielu nowych rzeczy o automatach komórkowych, języku C, znakach Unicode i funkcji getopt. Cieszyłem się, że mogłem wykorzystać moją kreatywność i umiejętności do stworzenia czegoś użytecznego i edukacyjnego. Byłem też zaskoczony i pod wrażeniem, jak z prostych zasad mogą powstawać złożone i piękne wzorce. Podziwiam pracę i pomysłowość naukowców i programistów, którzy zajmują się badaniem i rozwojem mrówki Langtona i innych automatów komórkowych.


