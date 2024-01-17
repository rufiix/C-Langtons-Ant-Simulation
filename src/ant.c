#include<stdio.h>
#include<stdlib.h>
#include "ant.h"

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
