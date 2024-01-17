#ifndef _ANT_H
#define _ANT_H

#define LINE_VERTICAL "│" //definiujemy znak pionowej linii
#define LINE_HORIZONTAL "─" //definiujemy znak poziomej linii
#define LINE_DOWN_RIGHT "┌" //definiujemy znak rogu dolnego prawego
#define LINE_DOWN_LEFT "┐" //definiujemy znak rogu dolnego lewego
#define LINE_UP_RIGHT "└" //definiujemy znak rogu górnego prawego
#define LINE_UP_LEFT "┘" //definiujemy znak rogu górnego lewego
#define SQUARE_WHITE " " //definiujemy znak białego kwadratu
#define SQUARE_BLACK "█" //definiujemy znak czarnego kwadratu
#define ARROW_NORTH_WHITE "△" //definiujemy znak białej strzałki skierowanej na górę
#define ARROW_NORTH_BLACK "▲" //definiujemy znak czarnej strzałki skierowanej na górę
#define ARROW_EAST_WHITE "▷" //definiujemy znak białej strzałki skierowanej na prawo
#define ARROW_EAST_BLACK "▶" //definiujemy znak czarnej strzałki skierowanej na prawo
#define ARROW_SOUTH_WHITE "▽" //definiujemy znak białej strzałki skierowanej na dół
#define ARROW_SOUTH_BLACK "▼" //definiujemy znak czarnej strzałki skierowanej na dół
#define ARROW_WEST_WHITE "◁" //definiujemy znak białej strzałki skierowanej na lewo
#define ARROW_WEST_BLACK "◀" //definiujemy znak czarnej strzałki skierowanej na lewo
#define WHITE 0 //definiujemy stałą oznaczającą biały kolor
#define BLACK 1 //definiujemy stałą oznaczającą czarny kolor
#define NORTH 0 //definiujemy stałą oznaczającą kierunek północny
#define EAST 1 //definiujemy stałą oznaczającą kierunek wschodni
#define SOUTH 2 //definiujemy stałą oznaczającą kierunek południowy
#define WEST 3 //definiujemy stałą oznaczającą kierunek zachodni

typedef struct{int x;int y;int dir;}Ant; //definiujemy typ struktury reprezentującej mrówkę

Ant*create_ant(int x,int y,int dir);
void destroy_ant(Ant*ant);
void step(int**board,int m,int n,Ant*ant);

#endif

