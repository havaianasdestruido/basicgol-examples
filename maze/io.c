#include <basicgol.h>
#include "maze.h"
#include "io.h"
#include "solver.h"

/**
 * @brief Calculates the number of columns in the maze from the input file.
 *
 * Scans the first line of the file to determine the width of the maze
 * based on the character pattern.
 *
 * @param[in] fp Pointer to the opened file stream.
 * @return The total number of columns found.
 */
FUNCAO INTEIRO get_num_cols(FILE *fp) {
    INTEIRO num_corners = 0;

    INTEIRO ch; // fgetc() returns int and EOF is int
    ENQUANTO (ch = fgetc(fp)) != '\n' E ch != EOF FACA
        SE ch == '+' ENTAO
            num_corners++;
        FIM_SE
    FIM_ENQUANTO

    // Reset fp to start
    fseek(fp, 0, SEEK_SET);

    RETORNE num_corners - 1;
}

/**
 * @brief Calculates the number of rows in the maze from the input file.
 *
 * Counts the total lines in the file to determine the grid height.
 *
 * @param[in] fp Pointer to the opened file stream.
 * @return The total number of rows found.
 */
FUNCAO INTEIRO get_num_rows(FILE *fp) {
    INTEIRO num_lines = 0;

    CARACTERE line[200]; // an arbitrary limit
    ENQUANTO fgets(line, 200, fp) != NULL FACA
        num_lines++;
    FIM_ENQUANTO

    // Reset fp to start
    fseek(fp, 0, SEEK_SET);

    RETORNE (num_lines - 1) / 2;
}

/* Implementation as declared in io.h */
PROCEDIMENTO read_maze_from_file(Maze *maze, CARACTERE *filename) {
    INTEIRO i;
    FILE *fp = fopen(filename, "r");
    SE fp == NULL ENTAO
        ESCREVA_FMT("Error: unable to open maze file %s. Quitting...\n", filename);
        exit(1);
    FIM_SE

    maze->num_cols = get_num_cols(fp);
    maze->num_rows = get_num_rows(fp);

    create_maze(maze);

    CARACTERE (*lines)[maze->line_len] = (CARACTERE (*)[maze->line_len])maze->lines;
    PARA(i, 0, maze->num_lines - 1) {
        SE fgets(lines[i], maze->line_len, fp) == NULL ENTAO
            lines[i][0] = '\0';
        FIM_SE
    }

    fclose(fp);
}

/* Implementation as declared in io.h */
PROCEDIMENTO encode_maze(Maze *maze) {
    INTEIRO r, c;
    CARACTERE (*lines)[maze->line_len] = (CARACTERE (*)[maze->line_len])maze->lines;
    CARACTERE (*m)[maze->num_cols] = (CARACTERE (*)[maze->num_cols])maze->m;

    PARA(r, 0, maze->num_rows - 1) {
        PARA(c, 0, maze->num_cols - 1) {
            CARACTERE cell_val = 0;

            SE lines[2 * r][4 * c + 1] == '-' ENTAO
                cell_val |= North;
            FIM_SE
            SE lines[2 * r + 1][4 * c + 4] == '|' ENTAO
                cell_val |= East;
            FIM_SE
            SE lines[2 * r + 2][4 * c + 1] == '-' ENTAO
                cell_val |= South;
            FIM_SE
            SE lines[2 * r + 1][4 * c] == '|' ENTAO
                cell_val |= West;
            FIM_SE

            m[r][c] = cell_val;
        }
    }
}

/* Implementation as declared in io.h */
PROCEDIMENTO print_encoded_maze(Maze *maze) {
    INTEIRO i, j;
    PARA(i, 0, maze->num_rows - 1) {
        PARA(j, 0, maze->num_cols - 1) {
            ESCREVA_FMT("0x%02X", (NATURAL8)maze->m[i*maze->num_cols + j]);
            SE j == maze->num_cols-1 ENTAO
                ESCREVA_LINHA();
            SENAO
                ESCREVA(" ");
            FIM_SE
        }
    }
}

/* Implementation as declared in io.h */
PROCEDIMENTO print_maze(Maze *maze, Path *path) {
    INTEIRO r, c;
    CARACTERE (*m)[maze->num_cols] = (CARACTERE (*)[maze->num_cols])maze->m;

    PARA(r, 0, maze->num_rows - 1) {

        // --- 1. Print the North Walls Row ---
        PARA(c, 0, maze->num_cols - 1) {
            ESCREVA("+");
            SE m[r][c] & North ENTAO
                ESCREVA("---");
            SENAO
                ESCREVA("   ");
            FIM_SE
        }
        // Caps off the right side of the North boundary row
        ESCREVAL("+");

        // --- 2. Print the Cell Middle Row (West wall, Space/*, East wall) ---
        PARA(c, 0, maze->num_cols - 1) {
            // Print the West wall of the cell
            SE m[r][c] & West ENTAO
                ESCREVA("|");
            SENAO
                ESCREVA(" ");
            FIM_SE

            // Print the cell interior center (Path marker '*' or empty space)
            SE is_on_path(r, c, path) ENTAO
                ESCREVA(" * ");
            SENAO
                ESCREVA("   ");
            FIM_SE
        }
        // Caps off the very last East wall of the current row
        SE m[r][maze->num_cols - 1] & East ENTAO
            ESCREVAL("|");
        SENAO
            ESCREVAL(" ");
        FIM_SE
    }

    // --- 3. Print the Final South Wall Row ---
    // The bottom-most outer border needs to be closed out cleanly
    PARA(c, 0, maze->num_cols - 1) {
        ESCREVA("+");
        SE m[maze->num_rows - 1][c] & South ENTAO
            ESCREVA("---");
        SENAO
            ESCREVA("   ");
        FIM_SE
    }
    ESCREVAL("+");
}
