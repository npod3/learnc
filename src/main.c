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
    int advanced; // 0 core, 1 advanced section
} ExampleEntry;

static ExampleEntry examples[] = {
    { 1,  "Basics", example_basics, 0 },
    { 2,  "Control Flow", example_control_flow, 0 },
    { 3,  "Pointers & Arrays", example_pointers_arrays, 0 },
    { 4,  "Strings", example_strings, 0 },
    { 5,  "Structs & Enums", example_structs_enums, 0 },
    { 6,  "Memory Management", example_memory, 0 },
    { 7,  "File I/O", example_file_io, 0 },
    { 8,  "Macros", example_macros, 0 },
    { 9,  "Modules / Compilation Units", example_modules, 0 },
    {10,  "Time & Random", example_time_random, 0 },
    {11,  "Error Handling", example_error_handling, 0 },
    {12,  "Function Pointers", example_function_pointers, 0 },
    {13,  "Dynamic Arrays", example_dynamic_arrays, 0 },
    {14,  "Bitwise Ops", example_bitwise, 0 },
    {15,  "Threading (C11)", example_threading, 0 },
    {16,  "Sockets (TCP)", example_sockets, 0 },
    {17,  "Math & Floats", example_math, 0 },
    {18,  "Snake Game", example_game_snake, 0 },
    {19,  "ANSI Colors", example_ansi_colors, 0 },
    {20,  "Build Config / Platform", example_build_config, 0 },
    {21,  "Serialization", example_serialization, 0 },
    // Advanced topics (100+ IDs)
    {101, "Memory – Advanced", example_memory_advanced, 1 },
    {102, "Atomics & Concurrency", example_atomics_concurrency, 1 },
    {103, "Threading – Queue", example_threading_queue, 1 },
    {104, "Profiling & Timing", example_profiling_timing, 1 },
    {105, "SIMD Basics", example_simd_basics, 1 },
    {106, "Parsing FSM", example_parsing_fsm, 1 },
    {107, "Modular Plugins", example_modular_plugins, 1 },
    {108, "Binary Serialization", example_serialization_binary, 1 },
    {109, "Security Basics", example_security_basics, 1 },
    {110, "Networking select()", example_networking_select, 1 },
    {111, "Error Strategy", example_error_strategy, 1 },
    {112, "Build System Notes", example_build_system_notes, 1 },
    {113, "FFI Rust Bridge", example_ffi_rust_bridge, 1 },
    {114, "Testing Harness", example_testing_harness, 1 },
    {115, "Resource Graph", example_resource_graph, 1 },
    {116, "Logging System", example_logging_system, 1 },
    {117, "Blackjack Twist (Game)", example_blackjack_twist, 1 }
};

static void print_menu(void) {
    printf("\n=== Learn C Menu ===\n");
    size_t count = sizeof(examples)/sizeof(examples[0]);
    int advanced_header_printed = 0;
    for (size_t i = 0; i < count; ++i) {
        if (examples[i].advanced && !advanced_header_printed) {
            printf("\n=== Advanced Topics ===\n");
            advanced_header_printed = 1;
        }
        printf("%3d) %s\n", examples[i].id, examples[i].name);
    }
    printf("  0) Exit\n");
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
