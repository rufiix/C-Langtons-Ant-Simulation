#include <stdio.h>
#include <stdlib.h>

// Definicja stałych dla znaków do rysowania mapy
#define LINE_VERTICAL "│"
#define LINE_HORIZONTAL "─"
#define LINE_DOWN_RIGHT "┌"
#define LINE_DOWN_LEFT "┐"
#define LINE_UP_RIGHT "└"
#define LINE_UP_LEFT "┘"
#define SQUARE_WHITE " "
#define SQUARE_BLACK "█"
#define ARROW_NORTH_WHITE "△"
#define ARROW_NORTH_BLACK "▲"
#define ARROW_EAST_WHITE "▷"
#define ARROW_EAST_BLACK "▶"
#define ARROW_SOUTH_WHITE "▽"
#define ARROW_SOUTH_BLACK "▼"
#define ARROW_WEST_WHITE "◁"
#define ARROW_WEST_BLACK "◀"

// Definicja stałych dla kolorów komórek
#define WHITE 0
#define BLACK 1

// Definicja stałych dla kierunków mrówki
#define NORTH 0
#define EAST 1
#define SOUTH 2
#define WEST 3

// Definicja struktury dla mrówki
typedef struct {
    int x; // współrzędna x mrówki
    int y; // współrzędna y mrówki
    int dir; // kierunek mrówki
} Ant;

// Funkcja, która tworzy nową mrówkę o podanych parametrach
Ant* create_ant(int x, int y, int dir) {
    Ant* ant = (Ant*)malloc(sizeof(Ant)); // alokacja pamięci dla mrówki
    ant->x = x; // ustawienie współrzędnej x
    ant->y = y; // ustawienie współrzędnej y
    ant->dir = dir; // ustawienie kierunku
    return ant; // zwrócenie wskaźnika na mrówkę
}

// Funkcja, która zwalnia pamięć zajmowaną przez mrówkę
void destroy_ant(Ant* ant) {
    free(ant); // zwolnienie pamięci
}

// Funkcja, która tworzy nową planszę o podanych wymiarach i wypełnia ją białymi komórkami
int** create_board(int m, int n) {
    int** board = (int**)malloc(m * sizeof(int*)); // alokacja pamięci dla wierszy planszy
    for (int i = 0; i < m; i++) {
        board[i] = (int*)malloc(n * sizeof(int)); // alokacja pamięci dla kolumn planszy
        for (int j = 0; j < n; j++) {
            board[i][j] = WHITE; // ustawienie koloru komórki na biały
        }
    }
    return board; // zwrócenie wskaźnika na planszę
}

// Funkcja, która zwalnia pamięć zajmowaną przez planszę
void destroy_board(int** board, int m) {
    for (int i = 0; i < m; i++) {
        free(board[i]); // zwolnienie pamięci dla kolumn planszy
    }
    free(board); // zwolnienie pamięci dla wierszy planszy
}

// Funkcja, która rysuje planszę na stdout, używając znaków zdefiniowanych wcześniej
void draw_board(int** board, int m, int n, Ant* ant) {
    // Rysowanie górnej krawędzi planszy
    printf(LINE_DOWN_RIGHT); // lewy górny róg
    for (int j = 0; j < n; j++) {
        printf(LINE_HORIZONTAL); // pozioma krawędź
    }
    printf(LINE_DOWN_LEFT); // prawy górny róg
    printf("\n"); // nowa linia

    // Rysowanie wierszy planszy
    for (int i = 0; i < m; i++) {
        printf(LINE_VERTICAL); // lewa pionowa krawędź
        for (int j = 0; j < n; j++) {
            if (i == ant->y && j == ant->x) {
                // Rysowanie mrówki w zależności od koloru komórki i kierunku mrówki
                switch (board[i][j]) {
                    case WHITE:
                        switch (ant->dir) {
                            case NORTH: printf(ARROW_NORTH_WHITE); break;
                            case EAST: printf(ARROW_EAST_WHITE); break;
                            case SOUTH: printf(ARROW_SOUTH_WHITE); break;
                            case WEST: printf(ARROW_WEST_WHITE); break;
                        }
                        break;
                    case BLACK:
                        switch (ant->dir) {
                            case NORTH: printf(ARROW_NORTH_BLACK); break;
                            case EAST: printf(ARROW_EAST_BLACK); break;
                            case SOUTH: printf(ARROW_SOUTH_BLACK); break;
                            case WEST: printf(ARROW_WEST_BLACK); break;
                        }
                        break;
                }
            } else {
                // Rysowanie komórki w zależności od koloru
                switch (board[i][j]) {
                    case WHITE: printf(SQUARE_WHITE); break;
                    case BLACK: printf(SQUARE_BLACK); break;
                }
            }
        }
        printf(LINE_VERTICAL); // prawa pionowa krawędź
        printf("\n"); // nowa linia
    }

    // Rysowanie dolnej krawędzi planszy
    printf(LINE_UP_RIGHT); // lewy dolny róg
    for (int j = 0; j < n; j++) {
        printf(LINE_HORIZONTAL); // pozioma krawędź
    }
    printf(LINE_UP_LEFT); // prawy dolny róg
    printf("\n"); // nowa linia
}

// Funkcja, która wykonuje jeden krok mrówki, zmieniając kolor komórki i kierunek i położenie mrówki
void step(int** board, int m, int n, Ant* ant) {
    // Zmiana koloru komórki na przeciwny
    board[ant->y][ant->x] = 1 - board[ant->y][ant->x];

    // Zmiana kierunku mrówki w zależności od koloru komórki
    switch (board[ant->y][ant->x]) {
        case WHITE: ant->dir = (ant->dir + 1) % 4; break; // obrót o 90 stopni w prawo
        case BLACK: ant->dir = (ant->dir + 3) % 4; break; // obrót o 90 stopni w lewo
    }

    // Zmiana położenia mrówki w zależności od kierunku mrówki
    switch (ant->dir) {
        case NORTH: ant->y = (ant->y - 1 + m) % m; break; // ruch o jedną komórkę do góry
        case EAST: ant->x = (ant->x + 1) % n; break; // ruch o jedną komórkę w prawo
        case SOUTH: ant->y = (ant->y + 1) % m; break; // ruch o jedną komórkę w dół
        case WEST: ant->x = (ant->x - 1 + n) % n; break; // ruch o jedną komórkę w lewo
    }
}

// Główna funkcja programu
// Główna funkcja programu
int main() {
    // Deklaracja zmiennych dla parametrów wejściowych
    int m, n, i, dir;

    // Wczytanie parametrów wejściowych od użytkownika
    printf("Podaj liczbę wierszy planszy m: ");
    scanf("%d", &m);
    printf("Podaj liczbę kolumn planszy n: ");
    scanf("%d", &n);
    printf("Podaj liczbę iteracji i: ");
    scanf("%d", &i);
    printf("Podaj początkowy kierunek mrówki (0 - góra, 1 - prawo, 2 - dół, 3 - lewo): ");
    scanf("%d", &dir);

    // Tworzenie planszy o podanych wymiarach
    int** board = create_board(m, n);

    // Tworzenie mrówki o podanym kierunku i umieszczenie jej na środku planszy
    Ant* ant = create_ant(n / 2, m / 2, dir);

    // Wykonanie podanej liczby iteracji
    for (int k = 0; k < i; k++) {
        // Rysowanie planszy na stdout
        draw_board(board, m, n, ant);

        // Wykonanie jednego kroku mrówki
        step(board, m, n, ant);
    }

    // Zwalnianie pamięci zajmowanej przez planszę i mrówkę
    destroy_board(board, m);
    destroy_ant(ant);

    // Zwrócenie wartości 0, oznaczającej poprawne zakończenie programu
    return 0;
}
