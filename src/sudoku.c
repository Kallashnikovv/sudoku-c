#include "sudoku.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

int** createArray2D(int size) {
    int** arr = malloc(size * sizeof(int*));
    for (int i = 0; i < size; i++) {
        arr[i] = malloc(size * sizeof(int));
    }
    return arr;
}

void initializeArray2D(int** arr, int size, int value) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            arr[i][j] = value;
        }
    }
}

void freeArray2D(int** arr, int size) {
    for (int i = 0; i < size; i++) {
        free(arr[i]);
    }
    free(arr);
}

bool is_valid_move(int** grid, int size, int row, int col, int num) {
    int subgrid = (int)sqrt(size);
    
    // Check row and column
    for (int i = 0; i < size; i++) {
        if (grid[row][i] == num || grid[i][col] == num) {
            return false;
        }
    }
    
    // Check subgrid
    int start_row = row - row % subgrid;
    int start_col = col - col % subgrid;
    for (int i = 0; i < subgrid; i++) {
        for (int j = 0; j < subgrid; j++) {
            if (grid[i + start_row][j + start_col] == num) {
                return false;
            }
        }
    }
    return true;
}

bool find_empty_cell(int** grid, int size, int* row, int* col) {
    for (*row = 0; *row < size; (*row)++) {
        for (*col = 0; *col < size; (*col)++) {
            if (grid[*row][*col] == 0) {
                return true;
            }
        }
    }
    return false;
}

bool solve_sudoku(int** grid, int size) {
    int row, col;
    if (!find_empty_cell(grid, size, &row, &col)) {
        return true;
    }

    for (int num = 1; num <= size; num++) {
        if (is_valid_move(grid, size, row, col, num)) {
            grid[row][col] = num;
            if (solve_sudoku(grid, size)) {
                return true;
            }
            grid[row][col] = 0;
        }
    }
    return false;
}

int** generateFilledGrid(int size) {
    int** grid = createArray2D(size);
    initializeArray2D(grid, size, 0);
    
    // Fill diagonal subgrids
    int subgrid = (int)sqrt(size);
    for (int i = 0; i < size; i += subgrid) {
        for (int j = 0; j < subgrid; j++) {
            for (int k = 0; k < subgrid; k++) {
                int num;
                do {
                    num = rand() % size + 1;
                } while (!is_valid_move(grid, size, i + j, i + k, num));
                grid[i + j][i + k] = num;
            }
        }
    }
    
    // Solve the rest
    solve_sudoku(grid, size);
    return grid;
}

void removeNumbers(GameState* game, int difficulty) {
    int cells_to_remove;
    switch (difficulty) {
        case 1: cells_to_remove = game->size * game->size / 2; break;  // Easy
        case 2: cells_to_remove = game->size * game->size * 3 / 4; break;  // Medium
        case 3: cells_to_remove = game->size * game->size * 5 / 6; break;  // Hard
        default: cells_to_remove = game->size * game->size / 2;
    }
    
    for (int i = 0; i < cells_to_remove; i++) {
        int row, col;
        do {
            row = rand() % game->size;
            col = rand() % game->size;
        } while (game->puzzle[row][col] == 0);
        
        int original = game->puzzle[row][col];
        game->puzzle[row][col] = 0;

        // Check for unique solution
        int** temp = createArray2D(game->size);
        for (int i = 0; i < game->size; i++) {
            for (int j = 0; j < game->size; j++) {
                temp[i][j] = game->puzzle[i][j];
            }
        }

        if (!solve_sudoku(temp, game->size)) {
            // Revert if no solution
            game->puzzle[row][col] = original;
            i--;
        } else {
            // Mark cell as editable if removal was successful
            game->editable[row][col] = true;
        }
        freeArray2D(temp, game->size);
    }
}

GameState* createGameState(int size, int difficulty) {
    GameState* game = malloc(sizeof(GameState));
    game->size = size;
    game->subgrid_size = (int)sqrt(size);
    game->difficulty = difficulty;
    
    game->solution = generateFilledGrid(size);
    game->puzzle = createArray2D(size);
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            game->puzzle[i][j] = game->solution[i][j];
        }
    }
    
    game->editable = malloc(size * sizeof(bool*));
    for (int i = 0; i < size; i++) {
        game->editable[i] = malloc(size * sizeof(bool));
        for (int j = 0; j < size; j++) {
            // Initialize all cells as non-editable first
            game->editable[i][j] = false;
        }
    }
    
    removeNumbers(game, difficulty);
    return game;
}

void freeGameState(GameState* game) {
    freeArray2D(game->solution, game->size);
    freeArray2D(game->puzzle, game->size);
    for (int i = 0; i < game->size; i++) {
        free(game->editable[i]);
    }
    free(game->editable);
    free(game);
}

bool check_win_condition(GameState* game) {
    for (int i = 0; i < game->size; i++) {
        for (int j = 0; j < game->size; j++) {
            if (game->puzzle[i][j] != game->solution[i][j]) {
                return false;
            }
        }
    }
    return true;
}

void saveGame(GameState* game, const char* filename) {
    FILE* file = fopen(filename, "w");
    if (!file) {
        return;
    }

    fprintf(file, "%d %d\n", game->size, game->difficulty);
    for (int i = 0; i < game->size; i++) {
        for (int j = 0; j < game->size; j++) {
            fprintf(file, "%d %d\n", game->puzzle[i][j], game->editable[i][j]);
        }
    }
    fclose(file);
}

GameState* loadGame(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (!file) return NULL;

    int size, difficulty;
    fscanf(file, "%d %d", &size, &difficulty);
    
    GameState* game = createGameState(size, difficulty);
    
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            int value, editable;
            fscanf(file, "%d %d", &value, &editable);
            game->puzzle[i][j] = value;
            game->editable[i][j] = editable;
        }
    }
    
    fclose(file);
    return game;
}