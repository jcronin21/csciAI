#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

#define BOARD_SIZE 8
#define BLACK_DISK 'B'
#define WHITE_DISK 'W'
#define EMPTY ' '

typedef struct {
    char board[BOARD_SIZE][BOARD_SIZE];
} OthelloBoard;

void initializeBoard(OthelloBoard *board) {
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            board->board[i][j] = EMPTY;
        }
    }

    board->board[3][3] = WHITE_DISK;
    board->board[4][4] = WHITE_DISK;
    board->board[3][4] = BLACK_DISK;
    board->board[4][3] = BLACK_DISK;
}

void printBoard(const OthelloBoard *board) {
    printf("  a b c d e f g h\n");
    for (int i = 0; i < BOARD_SIZE; i++) {
        printf("%d ", i + 1);
        for (int j = 0; j < BOARD_SIZE; j++) {
            printf("%c ", board->board[i][j]);
        }
        printf("\n");
    }
}

bool isValidMove(const OthelloBoard *board, int row, int col, char color) {
    if (row < 0 || row >= BOARD_SIZE || col < 0 || col >= BOARD_SIZE || board->board[row][col] != EMPTY) {
        return false;
    }

    char opponent = (color == BLACK_DISK) ? WHITE_DISK : BLACK_DISK;
    bool valid = false;

    int dr[] = {0, 0, 1, -1, 1, -1, 1, -1};
    int dc[] = {1, -1, 0, 0, 1, -1, -1, 1};

    for (int d = 0; d < 8; d++) {
        int r = row + dr[d];
        int c = col + dc[d];
        bool foundOpponent = false;

        while (r >= 0 && r < BOARD_SIZE && c >= 0 && c < BOARD_SIZE && board->board[r][c] == opponent) {
            r += dr[d];
            c += dc[d];
            foundOpponent = true;
        }

        if (foundOpponent && r >= 0 && r < BOARD_SIZE && c >= 0 && c < BOARD_SIZE && board->board[r][c] == color) {
            valid = true;
            break;
        }
    }

    return valid;
}

void applyMove(OthelloBoard *board, int row, int col, char color) {
    board->board[row][col] = color;

    char opponent = (color == BLACK_DISK) ? WHITE_DISK : BLACK_DISK;

    int dr[] = {0, 0, 1, -1, 1, -1, 1, -1};
    int dc[] = {1, -1, 0, 0, 1, -1, -1, 1};

    for (int d = 0; d < 8; d++) {
        int r = row + dr[d];
        int c = col + dc[d];
        bool foundOpponent = false;

        while (r >= 0 && r < BOARD_SIZE && c >= 0 && c < BOARD_SIZE && board->board[r][c] == opponent) {
            r += dr[d];
            c += dc[d];
            foundOpponent = true;
        }

        if (foundOpponent && r >= 0 && r < BOARD_SIZE && c >= 0 && c < BOARD_SIZE && board->board[r][c] == color) {
            r = row + dr[d];
            c = col + dc[d];
            while (r >= 0 && r < BOARD_SIZE && c >= 0 && c < BOARD_SIZE && board->board[r][c] == opponent) {
                board->board[r][c] = color;
                r += dr[d];
                c += dc[d];
            }
        }
    }
}

int countDisks(const OthelloBoard *board, char color) {
    int count = 0;
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (board->board[i][j] == color) {
                count++;
            }
        }
    }
    return count;
}

int main() {
    OthelloBoard board;
    initializeBoard(&board);

    srand(time(NULL));

    char playerColor;
    scanf("I %c", &playerColor);
    getchar();  

  int dr[] = {0, 0, 1, -1, 1, -1, 1, -1};
  int dc[] = {1, -1, 0, 0, 1, -1, -1, 1};


    char opponentColor = (playerColor == BLACK_DISK) ? WHITE_DISK : BLACK_DISK;

    while (1) {
        char action;
        scanf(" %c", &action);
        if (action == opponentColor) {
            char move[4];
            scanf(" %s", move);
            int col = move[0] - 'a';
            int row = move[1] - '1';

            if (isValidMove(&board, row, col, opponentColor)) {
                applyMove(&board, row, col, opponentColor);
            } else {
                //invalid opponent move
               if (action == playerColor) {
                  char move[4];
                  int col, row;

                   while (1) {
                      printf("Enter your move (e.g., 'c3'): ");
                      scanf(" %s", move);
                      col = move[0] - 'a';
                      row = move[1] - '1';

                  if (isValidMove(&board, row, col, playerColor)) {
                  applyMove(&board, row, col, playerColor);
                        break;  //Valid move
                  } else {
                     printf("Invalid move. Try again.\n");
                 }
            }
        }

            }
        }
        bool playerCanMove = false;
        for (int i = 0; i < BOARD_SIZE; i++) {
            for (int j = 0; j < BOARD_SIZE; j++) {
                if (isValidMove(&board, i, j, playerColor)) {
                    playerCanMove = true;
                    break;
                }
            }
            if (playerCanMove) {
                break;
            }
        }

        if (action == 'n') {
            int blackPieces;
            scanf("%d", &blackPieces);
            break;  
        } else if (playerCanMove) {
            int bestRow = -1;
            int bestCol = -1;
            int maxFlips = -1;

            for (int i = 0; i < BOARD_SIZE; i++) {
                for (int j = 0; j < BOARD_SIZE; j++) {
                    if (isValidMove(&board, i, j, playerColor)) {
                        int flips = 0;
                        int dr[] = {0, 0, 1, -1, 1, -1, 1, -1};
                       

                           for (int d = 0; d < 8; d++) {
                            int r = i + dr[d];
                            int c = j + dc[d];
                            bool foundOpponent = false;

                            while (r >= 0 && r < BOARD_SIZE && c >= 0 && c < BOARD_SIZE && board.board[r][c] == opponentColor) {
                                r += dr[d];
                                c += dc[d];
                                foundOpponent = true;
                            }

                            if (foundOpponent && r >= 0 && r < BOARD_SIZE && c >= 0 && c < BOARD_SIZE && board.board[r][c] == playerColor) {
                                flips += (r - i) - 1;
                            }
                        }

                        if (flips > maxFlips) {
                            bestRow = i;
                            bestCol = j;
                            maxFlips = flips;
                        }
                    }
                }
            }

            if (bestRow >= 0 && bestCol >= 0) {
                applyMove(&board, bestRow, bestCol, playerColor);
                printf("%c %c%d\n", playerColor, bestCol + 'a', bestRow + 1);
            } else {
                printf("%c\n", playerColor);
            }
        } else {
            printf("%c\n", playerColor); 
        }

        printBoard(&board);
    }

    return 0;
}

