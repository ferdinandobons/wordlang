/*
 * Wordlang - tokenizer.c
 * Tokenization implementation
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "tokenizer.h"
#include "globals.h"

TokenType get_keyword_type(const char *word) {
    // Control flow
    if (strcmp(word, "set") == 0) return TOK_SET;
    if (strcmp(word, "to") == 0) return TOK_TO;
    if (strcmp(word, "if") == 0) return TOK_IF;
    if (strcmp(word, "then") == 0) return TOK_THEN;
    if (strcmp(word, "else") == 0) return TOK_ELSE;
    if (strcmp(word, "elseif") == 0 || strcmp(word, "elif") == 0) return TOK_ELSEIF;
    if (strcmp(word, "end") == 0) return TOK_END;
    if (strcmp(word, "while") == 0) return TOK_WHILE;
    if (strcmp(word, "do") == 0) return TOK_DO;
    if (strcmp(word, "print") == 0) return TOK_PRINT;
    if (strcmp(word, "for") == 0) return TOK_FOR;
    if (strcmp(word, "in") == 0) return TOK_IN;
    if (strcmp(word, "range") == 0) return TOK_RANGE;
    if (strcmp(word, "define") == 0) return TOK_DEFINE;
    if (strcmp(word, "with") == 0) return TOK_WITH;
    if (strcmp(word, "return") == 0) return TOK_RETURN;
    if (strcmp(word, "call") == 0) return TOK_CALL;
    if (strcmp(word, "class") == 0) return TOK_CLASS;
    if (strcmp(word, "method") == 0) return TOK_METHOD;
    if (strcmp(word, "new") == 0) return TOK_NEW;
    if (strcmp(word, "dot") == 0) return TOK_DOT;
    if (strcmp(word, "input") == 0) return TOK_INPUT;
    if (strcmp(word, "break") == 0) return TOK_BREAK;
    if (strcmp(word, "continue") == 0) return TOK_CONTINUE;
    if (strcmp(word, "import") == 0) return TOK_IMPORT;
    if (strcmp(word, "from") == 0) return TOK_FROM;
    if (strcmp(word, "use") == 0) return TOK_USE;
    
    // Logical
    if (strcmp(word, "and") == 0) return TOK_AND;
    if (strcmp(word, "or") == 0) return TOK_OR;
    if (strcmp(word, "not") == 0) return TOK_NOT;
    
    // Arithmetic (words)
    if (strcmp(word, "plus") == 0 || strcmp(word, "add") == 0) return TOK_PLUS;
    if (strcmp(word, "minus") == 0 || strcmp(word, "subtract") == 0) return TOK_MINUS;
    if (strcmp(word, "times") == 0 || strcmp(word, "multiply") == 0) return TOK_STAR;
    if (strcmp(word, "divideby") == 0 || strcmp(word, "divide") == 0) return TOK_SLASH;
    if (strcmp(word, "mod") == 0 || strcmp(word, "modulo") == 0) return TOK_PERCENT;
    if (strcmp(word, "power") == 0 || strcmp(word, "pow") == 0) return TOK_CARET;
    
    // Comparison (words)
    if (strcmp(word, "equals") == 0 || strcmp(word, "is") == 0) return TOK_EQ;
    if (strcmp(word, "greater") == 0) return TOK_GT;
    if (strcmp(word, "less") == 0) return TOK_LT;
    if (strcmp(word, "than") == 0) return TOK_THAN;
    
    // Arrays
    if (strcmp(word, "array") == 0 || strcmp(word, "list") == 0) return TOK_ARRAY;
    if (strcmp(word, "get") == 0) return TOK_GET;
    if (strcmp(word, "put") == 0) return TOK_PUT;
    if (strcmp(word, "length") == 0 || strcmp(word, "len") == 0) return TOK_LENGTH;
    if (strcmp(word, "append") == 0 || strcmp(word, "push") == 0) return TOK_APPEND;
    if (strcmp(word, "concat") == 0 || strcmp(word, "join") == 0) return TOK_CONCAT;
    
    // Boolean
    if (strcmp(word, "true") == 0 || strcmp(word, "yes") == 0) return TOK_TRUE;
    if (strcmp(word, "false") == 0 || strcmp(word, "no") == 0) return TOK_FALSE;
    
    // Math library
    if (strcmp(word, "abs") == 0) return TOK_ABS;
    if (strcmp(word, "min") == 0) return TOK_MIN;
    if (strcmp(word, "max") == 0) return TOK_MAX;
    if (strcmp(word, "sqrt") == 0) return TOK_SQRT;
    if (strcmp(word, "sign") == 0) return TOK_SIGN;
    if (strcmp(word, "random") == 0 || strcmp(word, "rand") == 0) return TOK_RANDOM;
    if (strcmp(word, "randint") == 0) return TOK_RANDINT;
    if (strcmp(word, "randrange") == 0) return TOK_RANDRANGE;
    if (strcmp(word, "gcd") == 0) return TOK_GCD;
    if (strcmp(word, "lcm") == 0) return TOK_LCM;
    if (strcmp(word, "factorial") == 0 || strcmp(word, "fact") == 0) return TOK_FACTORIAL;
    if (strcmp(word, "clamp") == 0) return TOK_CLAMP;
    if (strcmp(word, "iseven") == 0 || strcmp(word, "even") == 0) return TOK_ISEVEN;
    if (strcmp(word, "isodd") == 0 || strcmp(word, "odd") == 0) return TOK_ISODD;
    
    // Time library
    if (strcmp(word, "now") == 0 || strcmp(word, "timestamp") == 0) return TOK_NOW;
    if (strcmp(word, "hour") == 0) return TOK_HOUR;
    if (strcmp(word, "minute") == 0) return TOK_MINUTE;
    if (strcmp(word, "second") == 0) return TOK_SECOND;
    if (strcmp(word, "day") == 0) return TOK_DAY;
    if (strcmp(word, "month") == 0) return TOK_MONTH;
    if (strcmp(word, "year") == 0) return TOK_YEAR;
    if (strcmp(word, "weekday") == 0) return TOK_WEEKDAY;
    if (strcmp(word, "yearday") == 0) return TOK_YEARDAY;
    if (strcmp(word, "time") == 0) return TOK_TIME;
    if (strcmp(word, "date") == 0) return TOK_DATE;
    if (strcmp(word, "datetime") == 0) return TOK_DATETIME;
    if (strcmp(word, "sleep") == 0) return TOK_SLEEP;
    
    // String library
    if (strcmp(word, "upper") == 0 || strcmp(word, "uppercase") == 0) return TOK_UPPER;
    if (strcmp(word, "lower") == 0 || strcmp(word, "lowercase") == 0) return TOK_LOWER;
    if (strcmp(word, "trim") == 0 || strcmp(word, "strip") == 0) return TOK_TRIM;
    if (strcmp(word, "reverse") == 0) return TOK_REVERSE;
    if (strcmp(word, "repeat") == 0) return TOK_REPEAT;
    if (strcmp(word, "startswith") == 0) return TOK_STARTSWITH;
    if (strcmp(word, "endswith") == 0) return TOK_ENDSWITH;
    if (strcmp(word, "contains") == 0) return TOK_CONTAINS;
    if (strcmp(word, "indexof") == 0 || strcmp(word, "find") == 0) return TOK_INDEXOF;
    if (strcmp(word, "charat") == 0) return TOK_CHARAT;
    if (strcmp(word, "replace") == 0) return TOK_REPLACE;
    if (strcmp(word, "isnumeric") == 0 || strcmp(word, "isdigit") == 0) return TOK_ISNUMERIC;
    if (strcmp(word, "isalpha") == 0 || strcmp(word, "isletter") == 0) return TOK_ISALPHA;
    
    return TOK_IDENTIFIER;
}

void add_token(TokenType type, const char *value) {
    if (token_count < MAX_TOKENS - 1) {
        tokens[token_count].type = type;
        strncpy(tokens[token_count].value, value, MAX_TOKEN_LEN - 1);
        tokens[token_count].value[MAX_TOKEN_LEN - 1] = '\0';
        token_count++;
    }
}

void tokenize(const char *source) {
    token_count = 0;
    tokenize_append(source);
    tokens[token_count].type = TOK_EOF;
    strcpy(tokens[token_count].value, "");
    token_count++;
}

void tokenize_append(const char *source) {
    int i = 0;
    
    // Remove EOF if present (for appending)
    if (token_count > 0 && tokens[token_count - 1].type == TOK_EOF) {
        token_count--;
    }
    
    while (source[i] != '\0' && token_count < MAX_TOKENS - 1) {
        while (isspace(source[i])) i++;
        if (source[i] == '\0') break;
        
        // Skip # comments
        if (source[i] == '#') {
            while (source[i] != '\0' && source[i] != '\n') i++;
            continue;
        }
        
        // Two-character operators
        if (source[i] == '=' && source[i+1] == '=') { add_token(TOK_EQ, "=="); i += 2; continue; }
        if (source[i] == '!' && source[i+1] == '=') { add_token(TOK_NE, "!="); i += 2; continue; }
        if (source[i] == '>' && source[i+1] == '=') { add_token(TOK_GE, ">="); i += 2; continue; }
        if (source[i] == '<' && source[i+1] == '=') { add_token(TOK_LE, "<="); i += 2; continue; }
        if (source[i] == '&' && source[i+1] == '&') { add_token(TOK_AND, "&&"); i += 2; continue; }
        if (source[i] == '|' && source[i+1] == '|') { add_token(TOK_OR, "||"); i += 2; continue; }
        if (source[i] == '*' && source[i+1] == '*') { add_token(TOK_CARET, "**"); i += 2; continue; }
        
        // Single-character operators
        switch (source[i]) {
            case '+': add_token(TOK_PLUS, "+"); i++; continue;
            case '-':
                if (isdigit(source[i+1])) {
                    char word[MAX_TOKEN_LEN];
                    int j = 0;
                    word[j++] = source[i++];
                    while (isdigit(source[i]) && j < MAX_TOKEN_LEN - 1) word[j++] = source[i++];
                    word[j] = '\0';
                    add_token(TOK_NUMBER, word);
                } else {
                    add_token(TOK_MINUS, "-"); i++;
                }
                continue;
            case '*': add_token(TOK_STAR, "*"); i++; continue;
            case '/': add_token(TOK_SLASH, "/"); i++; continue;
            case '%': add_token(TOK_PERCENT, "%"); i++; continue;
            case '^': add_token(TOK_CARET, "^"); i++; continue;
            case '>': add_token(TOK_GT, ">"); i++; continue;
            case '<': add_token(TOK_LT, "<"); i++; continue;
            case '=': add_token(TOK_EQ, "="); i++; continue;
            case '!': add_token(TOK_NOT, "!"); i++; continue;
            case '(': add_token(TOK_LPAREN, "("); i++; continue;
            case ')': add_token(TOK_RPAREN, ")"); i++; continue;
        }
        
        char word[MAX_TOKEN_LEN];
        int j = 0;
        
        if (isdigit(source[i])) {
            while (isdigit(source[i]) && j < MAX_TOKEN_LEN - 1) word[j++] = source[i++];
            word[j] = '\0';
            add_token(TOK_NUMBER, word);
        }
        else if (source[i] == '"') {
            i++;
            while (source[i] != '"' && source[i] != '\0' && j < MAX_TOKEN_LEN - 1) word[j++] = source[i++];
            if (source[i] == '"') i++;
            word[j] = '\0';
            add_token(TOK_STRING, word);
        }
        else if (isalpha(source[i]) || source[i] == '_') {
            while ((isalnum(source[i]) || source[i] == '_') && j < MAX_TOKEN_LEN - 1) word[j++] = source[i++];
            word[j] = '\0';
            add_token(get_keyword_type(word), word);
        }
        else {
            i++;
        }
    }
}

