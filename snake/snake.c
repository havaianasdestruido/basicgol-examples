/*
This implements the snake game where the snake grows each
time it eats a fruit. The game ends if the snake crashes
into a wall or its own body.

Instead of using ASCII characters, we use emojis to make
this game more colorful. When stored in memory, they will
be in UTF-8 encoding. To understand emojis,
see https://unicode.org/emoji/charts/full-emoji-list.html
To understand UTF-8,
see https://datatracker.ietf.org/doc/html/rfc3629 (sec. 3)

Here's an example of UTF-8 encoding of "brick" emoji:
- Unicode U+1F9F1
- UTF-8 encoding range:
     0001 0000-0010 FFFF >> 11110xxx 10xxxxxx 10xxxxxx 10xxxxxx
  => 0001 F9F1
  =  0001 1111 1001 1111 0001 >> 11110000 10011111 10100111 10110001
  =  F0 9F A7 B1

This code works on a Windows terminal but won't work on
a Linux terminal.

Note: It's common in gaming apps to view columns along x-axis
and rows along y-axis. In this implementation, we take the
approach of rows along x-axis and columns along y-axis. Hence,
we access the game board as grid[x][y] rather than grid[y][x].

TODO (some improvements to consider)
- Make the game faster when snake exceeds some length
- Make the game faster if game is being played for too long
- Give different scores for different fruits but more valuable
  fruits must be rarer
- Fruit disappears if not consumed within a fixed time
- Award bonus points if fruit is consumed quickly
- Allow 1-3 fruits on the board at the same time
- Extend the code to run on POSIX/Linux terminals as well
*/

#include <basicgol.h>

#include <time.h>
#include <ctype.h>
#include <conio.h>
#include <windows.h>

// Excludes the walls
#define WIDTH 30
#define HEIGHT 20

REGISTRO(Snake)
    INTEIRO x[WIDTH * HEIGHT]; // rows
    INTEIRO y[WIDTH * HEIGHT]; // cols
    INTEIRO len; // including the head at (x[0], y[0])
FIM_REGISTRO(Snake);
Snake snake;

ENUMERACAO(Direction)
    STOP = 0,
    LEFT,
    RIGHT,
    UP,
    DOWN
FIM_ENUMERACAO(Direction);
Direction dir;

CARACTERE *fruits[] = {"🍎", "🍌", "🍇", "🍉", "🥝", "🍍", "🍐", "🍊"};
INTEIRO num_fruits = TAMANHO_VETOR(fruits);
REGISTRO(Fruit)
    INTEIRO x, y; // only one fruit at a time
    INTEIRO which;
FIM_REGISTRO(Fruit);
Fruit fruit;

LOGICO gameOver;
INTEIRO score;
INTEIRO tick_ms = 100;

PROCEDIMENTO create_fruit() {
    INTEIRO i;
    LOGICO overlaps = VERDADEIRO;
    ENQUANTO overlaps FACA
        overlaps = FALSO;
        fruit.x = rand() % HEIGHT;
        fruit.y = rand() % WIDTH;
        PARA(i, 0, snake.len - 1) {
            SE fruit.x == snake.x[i] E fruit.y == snake.y[i] ENTAO
                overlaps = VERDADEIRO;
                PARE;
            FIM_SE
        }
    FIM_ENQUANTO
    fruit.which = rand() % num_fruits;
}

PROCEDIMENTO init_game() {
    gameOver = FALSO;

    srand(time(NULL));

    dir = STOP; // game begins only when a key is pressed

    snake.x[0] = HEIGHT / 2;
    snake.y[0] = WIDTH / 2;
    snake.len = 1;

    create_fruit();

    score = 0;
}

PROCEDIMENTO draw_board() {
    INTEIRO i, j, k;
    // Reset cursor to top-left to reduce flicker
    // TODO Improve this code to completely eliminate flicker
    COORD cursorPosition;
    cursorPosition.X = 0;
    cursorPosition.Y = 0;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cursorPosition);

    CARACTERE brick[] = "🧱";

    // Top wall
    PARA(i, 0, WIDTH + 1) ESCREVA(brick);
    ESCREVA_LINHA();

    PARA(i, 0, HEIGHT - 1) { // within the walls
        ESCREVA(brick); // left wall
        PARA(j, 0, WIDTH - 1) { // within the walls
            SE i == snake.x[0] E j == snake.y[0] ENTAO
                ESCREVA("🐸"); // actually a frog head!
            SENAO_SE i == fruit.x E j == fruit.y ENTAO
                ESCREVA(fruits[fruit.which]);
            SENAO
                LOGICO is_tail = FALSO;
                PARA(k, 1, snake.len - 1) {
                    SE i == snake.x[k] E j == snake.y[k] ENTAO
                        ESCREVA("🟢"); // snake body
                        is_tail = VERDADEIRO;
                    FIM_SE
                }
                SE NAO is_tail ENTAO
                    ESCREVA("⬜");
                FIM_SE
            FIM_SE
        }
        ESCREVA(brick); // right wall
        ESCREVA_LINHA();
    }

    // Bottom wall
    PARA(i, 0, WIDTH + 1) ESCREVA(brick);
    ESCREVA_LINHA();

    // Print score
    ESCREVA_FMT("\nScore: %d; Snake length: %d\n", score, snake.len);
    ESCREVAL("Use WASD keys to move. Press Q to quit.");
}

PROCEDIMENTO process_user_input() {
    SE _kbhit() ENTAO
        ESCOLHA(tolower(_getch()))
            // if statements below => we can't reverse from current dir
            CASO 'a':
                SE dir != RIGHT ENTAO
                    dir = LEFT;
                FIM_SE
                PARE;
            CASO 'd':
                SE dir != LEFT ENTAO
                    dir = RIGHT;
                FIM_SE
                PARE;
            CASO 'w':
                SE dir != DOWN ENTAO
                    dir = UP;
                FIM_SE
                PARE;
            CASO 's':
                SE dir != UP ENTAO
                    dir = DOWN;
                FIM_SE
                PARE;
            CASO 'q':
                gameOver = 1;
                PARE;
        FIM_ESCOLHA
    FIM_SE
}

PROCEDIMENTO update_board() {
    // Return if there's nothing to update
    SE gameOver OU dir == STOP ENTAO
        RETORNE;
    FIM_SE

    // Fruit consumption
    SE snake.x[0] == fruit.x E snake.y[0] == fruit.y ENTAO
        score += 10;

        snake.x[snake.len] = snake.x[snake.len-1];
        snake.y[snake.len] = snake.y[snake.len-1];
        snake.len++;

        create_fruit();
    FIM_SE

    // Move the body
    for (INTEIRO i = snake.len; i > 1; i--) {
        snake.x[i-1] = snake.x[i-2];
        snake.y[i-1] = snake.y[i-2];
    }

    // Move the head
    ESCOLHA(dir)
        CASO LEFT:  snake.y[0]--; PARE;
        CASO RIGHT: snake.y[0]++; PARE;
        CASO UP:    snake.x[0]--; PARE;
        CASO DOWN:  snake.x[0]++; PARE;
        CONTRARIO: PARE;
    FIM_ESCOLHA

    // Wall collision
    SE snake.x[0] >= HEIGHT OU snake.x[0] < 0 OU snake.y[0] >= WIDTH OU snake.y[0] < 0 ENTAO
        gameOver = VERDADEIRO;
    FIM_SE

    // Self-collision
    for (INTEIRO i = 1; NAO gameOver E i < snake.len; i++) {
        SE snake.x[i] == snake.x[0] E snake.y[i] == snake.y[0] ENTAO
            gameOver = VERDADEIRO;
            PARE;
        FIM_SE
    }
}

INICIO
    init_game();
    ENQUANTO NAO gameOver FACA
        draw_board();
        process_user_input();
        update_board();
        Sleep(tick_ms);
    FIM_ENQUANTO
    ESCREVA_FMT("\nGame Over! Final Score: %d\n", score);
    RETORNE 0;
FIM
