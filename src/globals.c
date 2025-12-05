/*
 * Wordlang - globals.c
 * Global state definitions
 */

#include "globals.h"

// Token array
Token tokens[MAX_TOKENS];
int token_count = 0;
int current_token = 0;

// Variables
Variable globals[MAX_VARS];
int global_count = 0;

// Functions
Function functions[MAX_FUNCTIONS];
int function_count = 0;

// Classes
Class classes[MAX_CLASSES];
int class_count = 0;

// Call stack
Frame call_stack[MAX_CALL_DEPTH];
int call_depth = 0;

// Control flags
int break_flag = 0;
int continue_flag = 0;
int return_flag = 0;
int return_value = 0;
char return_str[256];
int return_is_string = 0;

// Import tracking
char imported_files[MAX_IMPORTS][MAX_PATH];
int import_count = 0;

// Base path for finding libraries
char base_path[MAX_PATH] = "";

