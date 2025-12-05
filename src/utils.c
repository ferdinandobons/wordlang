/*
 * Wordlang - utils.c
 * Utility functions implementation
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"
#include "globals.h"

void error(const char *msg) {
    fprintf(stderr, "Error: %s\n", msg);
    exit(1);
}

void get_directory(const char *filepath, char *dir) {
    strcpy(dir, filepath);
    char *last_slash = strrchr(dir, '/');
    if (last_slash) {
        *(last_slash + 1) = '\0';
    } else {
        dir[0] = '\0';
    }
}

Token peek(void) { 
    return tokens[current_token]; 
}

Token peek_at(int offset) { 
    int idx = current_token + offset;
    return (idx < token_count) ? tokens[idx] : tokens[token_count - 1]; 
}

Token advance(void) { 
    return tokens[current_token++]; 
}

int expect(TokenType type) {
    if (peek().type == type) { 
        advance(); 
        return 1; 
    }
    return 0;
}

Variable* find_var(const char *name) {
    if (call_depth > 0) {
        Frame *f = &call_stack[call_depth - 1];
        for (int i = 0; i < f->local_count; i++) {
            if (strcmp(f->locals[i].name, name) == 0) return &f->locals[i];
        }
    }
    for (int i = 0; i < global_count; i++) {
        if (strcmp(globals[i].name, name) == 0) return &globals[i];
    }
    return NULL;
}

Variable* create_var(const char *name) {
    Variable *v = find_var(name);
    if (v) return v;
    
    if (call_depth > 0) {
        Frame *f = &call_stack[call_depth - 1];
        if (f->local_count >= 50) error("Too many local variables");
        v = &f->locals[f->local_count++];
    } else {
        if (global_count >= MAX_VARS) error("Too many variables");
        v = &globals[global_count++];
    }
    
    strncpy(v->name, name, 63);
    v->name[63] = '\0';
    v->value = 0;
    v->is_string = 0;
    v->is_array = 0;
    v->array_length = 0;
    v->is_instance = 0;
    v->class_index = -1;
    return v;
}

Function* find_func(const char *name) {
    for (int i = 0; i < function_count; i++) {
        if (strcmp(functions[i].name, name) == 0) return &functions[i];
    }
    return NULL;
}

int find_class(const char *name) {
    for (int i = 0; i < class_count; i++) {
        if (strcmp(classes[i].name, name) == 0) return i;
    }
    return -1;
}

int find_method(int class_idx, const char *method_name) {
    if (class_idx < 0 || class_idx >= class_count) return -1;
    Class *cls = &classes[class_idx];
    for (int i = 0; i < cls->method_count; i++) {
        if (strcmp(cls->method_names[i], method_name) == 0) return i;
    }
    return -1;
}

// Static buffer for string values
static char _str_val_buf[256];

const char* get_string_val(const char *val, TokenType type) {
    if (type == TOK_STRING) {
        strncpy(_str_val_buf, val, 255);
        _str_val_buf[255] = '\0';
        return _str_val_buf;
    }
    Variable *v = find_var(val);
    if (v && v->is_string) return v->str_value;
    strncpy(_str_val_buf, val, 255);
    _str_val_buf[255] = '\0';
    return _str_val_buf;
}

int is_binop(TokenType t) {
    return t == TOK_PLUS || t == TOK_MINUS || t == TOK_STAR || 
           t == TOK_SLASH || t == TOK_PERCENT || t == TOK_CARET;
}

int is_comparison(TokenType t) {
    return t == TOK_EQ || t == TOK_NE || t == TOK_GT || 
           t == TOK_LT || t == TOK_GE || t == TOK_LE;
}

