/*
 * Wordlang - globals.h
 * Global state declarations
 */

#ifndef WORDLANG_GLOBALS_H
#define WORDLANG_GLOBALS_H

#include "types.h"

// Token array
extern Token tokens[MAX_TOKENS];
extern int token_count;
extern int current_token;

// Variables
extern Variable globals[MAX_VARS];
extern int global_count;

// Functions
extern Function functions[MAX_FUNCTIONS];
extern int function_count;

// Classes
extern Class classes[MAX_CLASSES];
extern int class_count;

// Call stack
extern Frame call_stack[MAX_CALL_DEPTH];
extern int call_depth;

// Control flags
extern int break_flag;
extern int continue_flag;
extern int return_flag;
extern int return_value;
extern char return_str[256];
extern int return_is_string;

// Import tracking
extern char imported_files[MAX_IMPORTS][MAX_PATH];
extern int import_count;

// Base path for finding libraries
extern char base_path[MAX_PATH];

#endif // WORDLANG_GLOBALS_H

