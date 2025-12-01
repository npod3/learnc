// Purpose: Entry point with interactive menu to run C examples.
// Key Concepts: Function pointers, structured table of examples, user input loop.
// Compile: See README or Makefile; e.g.
//   gcc -std=c17 -Wall -Wextra -Wpedantic -O2 -Iinclude src/*.c src/examples/*.c -o bin/learnc.exe -lws2_32

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "examples.h"
#include "platform.h"

typedef struct ExampleEntry {
    int id;
    const char *name;
    int (*fn)(void);
} ExampleEntry;

static ExampleEntry examples[] = {
    { 1, "Basics", example_basics },
    { 2, "Control Flow", example_control_flow },
    { 3, "Pointers & Arrays", example_pointers_arrays },
    { 4, "Strings", example_strings },
    { 5, "Structs & Enums", example_structs_enums },
    { 6, "Memory Management", example_memory },
    { 7, "File I/O", example_file_io },
    { 8, "Macros", example_macros },
    { 9, "Modules / Compilation Units", example_modules },
    {10, "Time & Random", example_time_random },
    {11, "Error Handling", example_error_handling },
    {12, "Function Pointers", example_function_pointers },
    {13, "Dynamic Arrays", example_dynamic_arrays },
    {14, "Bitwise Ops", example_bitwise },
    {15, "Threading (C11)", example_threading },
    {16, "Sockets (TCP)", example_sockets },
    {17, "Math & Floats", example_math },
    {18, "Snake Game", example_game_snake },
    {19, "ANSI Colors", example_ansi_colors },
    {20, "Build Config / Platform", example_build_config },
    {21, "Serialization", example_serialization }
};

static void print_menu(void) {
    printf("\n=== Learn C Menu ===\n");
    size_t count = sizeof(examples)/sizeof(examples[0]);
    for (size_t i = 0; i < count; ++i) {
        printf("%2d) %s\n", examples[i].id, examples[i].name);
    }
    printf(" 0) Exit\n");
    printf("Select example number: ");
    fflush(stdout);
}

static int read_int_line(void) {
    char buf[64];
    if (!fgets(buf, sizeof(buf), stdin)) return -1;
    return atoi(buf);
}

int main(void) {
    while (1) {
        print_menu();
        int choice = read_int_line();
        if (choice == 0) {
            printf("Exiting.\n");
            break;
        }
        int found = 0;
        for (size_t i = 0; i < sizeof(examples)/sizeof(examples[0]); ++i) {
            if (examples[i].id == choice) {
                found = 1;
                platform_clear_screen();
                printf("-- Running: %s --\n", examples[i].name);
                int rc = examples[i].fn();
                printf("\n(Return code: %d)\n", rc);
                printf("Press Enter to return to menu...");
                fflush(stdout);
                (void)fgets((char[4]){0}, 4, stdin); // Wait minimal input
                break;
            }
        }
        if (!found) {
            printf("Invalid selection. Try again.\n");
        }
    }
    return 0;
}
