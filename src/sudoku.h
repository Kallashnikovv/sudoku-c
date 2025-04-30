#ifndef SUDOKU_H
#define SUDOKU_H

#include <stdbool.h>

typedef struct {
    int** puzzle;
    int** solution;
    bool** editable;
    int size;
    int subgrid_size;
    int difficulty;
} GameState;

// Core game functions
int** createArray2D(int size);
void initializeArray2D(int** arr, int size, int value);
void freeArray2D(int** arr, int size);
bool is_valid_move(int** grid, int size, int row, int col, int num);
bool find_empty_cell(int** grid, int size, int* row, int* col);
bool solve_sudoku(int** grid, int size);
int** generateFilledGrid(int size);
void removeNumbers(GameState* game, int difficulty);
GameState* createGameState(int size, int difficulty);
void freeGameState(GameState* game);
bool check_win_condition(GameState* game);

// File I/O
void saveGame(GameState* game, const char* filename);
GameState* loadGame(const char* filename);

#endif