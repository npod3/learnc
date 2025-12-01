// Purpose: Demonstrate fundamental C basics: variables, types, operators, scopes, constants.
// Key Concepts:
//   - Primitive types: int, unsigned, char, float, double, size_t
//   - Initialization vs assignment
//   - Arithmetic, relational, logical, bitwise operators
//   - const correctness
//   - Block scope & shadowing
//   - Implicit conversions & explicit casts
// Compile Example:
//   gcc -std=c17 -Wall -Wextra -Wpedantic -O2 -Iinclude src/*.c src/examples/*.c -o bin/learnc.exe
// Pitfalls:
//   - Uninitialized variables lead to indeterminate values (avoid)
//   - Implicit narrowing conversions can lose data
//   - Division with integers truncates (use casting for float division)
//   - Operator precedence confusion: use parentheses
//   - Signed overflow is undefined behavior; avoid relying on wrap

#include <stdio.h>
#include <limits.h>
#include <stdint.h>
#include <stddef.h>

int example_basics(void) {
    printf("== Basics Example ==\n");

    // Declaration + initialization
    int a = 10;            // signed int
    unsigned ua = 42u;     // unsigned int literal
    long l = 1000L;        // long literal
    float f = 3.14f;       // float literal
    double d = 2.718281828; // double literal
    char c = 'A';          // character literal
    const int DAYS_IN_WEEK = 7; // const prevents modification

    // size_t: unsigned type for sizes & indices
    size_t sz = sizeof(int);

    // Print values
    printf("a=%d ua=%u l=%ld f=%.2f d=%.6f c=%c sz=%zu\n", a, ua, l, f, d, c, sz);

    // Arithmetic
    int sum = a + (int)ua; // cast for clarity
    int diff = a - (int)ua;
    int prod = a * (int)ua;
    int quot = ua != 0 ? a / (int)ua : 0; // integer division truncates
    int mod  = ua != 0 ? a % (int)ua : 0;
    printf("sum=%d diff=%d prod=%d quot=%d mod=%d\n", sum, diff, prod, quot, mod);

    // Floating vs integer division
    double precise = (double)a / (double)ua; // force floating point
    printf("precise division a/ua=%.5f vs integer=%d\n", precise, quot);

    // Relational and logical
    int gt = a > (int)ua;  // 0 or 1
    int eq = a == (int)ua; // equality check
    int complex_logic = (a < 100 && ua > 10) || (c == 'Z');
    printf("gt=%d eq=%d complex_logic=%d\n", gt, eq, complex_logic);

    // Bitwise operations (on integers)
    unsigned x = 0x5u; // 0101
    unsigned y = 0xAu; // 1010
    unsigned andv = x & y; // 0000
    unsigned orv  = x | y; // 1111
    unsigned xorv = x ^ y; // 1111
    unsigned shl  = x << 1; // 1010
    unsigned shr  = y >> 1; // 0101
    printf("bitwise: and=%X or=%X xor=%X shl=%X shr=%X\n", andv, orv, xorv, shl, shr);

    // Casting and promotions
    char small = 120; // fits in signed char
    int promoted = small + 5; // char promoted to int in arithmetic
    printf("small=%d promoted=%d\n", (int)small, promoted);

    // Overflow caution (signed overflow UB); unsigned defined modulo 2^N
    unsigned maxu = UINT_MAX;
    unsigned wrap = maxu + 1u; // wraps to 0 (defined behavior)
    printf("unsigned wrap: UINT_MAX=%u wrap=%u\n", maxu, wrap);

    // Block scope and shadowing
    int scoped = 1;
    printf("outer scoped=%d\n", scoped);
    {
        int scoped = 2; // shadows outer variable
        scoped += 3;
        printf("inner scoped=%d\n", scoped);
    }
    printf("outer scoped still=%d\n", scoped);

    // const demonstration
    // DAYS_IN_WEEK = 8; // would be compile error
    printf("DAYS_IN_WEEK=%d\n", DAYS_IN_WEEK);

    // sizeof examples
    printf("sizeof(char)=%zu sizeof(int)=%zu sizeof(double)=%zu\n", sizeof(char), sizeof(int), sizeof(double));

    // Boolean demonstration (C uses int for conditions; 0=false, non-zero=true)
    int flag = 0;
    if (!flag) {
        printf("flag is false (0)\n");
    }
    flag = 5; // non-zero
    if (flag) {
        printf("flag is true (non-zero: %d)\n", flag);
    }

    // Use of ternary operator
    int max_ab = (a > (int)ua) ? a : (int)ua;
    printf("max(a,ua)=%d\n", max_ab);

    // Return success
    return 0;
}
