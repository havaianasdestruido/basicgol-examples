#include <basicgol.h>
#include "maze.h"

/* Implementation as declared in maze.h */
PROCEDIMENTO create_maze(Maze *maze) {
    maze->num_lines = 2 * (maze->num_rows) + 1;
    maze->line_len = 4 * (maze->num_cols) + 3; // 4 chars per cell + 1 East boundary + '\n' + '\0'
    maze->lines = calloc(maze->num_lines * maze->line_len, sizeof(CARACTERE));
    maze->m = calloc(maze->num_rows * maze->num_cols, sizeof(CARACTERE));
}

/* Implementation as declared in maze.h */
PROCEDIMENTO free_maze(Maze *maze) {
    free(maze->lines);
    free(maze->m);
}
