/*
 * Wordlang - main.c
 * Main entry point
 */

#include <stdio.h>
#include <stdlib.h>
#include "utils.h"
#include "tokenizer.h"
#include "parser.h"
#include "globals.h"

#define VERSION "2.3"

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Wordlang Interpreter v%s\n", VERSION);
        fprintf(stderr, "Usage: %s <source_file>\n", argv[0]);
        return 1;
    }
    
    // Set base path from input file
    get_directory(argv[1], base_path);
    
    FILE *f = fopen(argv[1], "r");
    if (!f) {
        fprintf(stderr, "Cannot open file: %s\n", argv[1]);
        return 1;
    }
    
    fseek(f, 0, SEEK_END);
    long size = ftell(f);
    fseek(f, 0, SEEK_SET);
    
    char *src = malloc(size + 1);
    if (!src) {
        fprintf(stderr, "Memory error\n");
        fclose(f);
        return 1;
    }
    
    fread(src, 1, size, f);
    src[size] = '\0';
    fclose(f);
    
    tokenize(src);
    parse_program();
    
    free(src);
    return 0;
}

