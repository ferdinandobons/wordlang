/*
 * Wordlang - parser.h
 * Parser declarations
 */

#ifndef WORDLANG_PARSER_H
#define WORDLANG_PARSER_H

// Expression parsing
int parse_primary(void);
int parse_power(void);
int parse_term(void);
int parse_expr(void);
int parse_comparison(void);
int parse_cond(void);

// Statement parsing
void parse_print(void);
void parse_set(void);
void parse_if(void);
void parse_while(void);
void parse_for(void);
void parse_define(void);
void parse_return(void);
void parse_put(void);
void parse_append(void);
void parse_class(void);
void parse_sleep(void);
void parse_import(void);
void parse_stmt(void);

// Main parser
void parse_program(void);

#endif // WORDLANG_PARSER_H

