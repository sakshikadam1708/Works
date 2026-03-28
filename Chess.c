#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define SIZE 8

// Chess board
char board[SIZE][SIZE];

// Initialize chess board
void initBoard() {
    int i, j;

    // Empty board
    for (i = 0; i < SIZE; i++)
        for (j = 0; j < SIZE; j++)
            board[i][j] = '.';

    // Black pieces
    char black[] = "rnbqkbnr";
    for (j = 0; j < SIZE; j++) {
        board[0][j] = black[j];
        board[1][j] = 'p';
    }

    // White pieces
    char white[] = "RNBQKBNR";
    for (j = 0; j < SIZE; j++) {
        board[6][j] = 'P';
        board[7][j] = white[j];
    }
}

// Display board
void displayBoard() {
    int i, j;

    printf("\n");
    for (i = 0; i < SIZE; i++) {
        printf("%d ", 8 - i);
        for (j = 0; j < SIZE; j++) {
            printf("%c ", board[i][j]);
        }
        printf("\n");
    }
    printf("  a b c d e f g h\n");
}

// Parse move like e2 e4
int parseMove(char *from, char *to,
              int *fromRow, int *fromCol,
              int *toRow, int *toCol) {

    if (strlen(from) != 2 || strlen(to) != 2)
        return 0;

    if (!islower(from[0]) || !isdigit(from[1]) ||
        !islower(to[0]) || !isdigit(to[1]))
        return 0;

    *fromCol = from[0] - 'a';
    *toCol   = to[0] - 'a';

    *fromRow = 8 - (from[1] - '0');
    *toRow   = 8 - (to[1] - '0');

    if (*fromRow < 0 || *fromRow >= SIZE ||
        *fromCol < 0 || *fromCol >= SIZE ||
        *toRow < 0 || *toRow >= SIZE ||
        *toCol < 0 || *toCol >= SIZE)
        return 0;

    return 1;
}

// Make move
void makeMove(int fromRow, int fromCol, int toRow, int toCol) {
    board[toRow][toCol] = board[fromRow][fromCol];
    board[fromRow][fromCol] = '.';
}

int main() {
    char input[20];
    char from[3], to[3];
    int fromRow, fromCol, toRow, toCol;

    initBoard();

    while (1) {
        displayBoard();
        printf("\nEnter move (e2 e4) or q to quit: ");
        fgets(input, sizeof(input), stdin);

        if (input[0] == 'q')
            break;

        if (strlen(input) < 5) {
            printf("Invalid input format!\n");
            continue;
        }

        from[0] = input[0];
        from[1] = input[1];
        from[2] = '\0';

        to[0] = input[3];
        to[1] = input[4];
        to[2] = '\0';

        if (parseMove(from, to, &fromRow, &fromCol, &toRow, &toCol)) {
            makeMove(fromRow, fromCol, toRow, toCol);
        } else {
            printf("Invalid move!\n");
        }
    }

    printf("Game ended.\n");
    return 0;
}