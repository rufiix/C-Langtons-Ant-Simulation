**Program mrówka** 

Program symuluje zachowanie automatu komórkowego zwanego mrówką Langtona. Program zapisuje 1000 ostatnich iteracji symulacji do plików tekstowych w folderze “out”.

**Uruchomienie programu** 

Program należy uruchomić z linii poleceń, podając następujące argumenty:

./bin/mrowka -n [n] -m [m] -i [i] -d [dir] -p [%]

n - liczba wierszy planszy 
m - liczba kolumn planszy 
i - liczba iteracji symulacji 
dir - kierunek początkowy mrówki (0 - góra, 1 - prawo, 2 - dół, 3 - lewo) 
% - procent zamalowanych na czarno pól planszy na początku symulacji

**Przykład** 

./bin/mrowka -n 10 -m 20 -i 2000 -d 0 -p 25

To polecenie uruchomi symulację mrówki Langtona na planszy o wymiarach 10x20, wykonując 2000 iteracji. Na początku symulacji 25% pól planszy będzie czarnych, a mrówka będzie skierowana w górę. Program zapisze ostatnie 1000 iteracji do plików “1001.txt” do “2000.txt” w folderze “out”.

