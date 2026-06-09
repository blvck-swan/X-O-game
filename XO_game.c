
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

#define SIZE 3

char board[SIZE][SIZE];

#define RESET   "\x1b[0m"
#define RED     "\x1b[31m"
#define BLUE    "\x1b[34m"
#define GREEN   "\x1b[32m"
#define YELLOW  "\x1b[33m"

void initializeBoard() {
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)
            board[i][j] = ' ';
}

void printBoard() {
    printf("\n");
    for (int i = 0; i < SIZE; i++) {
        printf(" ");
        for (int j = 0; j < SIZE; j++) {
            if (board[i][j] == 'X')
                printf(RED " %c " RESET, board[i][j]);
            else if (board[i][j] == 'O')
                printf(BLUE " %c " RESET, board[i][j]);
            else
                printf("   ");
            if (j < SIZE - 1) printf(GREEN "|" RESET);
        }
        printf("\n");
        if (i < SIZE - 1)
            printf(GREEN " ---+---+---\n" RESET);
    }
    printf("\n");
}

bool checkWinner(char player) {
    for (int i = 0; i < SIZE; i++) {
        if ((board[i][0] == player && board[i][1] == player && board[i][2] == player) ||
            (board[0][i] == player && board[1][i] == player && board[2][i] == player))
            return true;
    }
    if ((board[0][0] == player && board[1][1] == player && board[2][2] == player) ||
        (board[0][2] == player && board[1][1] == player && board[2][0] == player))
        return true;
    return false;
}

bool isBoardFull() {
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)
            if (board[i][j] == ' ')
                return false;
    return true;
}

bool placeMove(int row, int col, char player) {
    if (row >= 0 && row < SIZE && col >= 0 && col < SIZE && board[row][col] == ' ') {
        board[row][col] = player;
        return true;
    }
    return false;
}

void playerMove() {
    int row, col;
    while (true) {
        printf(YELLOW "Enter your move (row and column: 1 1 for top-left): " RESET);
        if (scanf("%d %d", &row, &col) != 2) {
            while (getchar() != '\n');
            printf("Invalid input! Please enter two numbers.\n");
            continue;
        }
        row--; col--; 
        if (placeMove(row, col, 'X')) break;
        else printf("Invalid move! Cell already occupied or out of range.\n");
    }
}


void computerMove() {
    int row, col;
    srand(time(NULL));
    if (isBoardFull()) return;
    do {
        row = rand() % SIZE;
        col = rand() % SIZE;
    } while (!placeMove(row, col, 'O'));
    printf("Computer placed an O at %d %d\n", row + 1, col + 1);
}

int main() {
    initializeBoard();
    printf(GREEN "Welcome to Advanced Tic-Tac-Toe with Colors!\n" RESET);
    printBoard();

    while (true) {
        playerMove();
        printBoard();
        if (checkWinner('X')) {
            printf(RED "Congratulations! You win!\n" RESET);
            break;
        }
        if (isBoardFull()) {
            printf(YELLOW "It's a draw!\n" RESET);
            break;
        }

        computerMove();
        printBoard();
        if (checkWinner('O')) {
            printf(BLUE "Computer wins! Better luck next time.\n" RESET);
            break;
        }
        if (isBoardFull()) {
            printf(YELLOW "It's a draw!\n" RESET);
            break;
        }
    }

    return 0;
}