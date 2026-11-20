#include <basicgol.h>
#include "maze.h"
#include "io.h"
#include "solver.h"

#define DEBUG_SOLVER 0

/* Implementation as declared in solver.h */
FUNCAO LOGICO is_on_path(INTEIRO r, INTEIRO c, Path *path) {
    INTEIRO i;
    SE path == NULL ENTAO
        RETORNE FALSO;
    FIM_SE
    PARA(i, 0, path->num_steps - 1) {
        SE path->cells[i].x == r E path->cells[i].y == c ENTAO
            RETORNE VERDADEIRO;
        FIM_SE
    }
    RETORNE FALSO;
}

/**
 * @brief Core recursive function that explores the maze layout using Depth-First Search (DFS).
 *
 * Navigates from cell to cell by assessing valid moves (openings with no walls) while
 * updating the active path array and tracking the incoming entry direction to prevent backtracking.
 *
 * @param[in]     x        The current cell row coordinate.
 * @param[in]     y        The current cell column coordinate.
 * @param[in]     in       The direction from which the algorithm entered the current cell.
 * @param[in]     maze     Pointer to the encoded maze structure.
 * @param[in,out] path     Pointer to the active path tracking struct.
 * @param[in]     path_idx The current depth/step index within the execution path.
 * @return A pointer to the final Cell array containing the path sequence, or NULL if blocked.
 */
FUNCAO Cell* explore(INTEIRO x, INTEIRO y, Direction in, Maze *maze, Path *path, INTEIRO path_idx) {
    INTEIRO i;
    Direction dirs[] = {North, East, South, West};
    INTEIRO num_dirs = sizeof(dirs) / sizeof(dirs[0]);

    #if DEBUG_SOLVER
    ESCREVA_FMT("explore(%d, %d, %d, %d)\n", x, y, in, path_idx);
    #endif

    // Skip if indices are out of bounds
    SE x < 0 OU x >= maze->num_rows OU y < 0 OU y >= maze->num_cols ENTAO
        RETORNE NULL;
    FIM_SE

    SE x == maze->num_rows-1 E y == maze->num_cols-1 ENTAO
        // We have reached the bottom-right cell: Success!
        path->found_path = 1;
        path->num_steps = path_idx + 1;
        path->cells[path_idx].x = x;
        path->cells[path_idx].y = y;
        RETORNE path->cells + path_idx;
    FIM_SE

    Cell *next = NULL;
    PARA(i, 0, num_dirs - 1) {
        // Don't explore the way we came in
        SE dirs[i] == in ENTAO
            PROSSIGA;
        FIM_SE

        // Bit-wise operation non-zero implies a wall
        SE (maze->m[x*maze->num_cols + y] & dirs[i]) ENTAO
            PROSSIGA;
        FIM_SE

        ESCOLHA(dirs[i])
            CASO North:
                next = explore(x-1, y, South, maze, path, path_idx+1);
                PARE;
            CASO East:
                next = explore(x, y+1, West, maze, path, path_idx+1);
                PARE;
            CASO South:
                next = explore(x+1, y, North, maze, path, path_idx+1);
                PARE;
            CASO West:
                next = explore(x, y-1, East, maze, path, path_idx+1);
                PARE;
        FIM_ESCOLHA

        // If found a path, don't search in other directions
        SE path->found_path ENTAO
            PARE;
        FIM_SE
    }

    SE next ENTAO
        // Found a path
        path->cells[path_idx].x = x;
        path->cells[path_idx].y = y;
        RETORNE path->cells + path_idx;
    FIM_SE

    RETORNE NULL;
}

/* Implementation as declared in solver.h */
PROCEDIMENTO solve_maze(Maze *maze) {
    INTEIRO i;
    Path path;
    path.found_path = FALSO;
    path.cells = malloc(maze->num_rows * maze->num_cols * sizeof(Cell));

    explore(0, 0, West, maze, &path, 0);
    ESCREVA_FMT("Found maze path of %d steps: ", path.num_steps);
    PARA(i, 0, path.num_steps - 1) {
        ESCREVA_FMT("(%d, %d) ", path.cells[i].x, path.cells[i].y);
    }
    ESCREVA_FMT("\n\n");
    print_maze(maze, &path);

    free(path.cells);
}
