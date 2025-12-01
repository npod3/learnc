// Purpose: Terminal Snake game demonstrating state management, input polling, timing, and simple rendering.
// Key Concepts:
//   - Game loop with fixed timestep
//   - Non-blocking keyboard input (platform abstraction)
//   - 2D grid representation
//   - Dynamic snake growth and collision detection
//   - Simple double-buffer drawing
// Compile:
//   gcc -std=c17 -Wall -Wextra -Wpedantic -O2 -Iinclude src/*.c src/examples/*.c -o bin/learnc.exe -lws2_32
// Controls: W (up), A (left), S (down), D (right), Q (quit)
// Pitfalls:
//   - Avoid reading input in a blocking manner inside the loop
//   - Ensure snake body update order prevents overwriting head position prematurely
//   - Avoid using system("cls")/system("clear") repeatedly (slow); we use ANSI clear

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "platform.h"

#define GRID_W 20
#define GRID_H 20
#define MAX_SNAKE (GRID_W * GRID_H)

typedef struct { int x, y; } Cell;

typedef enum { DIR_UP, DIR_DOWN, DIR_LEFT, DIR_RIGHT } Direction;

static Cell snake[MAX_SNAKE];
static size_t snake_len;
static Direction dir;
static Cell food;
static int alive;
static int score;

static void place_food(void) {
    // Simple pseudo-random using timestamp
    uint64_t t = platform_millis();
    food.x = (int)(t % GRID_W);
    food.y = (int)((t / GRID_W) % GRID_H);
    // Ensure not on snake
    for (size_t i = 0; i < snake_len; ++i) {
        if (snake[i].x == food.x && snake[i].y == food.y) {
            food.x = (food.x + 5) % GRID_W;
            food.y = (food.y + 7) % GRID_H;
            i = 0; // restart check
        }
    }
}

static void init_game(void) {
    snake_len = 3;
    snake[0].x = GRID_W/2; snake[0].y = GRID_H/2;
    snake[1].x = GRID_W/2 - 1; snake[1].y = GRID_H/2;
    snake[2].x = GRID_W/2 - 2; snake[2].y = GRID_H/2;
    dir = DIR_RIGHT;
    score = 0;
    alive = 1;
    place_food();
}

static int collides(int x, int y) {
    if (x < 0 || y < 0 || x >= GRID_W || y >= GRID_H) return 1;
    for (size_t i = 0; i < snake_len; ++i) {
        if (snake[i].x == x && snake[i].y == y) return 1;
    }
    return 0;
}

static void update_dir_from_key(int ch) {
    switch (ch) {
        case 'w': case 'W': if (dir != DIR_DOWN) dir = DIR_UP; break;
        case 's': case 'S': if (dir != DIR_UP) dir = DIR_DOWN; break;
        case 'a': case 'A': if (dir != DIR_RIGHT) dir = DIR_LEFT; break;
        case 'd': case 'D': if (dir != DIR_LEFT) dir = DIR_RIGHT; break;
        default: break;
    }
}

static void step(void) {
    // Compute new head
    Cell head = snake[0];
    switch (dir) {
        case DIR_UP: head.y -= 1; break;
        case DIR_DOWN: head.y += 1; break;
        case DIR_LEFT: head.x -= 1; break;
        case DIR_RIGHT: head.x += 1; break;
    }
    // Check collision with walls or self
    for (size_t i = 0; i < snake_len; ++i) {
        if (snake[i].x == head.x && snake[i].y == head.y) { alive = 0; return; }
    }
    if (head.x < 0 || head.y < 0 || head.x >= GRID_W || head.y >= GRID_H) { alive = 0; return; }

    // Move body: shift back
    memmove(&snake[1], &snake[0], snake_len * sizeof(Cell));
    snake[0] = head;

    // Check food
    if (head.x == food.x && head.y == food.y) {
        if (snake_len < MAX_SNAKE) {
            snake_len++;
            score += 10;
            place_food();
        }
    } else {
        // Remove last cell if not eating: accomplished by shifting w/o extra tail growth
        // memmove already grown body; need to discard last. Achieved by not adding beyond length.
        // Nothing extra required here.
    }
}

static void draw(void) {
    platform_clear_screen();
    char grid[GRID_H][GRID_W];
    for (int y = 0; y < GRID_H; ++y) {
        for (int x = 0; x < GRID_W; ++x) grid[y][x] = ' ';
    }
    // Food
    grid[food.y][food.x] = '*';
    // Snake
    for (size_t i = 0; i < snake_len; ++i) {
        int x = snake[i].x, y = snake[i].y;
        if (x >=0 && y >=0 && x < GRID_W && y < GRID_H) {
            grid[y][x] = (i == 0) ? 'O' : 'o';
        }
    }
    // Border top
    printf("+");
    for (int x = 0; x < GRID_W; ++x) printf("-");
    printf("+\n");
    for (int y = 0; y < GRID_H; ++y) {
        printf("|");
        for (int x = 0; x < GRID_W; ++x) {
            putchar(grid[y][x]);
        }
        printf("|\n");
    }
    printf("+");
    for (int x = 0; x < GRID_W; ++x) printf("-");
    printf("+\n");
    printf("Score: %d  Length: %zu  (WASD to move, Q to quit)\n", score, snake_len);
}

int example_game_snake(void) {
    init_game();
    const unsigned frame_ms = 120; // ~8 FPS
    uint64_t last = platform_millis();
    while (alive) {
        // Input
        int ch = platform_getch();
        if (ch == 'q' || ch == 'Q') { alive = 0; break; }
        if (ch != -1) update_dir_from_key(ch);

        uint64_t now = platform_millis();
        if (now - last >= frame_ms) {
            step();
            draw();
            last = now;
        }
        platform_sleep_ms(5); // Small sleep to reduce CPU usage
    }
    printf("Game Over. Final Score: %d\n", score);
    return 0;
}
