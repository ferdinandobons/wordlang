/*
 * Wordlang - types.h
 * Type definitions and constants
 */

#ifndef WORDLANG_TYPES_H
#define WORDLANG_TYPES_H

#define MAX_TOKEN_LEN 128
#define MAX_TOKENS 10000
#define MAX_VARS 500
#define MAX_FUNCTIONS 100
#define MAX_PARAMS 10
#define MAX_CLASSES 20
#define MAX_METHODS 10
#define MAX_ARRAY_SIZE 100
#define MAX_CALL_DEPTH 50
#define MAX_IMPORTS 50
#define MAX_PATH 512

// Token types
typedef enum {
    TOK_SET, TOK_TO, TOK_IF, TOK_THEN, TOK_ELSE, TOK_ELSEIF, TOK_END,
    TOK_WHILE, TOK_DO, TOK_PRINT, TOK_AND, TOK_OR, TOK_NOT,
    TOK_FOR, TOK_IN, TOK_RANGE, TOK_DEFINE, TOK_WITH, TOK_RETURN,
    TOK_CALL, TOK_CLASS, TOK_METHOD, TOK_NEW, TOK_DOT,
    TOK_INPUT, TOK_BREAK, TOK_CONTINUE,
    TOK_ARRAY, TOK_GET, TOK_PUT, TOK_LENGTH,
    TOK_CONCAT, TOK_TRUE, TOK_FALSE, TOK_APPEND,
    TOK_IMPORT, TOK_FROM, TOK_USE,
    // Operators
    TOK_PLUS, TOK_MINUS, TOK_STAR, TOK_SLASH, TOK_PERCENT, TOK_CARET,
    TOK_EQ, TOK_NE, TOK_GT, TOK_LT, TOK_GE, TOK_LE,
    TOK_THAN,
    // Core library functions
    TOK_ABS, TOK_MIN, TOK_MAX, TOK_SQRT, TOK_SIGN, TOK_RANDOM,
    TOK_RANDINT, TOK_RANDRANGE, TOK_GCD, TOK_LCM, TOK_FACTORIAL,
    TOK_CLAMP, TOK_ISEVEN, TOK_ISODD,
    // Time library
    TOK_NOW, TOK_HOUR, TOK_MINUTE, TOK_SECOND,
    TOK_DAY, TOK_MONTH, TOK_YEAR, TOK_WEEKDAY, TOK_YEARDAY,
    TOK_TIME, TOK_DATE, TOK_DATETIME, TOK_SLEEP,
    // String library
    TOK_UPPER, TOK_LOWER, TOK_TRIM, TOK_REVERSE, TOK_REPEAT,
    TOK_STARTSWITH, TOK_ENDSWITH, TOK_CONTAINS, TOK_INDEXOF,
    TOK_CHARAT, TOK_REPLACE, TOK_ISNUMERIC, TOK_ISALPHA,
    // Basic tokens
    TOK_IDENTIFIER, TOK_NUMBER, TOK_STRING, TOK_EOF,
    TOK_LPAREN, TOK_RPAREN
} TokenType;

typedef struct {
    TokenType type;
    char value[MAX_TOKEN_LEN];
} Token;

typedef struct {
    char name[64];
    int value;
    int is_string;
    char str_value[256];
    int is_array;
    int array_values[MAX_ARRAY_SIZE];
    int array_length;
    int is_instance;      // Is this an instance of a class?
    int class_index;      // Index of the class in classes array
} Variable;

typedef struct {
    char name[64];
    char params[MAX_PARAMS][64];
    int param_count;
    int body_start;
    int body_end;
} Function;

typedef struct {
    char name[64];
    int method_starts[MAX_METHODS];
    int method_ends[MAX_METHODS];
    char method_names[MAX_METHODS][64];
    char method_params[MAX_METHODS][MAX_PARAMS][64];  // Parameter names for each method
    int method_param_counts[MAX_METHODS];
    int method_count;
} Class;

// Call stack frame
typedef struct {
    Variable locals[50];
    int local_count;
} Frame;

#endif // WORDLANG_TYPES_H

