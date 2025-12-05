/*
 * Wordlang - utils.h
 * Utility functions
 */

#ifndef WORDLANG_UTILS_H
#define WORDLANG_UTILS_H

#include "types.h"

// Error handling
void error(const char *msg);

// Path utilities
void get_directory(const char *filepath, char *dir);

// Token helpers
Token peek(void);
Token peek_at(int offset);
Token advance(void);
int expect(TokenType type);

// Variable/Function/Class management
Variable* find_var(const char *name);
Variable* create_var(const char *name);
Function* find_func(const char *name);
int find_class(const char *name);
int find_method(int class_idx, const char *method_name);

// String value helper
const char* get_string_val(const char *val, TokenType type);

// Operator helpers
int is_binop(TokenType t);
int is_comparison(TokenType t);

#endif // WORDLANG_UTILS_H

