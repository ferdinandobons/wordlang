/*
 * Wordlang - tokenizer.h
 * Tokenization declarations
 */

#ifndef WORDLANG_TOKENIZER_H
#define WORDLANG_TOKENIZER_H

#include "types.h"

// Get keyword type from word
TokenType get_keyword_type(const char *word);

// Add a token to the token array
void add_token(TokenType type, const char *value);

// Tokenize source code (resets token array)
void tokenize(const char *source);

// Tokenize and append to existing tokens
void tokenize_append(const char *source);

#endif // WORDLANG_TOKENIZER_H

