#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <wchar.h>
#include <locale.h>

// znaki do rysowania mapy
#define LINE_VERTICAL L'│'
#define LINE_HORIZONTAL L'─'
#define LINE_DOWN_RIGHT L'┌'
#define LINE_DOWN_LEFT L'┐'
#define LINE_UP_RIGHT L'└'
#define LINE_UP_LEFT L'┘'
#define SQUARE_WHITE L' '
#define SQUARE_BLACK L'█'
#define ARROW_NORTH_WHITE L'△'
#define ARROW_NORTH_BLACK L'▲'
#define ARROW_EAST_WHITE L'▷'
#define ARROW_EAST_BLACK L'▶'
#define ARROW_SOUTH_WHITE L'▽'
#define ARROW_SOUTH_BLACK L'▼'
#define ARROW_WEST_WHITE L'◁'
#define ARROW_WEST_BLACK L'◀'

// kierunki mrówki
#define NORTH 0
#define EAST 1
#define SOUTH 2
#define WEST 3

// struktura przechowująca stan mrówki
typedef struct {
    int x; // położenie w poziomie
    int y; // położenie w pionie
    int dir; // kierunek
    wchar_t arrow; // znak strzałki
} ant_t;

// funkcja tworząca nową mrówkę
ant_t *new_ant(int x, int y, int dir) {
    ant_t *ant = malloc(sizeof(ant_t));
    if (ant == NULL) {
        fprintf(stderr, "Błąd alokacji pamięci dla mrówki\n");
        exit(1);
    }
    ant->x = x;
    ant->y = y;
    ant->dir = dir;
    switch (dir) {
        case NORTH:
            ant->arrow = ARROW_NORTH_WHITE;
            break;
        case EAST:
            ant->arrow = ARROW_EAST_WHITE;
            break;
        case SOUTH:
            ant->arrow = ARROW_SOUTH_WHITE;
            break;
        case WEST:
            ant->arrow = ARROW_WEST_WHITE;
            break;
        default:
            fprintf(stderr, "Nieprawidłowy kierunek mrówki\n");
            exit(1);
    }
    return ant;
}

// funkcja zwalniająca pamięć mrówki
void free_ant(ant_t *ant) {
    free(ant);
}

// funkcja tworząca nową planszę o podanych wymiarach
wchar_t **new_board(int m, int n) {
    wchar_t **board = malloc(m * sizeof(wchar_t *));
    if (board == NULL) {
        fprintf(stderr, "Błąd alokacji pamięci dla planszy\n");
        exit(1);
    }
    for (int i = 0; i < m; i++) {
        board[i] = malloc(n * sizeof(wchar_t));
        if (board[i] == NULL) {
            fprintf(stderr, "Błąd alokacji pamięci dla planszy\n");
            exit(1);
        }
        for (int j = 0; j < n; j++) {
            board[i][j] = SQUARE_WHITE; // domyślnie wszystkie pola są białe
        }
    }
    return board;
}

// funkcja zwalniająca pamięć planszy
void free_board(wchar_t **board, int m) {
    for (int i = 0; i < m; i++) {
        free(board[i]);
    }
    free(board);
}

// funkcja wczytująca planszę z pliku
wchar_t **load_board(char *filename, int *m, int *n, ant_t **ant) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        fprintf(stderr, "Błąd otwarcia pliku %s\n", filename);
        exit(1);
    }
    // wczytanie wymiarów planszy
    if (fscanf(file, "%d %d\n", m, n) != 2) {
        fprintf(stderr, "Błąd wczytania wymiarów planszy z pliku %s\n", filename);
        exit(1);
    }
    // utworzenie planszy
    wchar_t **board = new_board(*m, *n);
    // wczytanie stanu planszy
    for (int i = 0; i < *m; i++) {
        for (int j = 0; j < *n; j++) {
            wchar_t c = fgetwc(file);
            if (c == WEOF) {
                fprintf(stderr, "Błąd wczytania znaku z pliku %s\n", filename);
                exit(1);
            }
            // sprawdzenie, czy znak jest poprawnym polem planszy
            if (c != SQUARE_WHITE && c != SQUARE_BLACK) {
                fprintf(stderr, "Nieprawidłowy znak %lc w pliku %s\n", c, filename);
                exit(1);
            }
            board[i][j] = c;
        }
        // pominięcie znaku nowej linii
        fgetwc(file);
    }
    // wczytanie położenia i kierunku mrówki
    int x, y, dir;
    if (fscanf(file, "%d %d %d\n", &x, &y, &dir) != 3) {
        fprintf(stderr, "Błąd wczytania stanu mrówki z pliku %s\n", filename);
        exit(1);
    }
    // sprawdzenie, czy położenie mrówki jest w granicach planszy
    if (x < 0 || x >= *n || y < 0 || y >= *m) {
        fprintf(stderr, "Nieprawidłowe położenie mrówki w pliku %s\n", filename);
        exit(1);
    }
    // utworzenie mrówki
    *ant = new_ant(x, y, dir);
    // zamknięcie pliku
    fclose(file);
    return board;
}

// funkcja generująca planszę z losowymi polami czarnymi
wchar_t **generate_board(int m, int n, int fill, ant_t **ant) {
    // utworzenie planszy
    wchar_t **board = new_board(m, n);
    // ustawienie ziarna generatora liczb losowych
    srand(time(NULL));
    // obliczenie liczby pól czarnych
    int black = m * n * fill / 100;
    // losowanie pól czarnych
    while (black > 0) {
        int i = rand() % m;
        int j = rand() % n;
        if (board[i][j] == SQUARE_WHITE) {
            board[i][j] = SQUARE_BLACK;
            black--;
        }
    }
    // losowanie położenia i kierunku mrówki
    int x = rand() % n;
    int y = rand() % m;
    int dir = rand() % 4;
    // utworzenie mrówki
    *ant = new_ant(x, y, dir);
    return board;
}

// funkcja zapisująca planszę do pliku
void save_board(wchar_t **board, int m, int n, ant_t *ant, char *filename) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        fprintf(stderr, "Błąd otwarcia pliku %s\n", filename);
        exit(1);
    }
    // zapisanie wymiarów planszy
    fprintf(file, "%d %d\n", m, n);
    // zapisanie stanu planszy
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            fputwc(board[i][j], file);
        }
        // zapisanie znaku nowej linii
        fputwc(L'\n', file);
    }
    // zapisanie położenia i kierunku mrówki
    fprintf(file, "%d %d %d\n", ant->x, ant->y, ant->dir);
    // zamknięcie pliku
    fclose(file);
}

// funkcja wypisująca planszę na standardowe wyjście
// funkcja wypisująca planszę na standardowe wyjście
void print_board(wchar_t **board, int m, int n, ant_t *ant) {
    // wypisanie górnej ramki
    fputwc(LINE_DOWN_RIGHT, stdout);
    for (int j = 0; j < n; j++) {
        fputwc(LINE_HORIZONTAL, stdout);
    }
    fputwc(LINE_DOWN_LEFT, stdout);
    fputwc(L'\n', stdout);
    // wypisanie stanu planszy
    for (int i = 0; i < m; i++) {
        fputwc(LINE_VERTICAL, stdout);
        for (int j = 0; j < n; j++) {
            // wypisanie pola planszy lub strzałki mrówki
            if (i == ant->y && j == ant->x) {
                fputwc(ant->arrow, stdout);
            } else {
                fputwc(board[i][j], stdout);
            }
        }
        fputwc(LINE_VERTICAL, stdout);
        fputwc(L'\n', stdout);
    }
    // wypisanie dolnej ramki
    fputwc(LINE_UP_RIGHT, stdout);
    for (int j = 0; j < n; j++) {
        fputwc(LINE_HORIZONTAL, stdout);
    }
    fputwc(LINE_UP_LEFT, stdout);
    fputwc(L'\n', stdout);
}

// funkcja wykonująca jeden krok mrówki
void step(wchar_t **board, int m, int n, ant_t *ant) {
    // sprawdzenie koloru pola, na którym stoi mrówka
    if (board[ant->y][ant->x] == SQUARE_WHITE) {
        // jeśli pole jest białe, zmiana koloru na czarny
        board[ant->y][ant->x] = SQUARE_BLACK;
        // obrót mrówki o 90 stopni w prawo
        ant->dir = (ant->dir + 1) % 4;
        // zmiana znaku strzałki na czarny
        switch (ant->dir) {
            case NORTH:
                ant->arrow = ARROW_NORTH_BLACK;
                break;
            case EAST:
                ant->arrow = ARROW_EAST_BLACK;
                break;
            case SOUTH:
                ant->arrow = ARROW_SOUTH_BLACK;
                break;
            case WEST:
                ant->arrow = ARROW_WEST_BLACK;
                break;
        }
    } else {
        // jeśli pole jest czarne, zmiana koloru na biały
        board[ant->y][ant->x] = SQUARE_WHITE;
        // obrót mrówki o 90 stopni w lewo
        ant->dir = (ant->dir + 3) % 4;
        // zmiana znaku strzałki na biały
        switch (ant->dir) {
            case NORTH:
                ant->arrow = ARROW_NORTH_WHITE;
                break;
            case EAST:
                ant->arrow = ARROW_EAST_WHITE;
                break;
            case SOUTH:
                ant->arrow = ARROW_SOUTH_WHITE;
                break;
            case WEST:
                ant->arrow = ARROW_WEST_WHITE;
                break;
        }
    }
    // przesunięcie mrówki o jedną komórkę do przodu
    switch (ant->dir) {
        case NORTH:
            ant->y = (ant->y + m - 1) % m;
            break;
        case EAST:
            ant->x = (ant->x + 1) % n;
            break;
        case SOUTH:
            ant->y = (ant->y + 1) % m;
            break;
        case WEST:
            ant->x = (ant->x + n - 1) % n;
            break;
    }
}

// funkcja symulująca mrówkę Langtona
void simulate(wchar_t **board, int m, int n, int i, char *name, ant_t *ant) {
    // utworzenie bufora dla nazwy pliku wynikowego
    char filename[100];
    // wykonanie i iteracji
    for (int k = 0; k < i; k++) {
        // wykonanie jednego kroku mrówki
        step(board, m, n, ant);
        // sprawdzenie, czy podano nazwę pliku
        if (name != NULL) {
            // utworzenie nazwy pliku wynikowego
            sprintf(filename, "%s_%d", name, k + 1);
            // zapisanie planszy do pliku
            save_board(board, m, n, ant, filename);
        } else {
            // wypisanie planszy na standardowe wyjście
            print_board(board, m, n, ant);
        }
    }
}

// funkcja wyświetlająca pomoc
void print_help() {
    printf("Sposób użycia: langton [opcje] m n i name\n");
    printf("Opcje:\n");
    printf("-h\twyświetla tę pomoc\n");
    printf("-l plik\twczytuje planszę z pliku\n");
    printf("-g fill\tgeneruje planszę z losowymi polami czarnymi\n");
    printf("Argumenty:\n");
    printf("m\tliczba wierszy planszy\n");
    printf("n\tliczba kolumn planszy\n");
    printf("i\tliczba iteracji\n");
    printf("name\tprzedrostek plików wynikowych\n");
}

// główna funkcja programu
int main(int argc, char **argv) {
    // ustawienie kodowania znaków na UTF-8
    setlocale(LC_ALL, "C.UTF-8");
    // deklaracja zmiennych
    int m, n, i, fill;
    char *name, *file;
    wchar_t **board;
    ant_t *ant;
    // inicjalizacja zmiennych
    m = n = i = fill = 0;
    name = file = NULL;
    board = NULL;
    ant = NULL;
    // przetwarzanie opcji wywołania
    int opt;
    while ((opt = getopt(argc, argv, "hl:g:")) != -1) {
        switch (opt) {
            case 'h':
                // wyświetlenie pomocy i zakończenie programu
                print_help();
                return 0;
            case 'l':
                // wczytanie nazwy pliku z planszą
                file = optarg;
                break;
            case 'g':
                // wczytanie procentowego zapełnienia planszy
                fill = atoi(optarg);
                break;
            default:
                // wyświetlenie pomocy i zakończenie programu z błędem
                print_help();
                return 1;
        }
    }
    // sprawdzenie, czy podano nazwę pliku z planszą
    if (file != NULL) {
        // wczytanie planszy z pliku
        board = load_board(file, &m, &n, &ant);
    } else {
        // sprawdzenie, czy podano wymiary planszy
        if (optind + 3 >= argc) {
            // wyświetlenie pomocy i zakończenie programu z błędem
            print_help();
            return 1;
        }
        // wczytanie wymiarów planszy
        m = atoi(argv[optind]);
        n = atoi(argv[optind + 1]);
        // sprawdzenie, czy wymiary są dodatnie
        if (m <= 0 || n <= 0) {
            // wyświetlenie błędu i zakończenie programu z błędem
            fprintf(stderr, "Wymiary planszy muszą być dodatnie\n");
            return 1;
        }
        // sprawdzenie, czy podano procentowe zapełnienie planszy
        if (fill > 0) {
            // generowanie planszy z losowymi polami czarnymi
            board = generate_board(m, n, fill, &ant);
        } else {
            // tworzenie pustej planszy
            board = new_board(m, n);
            // tworzenie mrówki na środku planszy
            ant = new_ant(n / 2, m / 2, NORTH);
        }
    }
    // wczytanie liczby iteracji
    i = atoi(argv[optind + 2]);
    // sprawdzenie, czy liczba iteracji jest nieujemna
    if (i < 0) {
        // wyświetlenie błędu i zakończenie programu z błędem
        fprintf(stderr, "Liczba iteracji musi być nieujemna\n");
        return 1;
    }
    // wczytanie nazwy pliku wynikowego
	name = argv[optind + 3];
	// symulacja mrówki Langtona
	simulate(board, m, n, i, name, ant);
	// zwolnienie pamięci planszy i mrówki
	free_board(board, m);
	free_ant(ant);
	// zakończenie programu z sukcesem
	return 0;
	}