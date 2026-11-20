#ifndef MAZE_H
#define MAZE_H

#include <basicgol.h>

ENUMERACAO(Direction)
    North = 1,
    East = 2,
    South = 4,
    West = 8
FIM_ENUMERACAO(Direction);

REGISTRO(Cell)
    INTEIRO x;
    INTEIRO y;
FIM_REGISTRO(Cell);

REGISTRO(Maze)
    INTEIRO num_rows;
    INTEIRO num_cols;
    INTEIRO num_lines;
    INTEIRO line_len;
    CARACTERE *lines; // as stored in file
    CARACTERE *m; // as encoded in memory
FIM_REGISTRO(Maze);

REGISTRO(Path)
    LOGICO found_path;
    INTEIRO num_steps; // indexes into cells
    Cell *cells;
FIM_REGISTRO(Path);

// ------------------------------------------
// Lifecycle management
// ------------------------------------------
/**
 * @brief Dynamically allocates memory associated with the Maze structure.
 *
 * This function allocates 1-D array of chars for `lines` and `m`. However,
 * there's a dependency before calling this function. Maze members `num_rows`
 * and `num_cols` have to be properly set.
 *
 * @param[in,out] maze Pointer to the Maze struct to be deallocated.
 */
PROCEDIMENTO create_maze(Maze *maze);

/**
 * @brief Frees all dynamically allocated memory associated with the Maze structure.
 *
 * This function cleans up the row string buffers (`lines`) and the flattened
 * encoded grid (`m`), resetting the maze pointer to prevent memory leaks.
 *
 * @param[in,out] maze Pointer to the Maze struct to be deallocated.
 */
PROCEDIMENTO free_maze(Maze *maze);

#endif // MAZE_H
