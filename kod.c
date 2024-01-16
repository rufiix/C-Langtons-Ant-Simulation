#include<stdio.h>
#include<stdlib.h>
#include<time.h> //dodajemy bibliotekę do generowania liczb losowych
#define LINE_VERTICAL"│" //definiujemy znak pionowej linii
#define LINE_HORIZONTAL"─" //definiujemy znak poziomej linii
#define LINE_DOWN_RIGHT"┌" //definiujemy znak rogu dolnego prawego
#define LINE_DOWN_LEFT"┐" //definiujemy znak rogu dolnego lewego
#define LINE_UP_RIGHT"└" //definiujemy znak rogu górnego prawego
#define LINE_UP_LEFT"┘" //definiujemy znak rogu górnego lewego
#define SQUARE_WHITE" " //definiujemy znak białego kwadratu
#define SQUARE_BLACK"█" //definiujemy znak czarnego kwadratu
#define ARROW_NORTH_WHITE"△" //definiujemy znak białej strzałki skierowanej na górę
#define ARROW_NORTH_BLACK"▲" //definiujemy znak czarnej strzałki skierowanej na górę
#define ARROW_EAST_WHITE"▷" //definiujemy znak białej strzałki skierowanej na prawo
#define ARROW_EAST_BLACK"▶" //definiujemy znak czarnej strzałki skierowanej na prawo
#define ARROW_SOUTH_WHITE"▽" //definiujemy znak białej strzałki skierowanej na dół
#define ARROW_SOUTH_BLACK"▼" //definiujemy znak czarnej strzałki skierowanej na dół
#define ARROW_WEST_WHITE"◁" //definiujemy znak białej strzałki skierowanej na lewo
#define ARROW_WEST_BLACK"◀" //definiujemy znak czarnej strzałki skierowanej na lewo
#define WHITE 0 //definiujemy stałą oznaczającą biały kolor
#define BLACK 1 //definiujemy stałą oznaczającą czarny kolor
#define NORTH 0 //definiujemy stałą oznaczającą kierunek północny
#define EAST 1 //definiujemy stałą oznaczającą kierunek wschodni
#define SOUTH 2 //definiujemy stałą oznaczającą kierunek południowy
#define WEST 3 //definiujemy stałą oznaczającą kierunek zachodni
typedef struct{int x;int y;int dir;}Ant; //definiujemy typ struktury reprezentującej mrówkę
Ant*create_ant(int x,int y,int dir){ //definiujemy funkcję, która tworzy mrówkę o podanych współrzędnych i kierunku
    Ant*ant=(Ant*)malloc(sizeof(Ant)); //alokujemy pamięć na mrówkę
    ant->x=x; //ustawiamy współrzędną x mrówki
    ant->y=y; //ustawiamy współrzędną y mrówki
    ant->dir=dir; //ustawiamy kierunek mrówki
    return ant; //zwracamy wskaźnik na mrówkę
}
void destroy_ant(Ant*ant){ //definiujemy funkcję, która zwalnia pamięć zajmowaną przez mrówkę
    free(ant); //zwalniamy pamięć
}
int**create_board(int m,int n){ //definiujemy funkcję, która tworzy planszę o podanym rozmiarze
    int**board=(int**)malloc(m*sizeof(int*)); //alokujemy pamięć na wiersze planszy
    for(int i=0;i<m;i++){ //dla każdego wiersza
        board[i]=(int*)malloc(n*sizeof(int)); //alokujemy pamięć na kolumny planszy
        for(int j=0;j<n;j++){ //dla każdej kolumny
            board[i][j]=WHITE; //ustawiamy komórkę na biało
        }
    }
    return board; //zwracamy wskaźnik na planszę
}
void destroy_board(int**board,int m){ //definiujemy funkcję, która zwalnia pamięć zajmowaną przez planszę
    for(int i=0;i<m;i++){ //dla każdego wiersza
        free(board[i]); //zwalniamy pamięć na kolumny
    }
    free(board); //zwalniamy pamięć na wiersze
}

//funkcja, która rysuje planszę na ekranie
void draw_board(int**board,int m,int n,Ant*ant){
    printf(LINE_DOWN_RIGHT); //drukujemy znak rogu dolnego prawego
    for(int j=0;j<n;j++){ //dla każdej kolumny
        printf(LINE_HORIZONTAL); //drukujemy znak poziomej linii
    }
    printf(LINE_DOWN_LEFT); //drukujemy znak rogu dolnego lewego
    printf("\n"); //drukujemy znak nowej linii
    for(int i=0;i<m;i++){ //dla każdego wiersza
        printf(LINE_VERTICAL); //drukujemy znak pionowej linii
        for(int j=0;j<n;j++){ //dla każdej kolumny
            if(i==ant->y&&j==ant->x){ //jeśli komórka zawiera mrówkę
                switch(board[i][j]){ //sprawdzamy kolor komórki
                    case WHITE: //jeśli jest biała
                        switch(ant->dir){ //sprawdzamy kierunek mrówki
                            case NORTH: //jeśli jest skierowana na górę
                                printf(ARROW_NORTH_WHITE); //drukujemy znak białej strzałki skierowanej na górę
                                break; //kończymy przypadek
                            case EAST: //analogicznie dla innych kierunków
                                printf(ARROW_EAST_WHITE);
                                break;
                            case SOUTH:
                                printf(ARROW_SOUTH_WHITE);
                                break;
                            case WEST:
                                printf(ARROW_WEST_WHITE);
                                break;
                        }
                        break; //kończymy przypadek
                    case BLACK: //jeśli jest czarna
                        switch(ant->dir){ //sprawdzamy kierunek mrówki
                            case NORTH: //jeśli jest skierowana na górę
                                printf(ARROW_NORTH_BLACK); //drukujemy znak czarnej strzałki skierowanej na górę
                                break; //kończymy przypadek
                            case EAST: //analogicznie dla innych kierunków
                                printf(ARROW_EAST_BLACK);
                                break;
                            case SOUTH:
                                printf(ARROW_SOUTH_BLACK);
                                break;
                            case WEST:
                                printf(ARROW_WEST_BLACK);
                                break;
                        }
                        break; //kończymy przypadek
                }
            }
            else{ //jeśli komórka nie zawiera mrówki
                switch(board[i][j]){ //sprawdzamy kolor komórki
                    case WHITE: //jeśli jest biała
                        printf(SQUARE_WHITE); //drukujemy znak białego kwadratu
                        break; //kończymy przypadek
                    case BLACK: //jeśli jest czarna
                        printf(SQUARE_BLACK); //drukujemy znak czarnego kwadratu
                        break; //kończymy przypadek
                }
            }
        }
        printf(LINE_VERTICAL); //drukujemy znak pionowej linii
        printf("\n"); //drukujemy znak nowej linii
    }
    printf(LINE_UP_RIGHT); //drukujemy znak rogu górnego prawego
    for(int j=0;j<n;j++){ //dla każdej kolumny
        printf(LINE_HORIZONTAL); //drukujemy znak poziomej linii
    }
    printf(LINE_UP_LEFT); //drukujemy znak rogu górnego lewego
    printf("\n"); //drukujemy znak nowej linii
}

//funkcja, która wykonuje jeden krok symulacji mrówki
void step(int**board,int m,int n,Ant*ant){
    board[ant->y][ant->x]=1-board[ant->y][ant->x]; //zmieniamy kolor komórki, na której jest mrówka
    switch(board[ant->y][ant->x]){ //sprawdzamy kolor komórki
        case WHITE: //jeśli jest biała
            ant->dir=(ant->dir+1)%4; //obracamy mrówkę w prawo
            break; //kończymy przypadek
        case BLACK: //jeśli jest czarna
            ant->dir=(ant->dir+3)%4; //obracamy mrówkę w lewo
            break; //kończymy przypadek
    }
    switch(ant->dir){ //sprawdzamy kierunek mrówki
        case NORTH: //jeśli jest skierowana na górę
            ant->y=(ant->y-1+m)%m; //przesuwamy mrówkę o jedną komórkę do góry (z uwzględnieniem granic planszy)
            break; //kończymy przypadek
        case EAST: //analogicznie dla innych kierunków
            ant->x=(ant->x+1)%n; //przesuwamy mrówkę o jedną komórkę w prawo
            break;
        case SOUTH:
            ant->y=(ant->y+1)%m; //przesuwamy mrówkę o jedną komórkę w dół
            break;
        case WEST:
            ant->x=(ant->x-1+n)%n; //przesuwamy mrówkę o jedną komórkę w lewo
            break;
    }
}

//funkcja główna programu
int main(){
    int m,n,i,dir,p; //deklarujemy zmienne do przechowywania parametrów
    printf("Podaj liczbę wierszy planszy m: "); //pytamy użytkownika o liczbę wierszy planszy
    scanf("%d",&m); //wczytujemy liczbę z klawiatury i zapisujemy ją w zmiennej m
    printf("Podaj liczbę kolumn planszy n: "); //pytamy użytkownika o liczbę kolumn planszy
    scanf("%d",&n); //wczytujemy liczbę z klawiatury i zapisujemy ją w zmiennej n
    printf("Podaj liczbę iteracji i: "); //pytamy użytkownika o liczbę iteracji symulacji
    scanf("%d",&i); //wczytujemy liczbę z klawiatury i zapisujemy ją w zmiennej i
    printf("Podaj początkowy kierunek mrówki (0 - góra, 1 - prawo, 2 - dół, 3 - lewo): "); //pytamy użytkownika o początkowy kierunek mrówki
    scanf("%d",&dir); //wczytujemy liczbę z klawiatury i zapisujemy ją w zmiennej dir
    printf("Podaj procentowe zapełnienie planszy czarnymi polami (0 - 100): "); //pytamy użytkownika o procentowe zapełnienie planszy czarnymi polami
    scanf("%d",&p); //wczytujemy liczbę z klawiatury i zapisujemy ją w zmiennej p
    int**board=create_board(m,n); //tworzymy planszę o podanym rozmiarze
    srand(time(NULL)); //inicjujemy generator liczb losowych
    for(int i=0;i<m;i++){ //przechodzimy po wszystkich wierszach planszy
        for(int j=0;j<n;j++){ //przechodzimy po wszystkich kolumnach planszy
            int r=rand()%100; //losujemy liczbę z zakresu 0-99
            if(r<p){ //jeśli jest mniejsza od procentowego zapełnienia
                board[i][j]=BLACK; //ustawiamy komórkę na czarno
            }
        }
    }
    Ant*ant=create_ant(n/2,m/2,dir); //tworzymy mrówkę na środku planszy o podanym kierunku
    for(int k=0;k<i;k++){ //powtarzamy i razy
        draw_board(board,m,n,ant); //rysujemy planszę na ekranie
        step(board,m,n,ant); //wykonujemy jeden krok symulacji mrówki
    }
    destroy_board(board,m); //zwalniamy pamięć zajmowaną przez planszę
    destroy_ant(ant); //zwalniamy pamięć zajmowaną przez mrówkę
    return 0; //kończymy program
}

