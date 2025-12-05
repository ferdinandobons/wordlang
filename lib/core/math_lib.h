/*
 * Wordlang Math Library
 * Core C library - compiled with interpreter
 */

#ifndef WL_MATH_LIB_H
#define WL_MATH_LIB_H

#include <stdlib.h>
#include <math.h>
#include <time.h>

// Initialize random seed (call once at startup)
static int _wl_math_seeded = 0;
static void wl_math_init() {
    if (!_wl_math_seeded) {
        srand((unsigned int)time(NULL));
        _wl_math_seeded = 1;
    }
}

// Absolute value
static int wl_abs(int x) {
    return x < 0 ? -x : x;
}

// Minimum of two values
static int wl_min(int a, int b) {
    return a < b ? a : b;
}

// Maximum of two values
static int wl_max(int a, int b) {
    return a > b ? a : b;
}

// Sign of a number (-1, 0, or 1)
static int wl_sign(int x) {
    if (x > 0) return 1;
    if (x < 0) return -1;
    return 0;
}

// Integer square root
static int wl_sqrt(int x) {
    if (x < 0) return 0;
    return (int)sqrt((double)x);
}

// Random number 0-99
static int wl_random() {
    wl_math_init();
    return rand() % 100;
}

// Random integer 0 to max-1
static int wl_randint(int max) {
    wl_math_init();
    if (max <= 0) return 0;
    return rand() % max;
}

// Random integer in range [min, max)
static int wl_randrange(int min, int max) {
    wl_math_init();
    if (max <= min) return min;
    return min + (rand() % (max - min));
}

// Clamp value between min and max
static int wl_clamp(int x, int min, int max) {
    if (x < min) return min;
    if (x > max) return max;
    return x;
}

// Floor division (always rounds down)
__attribute__((unused)) static int wl_floordiv(int a, int b) {
    if (b == 0) return 0;
    int q = a / b;
    if ((a % b != 0) && ((a < 0) != (b < 0))) q--;
    return q;
}

// GCD (greatest common divisor)
static int wl_gcd(int a, int b) {
    a = wl_abs(a);
    b = wl_abs(b);
    while (b != 0) {
        int t = b;
        b = a % b;
        a = t;
    }
    return a;
}

// LCM (least common multiple)
static int wl_lcm(int a, int b) {
    if (a == 0 || b == 0) return 0;
    return wl_abs(a * b) / wl_gcd(a, b);
}

// Factorial
static int wl_factorial(int n) {
    if (n < 0) return 0;
    if (n <= 1) return 1;
    int result = 1;
    for (int i = 2; i <= n; i++) {
        result *= i;
    }
    return result;
}

// Is even
static int wl_is_even(int x) {
    return (x % 2) == 0;
}

// Is odd
static int wl_is_odd(int x) {
    return (x % 2) != 0;
}

#endif

