#include<stdio.h>
#include<stdlib.h>
#include "ant.h"

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
void save_board(int**board,int m,int n,Ant*ant, int k, char* f){
    FILE* out;
    char filename[100];
    sprintf(filename, "out/%s_%d.txt",f, k);
    out = fopen(filename, "w");
    fprintf(out,LINE_DOWN_RIGHT); //drukujemy znak rogu dolnego prawego
    for(int j=0;j<n;j++){ //dla każdej kolumny
        fprintf(out,LINE_HORIZONTAL); //drukujemy znak poziomej linii
    }
    fprintf(out,LINE_DOWN_LEFT); //drukujemy znak rogu dolnego lewego
    fprintf(out,"\n"); //drukujemy znak nowej linii
    for(int i=0;i<m;i++){ //dla każdego wiersza
        fprintf(out,LINE_VERTICAL); //drukujemy znak pionowej linii
        for(int j=0;j<n;j++){ //dla każdej kolumny
            if(i==ant->y&&j==ant->x){ //jeśli komórka zawiera mrówkę
                switch(board[i][j]){ //sprawdzamy kolor komórki
                    case WHITE: //jeśli jest biała
                        switch(ant->dir){ //sprawdzamy kierunek mrówki
                            case NORTH: //jeśli jest skierowana na górę
                                fprintf(out,ARROW_NORTH_WHITE); //drukujemy znak białej strzałki skierowanej na górę
                                break; //kończymy przypadek
                            case EAST: //analogicznie dla innych kierunków
                                fprintf(out,ARROW_EAST_WHITE);
                                break;
                            case SOUTH:
                                fprintf(out,ARROW_SOUTH_WHITE);
                                break;
                            case WEST:
                                fprintf(out,ARROW_WEST_WHITE);
                                break;
                        }
                        break; //kończymy przypadek
                    case BLACK: //jeśli jest czarna
                        switch(ant->dir){ //sprawdzamy kierunek mrówki
                            case NORTH: //jeśli jest skierowana na górę
                                fprintf(out,ARROW_NORTH_BLACK); //drukujemy znak czarnej strzałki skierowanej na górę
                                break; //kończymy przypadek
                            case EAST: //analogicznie dla innych kierunków
                                fprintf(out,ARROW_EAST_BLACK);
                                break;
                            case SOUTH:
                                fprintf(out,ARROW_SOUTH_BLACK);
                                break;
                            case WEST:
                                fprintf(out,ARROW_WEST_BLACK);
                                break;
                        }
                        break; //kończymy przypadek
                }
            }
            else{ //jeśli komórka nie zawiera mrówki
                switch(board[i][j]){ //sprawdzamy kolor komórki
                    case WHITE: //jeśli jest biała
                        fprintf(out,SQUARE_WHITE); //drukujemy znak białego kwadratu
                        break; //kończymy przypadek
                    case BLACK: //jeśli jest czarna
                        fprintf(out,SQUARE_BLACK); //drukujemy znak czarnego kwadratu
                        break; //kończymy przypadek
                }
            }
        }
        fprintf(out,LINE_VERTICAL); //drukujemy znak pionowej linii
        fprintf(out,"\n"); //drukujemy znak nowej linii
    }
    fprintf(out,LINE_UP_RIGHT); //drukujemy znak rogu górnego prawego
    for(int j=0;j<n;j++){ //dla każdej kolumny
        fprintf(out,LINE_HORIZONTAL); //drukujemy znak poziomej linii
    }
    fprintf(out,LINE_UP_LEFT); //drukujemy znak rogu górnego lewego
    fprintf(out,"\n"); //drukujemy znak nowej linii
    fclose(out);
}

