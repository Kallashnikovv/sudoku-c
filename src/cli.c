#include "sudoku.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ctype.h>

/* ANSI escape codes for colors */
#define RESET   "\033[0m"
// Bright white for grid
#define GRID    "\033[1;37m"
// Bright blue for fixed numbers
#define FIXED   "\033[1;34m"
// Bright green for user input
#define USER    "\033[1;32m"
// Bright red for errors
#define ERROR   "\033[1;31m"
// Magenta for borders
#define BORDER  "\033[1;35m"

void printBoard(GameState* game) {
    int size = game->size;
    int subgrid = game->subgrid_size;
    
    // Column headers - 3 characters per column
    printf(BORDER "\n   ");
    for (int j = 0; j < size; j++) {
        printf("%2d ", j + 1);  // 2-digit number + space
    }
    printf(RESET "\n");

    // Build horizontal line template
    char hline[256];
    snprintf(hline, sizeof(hline), GRID "  +");
    for (int sg = 0; sg < size/subgrid; sg++) {
        // 3 dashes per column in subgrid (-1 to account for '+')
        for (int c = 0; c < subgrid * 3 - 1; c++) {
            strcat(hline, "-");
        }
        strcat(hline, "+");
    }
    strcat(hline, RESET "\n");

    for (int i = 0; i < size; i++) {
        // Print horizontal line between subgrid rows
        if (i % subgrid == 0) {
            printf("%s", hline);
        }

        // Row number with border
        printf(BORDER "%2d" GRID "|" RESET, i + 1);

        for (int j = 0; j < size; j++) {
            // Cell content (2 characters wide)
            if (game->puzzle[i][j] == 0) {
                printf("  ");
            } else {
                if (game->editable[i][j]) {
                    printf(USER "%2d" RESET, game->puzzle[i][j]);
                } else {
                    printf(FIXED "%2d" RESET, game->puzzle[i][j]);
                }
            }

            // Vertical separators (matches header spacing)
            if ((j + 1) % subgrid == 0) {
                printf(GRID "|" RESET);
            } else {
                printf(" ");
            }
        }
        printf("\n");
    }
    printf("%s", hline); // Bottom border
}

void displayMenu() {
    printf("\nSudoku Menu:\n");
    printf("1. New Game\n");
    printf("2. Change Size\n");
    printf("3. Change Difficulty\n");
    printf("4. Save Game\n");
    printf("5. Load Game\n");
    printf("6. Instructions\n");
    printf("7. Exit\n");
    printf("Enter choice: ");
}

void handleGame(GameState* game) {
    while (true) {
        printBoard(game);
        printf("\nEnter command (row col value) or 0 to menu: ");
        
        int row, col, value;
        if (scanf("%d", &row) != 1) {
            while (getchar() != '\n');
            printf(ERROR "Invalid input!" RESET "\n");
            continue;
        }
        
        if (row == 0) break;
        if (scanf("%d %d", &col, &value) != 2) {
            while (getchar() != '\n');
            printf(ERROR "Invalid input!" RESET "\n");
            continue;
        }
        
        row--; col--;
        if (row < 0 || row >= game->size || col < 0 || col >= game->size) {
            printf(ERROR "Invalid position!" RESET "\n");
            continue;
        }
        
        if (!game->editable[row][col]) {
            printf(ERROR "Cell is not editable!" RESET "\n");
            continue;
        }
        
        if (value < 1 || value > game->size) {
            printf(ERROR "Invalid value! (1-%d)" RESET "\n", game->size);
            continue;
        }
        
        if (is_valid_move(game->puzzle, game->size, row, col, value)) {
            game->puzzle[row][col] = value;
            if (check_win_condition(game)) {
                printBoard(game);
                printf(USER "\nCongratulations! You won!\n" RESET);
                return;
            }
        } else {
            printf(ERROR "Invalid move!" RESET "\n");
        }
    }
}

int main() {
    srand(time(NULL));
    GameState* game = NULL;
    int size = 9;
    int difficulty = 2;

    while (true) {
        displayMenu();
        int choice;
        scanf("%d", &choice);
        
        switch (choice) {
            // New Game
            case 1: {
                if (game) {
                    freeGameState(game);
                }
                game = createGameState(size, difficulty);
                handleGame(game);
                break;
            }
            // Change Size
            case 2: {
                printf("Available sizes: 4, 9, 16\nEnter size: ");
                scanf("%d", &size);
                if (size != 4 && size != 9 && size != 16) {
                    printf(ERROR "Invalid size! Using default 9\n" RESET);
                    size = 9;
                }
                break;
            }
            // Change Difficulty
            case 3: {
                printf("Difficulty levels:\n1. Easy\n2. Medium\n3. Hard\nEnter difficulty level: ");
                scanf("%d", &difficulty);
                if (difficulty < 1 || difficulty > 3) {
                    printf(ERROR "Invalid difficulty! Using Medium\n" RESET);
                    difficulty = 2;
                }
                break;
            }
            // Save Game
            case 4: {
                if (!game) {
                    printf(ERROR "No active game!\n" RESET);
                    break;
                }
                printf("Enter filename: ");
                char filename[100];
                scanf("%s", filename);
                saveGame(game, filename);
                printf("Game saved!\n" RESET);
                break;
            }
            // Load Game
            case 5: {
                printf("Enter filename: ");
                char filename[100];
                scanf("%s", filename);
                GameState* loaded = loadGame(filename);
                if (loaded) {
                    if (game) {
                        freeGameState(game);
                    }
                    game = loaded;
                    size = game->size;
                    difficulty = game->difficulty;
                    handleGame(game);
                } else {
                    printf(ERROR "Failed to load game!\n" RESET);
                }
                break;
            }
            // Instructions
            case 6: {
                printf("\nHow to play:\n");
                printf("1. Enter row and column numbers (1-%d)\n", size);
                printf("2. Enter value (1-%d)\n", size);
                printf("3. Cells with numbers are hints and can't be changed\n");
                printf("4. Enter 0 to return to menu\n");
                break;
            }
            // Exit
            case 7:
                if (game) {
                    freeGameState(game);
                }
                return 0;
            default:
                printf(ERROR "Invalid choice!\n" RESET);
        }
    }
}