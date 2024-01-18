#include<stdio.h>
#include<stdlib.h>
#include<time.h> //dodajemy bibliotekę do generowania liczb losowych
#include "ant.h"
#include "board.h"
#include <unistd.h>


//funkcja główna programu
int main(int argc, char** argv){
    int c, errflag = 0; int m = 0, n = 0, i = 0, dir = 0, p = 0; char* f = "";
    while((c = getopt(argc, argv, ":n:m:i:d:p:f:")) != -1){
        switch(c){
            case 'n':
                m = atoi(optarg);
                break;
            case 'm':
                n = atoi(optarg);
                break;
            case 'i':
                i = atoi(optarg);
                break;
            case 'd':
                dir = atoi(optarg);
                break;
            case 'p':
                p = atoi(optarg);
                break;
            case 'f':
                f = optarg;
                break;
            case ':':
            case '?':
                errflag++;
                break;
        }
    }
    if(errflag > 0){
        printf("Błąd");
        return 1;
    }/*
    int m = atoi(argv[1]); // Liczba wierszy planszy
    int n = atoi(argv[2]); // Liczba kolumn planszy
    int i = atoi(argv[3]); // Liczba iteracji
    int dir = atoi(argv[4]); // Początkowy kierunek mrówki (0 - góra, 1 - prawo, 2 - dół, 3 - lewo)
    int p = atoi(argv[5]); // Procent zapełnienia planszy czarnymi polami */
    int**board=create_board(m,n); //tworzymy planszę o podanym rozmiarze
    srand(time(NULL)); //inicjujemy generator liczb losowych
    for(int k=0;k<m;k++){ //przechodzimy po wszystkich wierszach planszy
        for(int j=0;j<n;j++){ //przechodzimy po wszystkich kolumnach planszy
            int r=rand()%100; //losujemy liczbę z zakresu 0-99
            if(r<p){ //jeśli jest mniejsza od procentowego zapełnienia
                board[k][j]=BLACK; //ustawiamy komórkę na czarno
            }
        }
    }
    Ant*ant=create_ant(n/2,m/2,dir); //tworzymy mrówkę na środku planszy o podanym kierunku
    for(int k=0;k<i;k++){ //powtarzamy i razy
        if(i-k <= 1000)save_board(board,m,n,ant, k + 1, f); //rysujemy planszę na ekranie
        step(board,m,n,ant); //wykonujemy jeden krok symulacji mrówki
    }
    destroy_board(board,m); //zwalniamy pamięć zajmowaną przez planszę
    destroy_ant(ant); //zwalniamy pamięć zajmowaną przez mrówkę
    return 0; //kończymy program
}

