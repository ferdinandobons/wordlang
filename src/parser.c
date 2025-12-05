/*
 * Wordlang - parser.c
 * Parser implementation
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parser.h"
#include "types.h"
#include "globals.h"
#include "utils.h"
#include "tokenizer.h"
#include "../lib/core/core.h"

// ============================================================
// Expression Parsing
// ============================================================

int parse_primary(void) {
    Token t = peek();
    
    // Parentheses
    if (t.type == TOK_LPAREN) {
        advance();
        int val = parse_expr();
        expect(TOK_RPAREN);
        return val;
    }
    
    // NOT operator
    if (t.type == TOK_NOT) {
        advance();
        return !parse_primary();
    }
    
    // Prefix arithmetic operators
    if (t.type == TOK_PLUS) {
        advance();
        int left = parse_primary();
        if (is_binop(peek().type) || is_comparison(peek().type) || 
            peek().type == TOK_THEN || peek().type == TOK_DO ||
            peek().type == TOK_END || peek().type == TOK_EOF ||
            peek().type == TOK_AND || peek().type == TOK_OR) {
            return left;
        }
        return left + parse_primary();
    }
    if (t.type == TOK_MINUS) {
        advance();
        int left = parse_primary();
        if (is_binop(peek().type) || is_comparison(peek().type) ||
            peek().type == TOK_THEN || peek().type == TOK_DO ||
            peek().type == TOK_END || peek().type == TOK_EOF ||
            peek().type == TOK_AND || peek().type == TOK_OR) {
            return -left;
        }
        return left - parse_primary();
    }
    if (t.type == TOK_STAR) { advance(); return parse_primary() * parse_primary(); }
    if (t.type == TOK_SLASH) { 
        advance(); 
        int l = parse_primary(), r = parse_primary();
        if (r == 0) error("Division by zero");
        return l / r;
    }
    if (t.type == TOK_PERCENT) {
        advance();
        int l = parse_primary(), r = parse_primary();
        if (r == 0) error("Modulo by zero");
        return l % r;
    }
    if (t.type == TOK_CARET) {
        advance();
        int base = parse_primary(), exp = parse_primary();
        int result = 1;
        for (int i = 0; i < exp; i++) result *= base;
        return result;
    }
    
    // Boolean literals
    if (t.type == TOK_TRUE) { advance(); return 1; }
    if (t.type == TOK_FALSE) { advance(); return 0; }
    
    // === MATH LIBRARY ===
    if (t.type == TOK_ABS) { advance(); return wl_abs(parse_primary()); }
    if (t.type == TOK_SQRT) { advance(); return wl_sqrt(parse_primary()); }
    if (t.type == TOK_SIGN) { advance(); return wl_sign(parse_primary()); }
    if (t.type == TOK_RANDOM) { advance(); return wl_random(); }
    if (t.type == TOK_RANDINT) { advance(); return wl_randint(parse_primary()); }
    if (t.type == TOK_FACTORIAL) { advance(); return wl_factorial(parse_primary()); }
    if (t.type == TOK_ISEVEN) { advance(); return wl_is_even(parse_primary()); }
    if (t.type == TOK_ISODD) { advance(); return wl_is_odd(parse_primary()); }
    if (t.type == TOK_MIN) { advance(); return wl_min(parse_primary(), parse_primary()); }
    if (t.type == TOK_MAX) { advance(); return wl_max(parse_primary(), parse_primary()); }
    if (t.type == TOK_GCD) { advance(); return wl_gcd(parse_primary(), parse_primary()); }
    if (t.type == TOK_LCM) { advance(); return wl_lcm(parse_primary(), parse_primary()); }
    if (t.type == TOK_RANDRANGE) { advance(); return wl_randrange(parse_primary(), parse_primary()); }
    if (t.type == TOK_CLAMP) { advance(); return wl_clamp(parse_primary(), parse_primary(), parse_primary()); }
    
    // === TIME LIBRARY ===
    if (t.type == TOK_NOW) { advance(); return wl_now(); }
    if (t.type == TOK_HOUR) { advance(); return wl_hour(); }
    if (t.type == TOK_MINUTE) { advance(); return wl_minute(); }
    if (t.type == TOK_SECOND) { advance(); return wl_second(); }
    if (t.type == TOK_DAY) { advance(); return wl_day(); }
    if (t.type == TOK_MONTH) { advance(); return wl_month(); }
    if (t.type == TOK_YEAR) { advance(); return wl_year(); }
    if (t.type == TOK_WEEKDAY) { advance(); return wl_weekday(); }
    if (t.type == TOK_YEARDAY) { advance(); return wl_yearday(); }
    
    // === STRING LIBRARY (int results) ===
    if (t.type == TOK_CHARAT) {
        advance();
        Token s = advance();
        return wl_charat(get_string_val(s.value, s.type), parse_primary());
    }
    if (t.type == TOK_INDEXOF) {
        advance();
        Token s = advance();
        const char *str = get_string_val(s.value, s.type);
        char str_copy[256]; strncpy(str_copy, str, 255); str_copy[255] = '\0';
        Token sub = advance();
        return wl_indexof(str_copy, get_string_val(sub.value, sub.type));
    }
    if (t.type == TOK_CONTAINS) {
        advance();
        Token s = advance();
        const char *str = get_string_val(s.value, s.type);
        char str_copy[256]; strncpy(str_copy, str, 255); str_copy[255] = '\0';
        Token sub = advance();
        return wl_contains(str_copy, get_string_val(sub.value, sub.type));
    }
    if (t.type == TOK_STARTSWITH) {
        advance();
        Token s = advance();
        const char *str = get_string_val(s.value, s.type);
        char str_copy[256]; strncpy(str_copy, str, 255); str_copy[255] = '\0';
        Token prefix = advance();
        return wl_startswith(str_copy, get_string_val(prefix.value, prefix.type));
    }
    if (t.type == TOK_ENDSWITH) {
        advance();
        Token s = advance();
        const char *str = get_string_val(s.value, s.type);
        char str_copy[256]; strncpy(str_copy, str, 255); str_copy[255] = '\0';
        Token suffix = advance();
        return wl_endswith(str_copy, get_string_val(suffix.value, suffix.type));
    }
    if (t.type == TOK_ISNUMERIC) {
        advance();
        Token s = advance();
        return wl_is_numeric(get_string_val(s.value, s.type));
    }
    if (t.type == TOK_ISALPHA) {
        advance();
        Token s = advance();
        return wl_is_alpha(get_string_val(s.value, s.type));
    }
    
    // Array length
    if (t.type == TOK_LENGTH) {
        advance();
        Token arr = advance();
        Variable *v = find_var(arr.value);
        if (!v) error("Undefined variable for length");
        if (v->is_string) return strlen(v->str_value);
        return v->array_length;
    }
    
    // Array get
    if (t.type == TOK_GET) {
        advance();
        Token arr = advance();
        int idx = parse_primary();
        Variable *v = find_var(arr.value);
        if (!v || !v->is_array) error("Invalid array access");
        if (idx < 0 || idx >= v->array_length) error("Index out of bounds");
        return v->array_values[idx];
    }
    
    // Function call
    if (t.type == TOK_CALL) {
        advance();
        Token fname = advance();
        Function *fn = find_func(fname.value);
        if (!fn) error("Undefined function");
        
        int args[MAX_PARAMS];
        int argc = 0;
        while (argc < fn->param_count) {
            Token next = peek();
            if (next.type == TOK_EOF || next.type == TOK_THEN || 
                next.type == TOK_DO || next.type == TOK_END ||
                next.type == TOK_ELSE || next.type == TOK_SET ||
                next.type == TOK_PRINT || next.type == TOK_IF ||
                next.type == TOK_WHILE || next.type == TOK_FOR ||
                next.type == TOK_RETURN || next.type == TOK_BREAK ||
                next.type == TOK_CONTINUE || is_comparison(next.type) ||
                next.type == TOK_AND || next.type == TOK_OR) break;
            args[argc++] = parse_expr();
        }
        
        if (call_depth >= MAX_CALL_DEPTH) error("Stack overflow");
        call_stack[call_depth].local_count = 0;
        call_depth++;
        
        for (int i = 0; i < fn->param_count && i < argc; i++) {
            Variable *p = create_var(fn->params[i]);
            p->value = args[i];
        }
        
        int saved = current_token;
        current_token = fn->body_start;
        return_flag = 0;
        
        while (current_token < fn->body_end && !return_flag) {
            parse_stmt();
        }
        
        int result = return_value;
        return_flag = 0;
        call_depth--;
        current_token = saved;
        
        return result;
    }
    
    // Number
    if (t.type == TOK_NUMBER) {
        advance();
        return atoi(t.value);
    }
    
    // Variable or method call (instance > method)
    if (t.type == TOK_IDENTIFIER) {
        advance();
        Variable *v = find_var(t.value);
        if (!v) {
            char msg[128];
            snprintf(msg, 128, "Undefined variable: %s", t.value);
            error(msg);
        }
        
        // Check for method call: instance > method args...
        if (v->is_instance && peek().type == TOK_GT) {
            advance();  // Skip >
            Token method_tok = advance();  // Get method name
            
            int class_idx = v->class_index;
            int method_idx = find_method(class_idx, method_tok.value);
            if (method_idx < 0) {
                char msg[128];
                snprintf(msg, 128, "Undefined method: %s", method_tok.value);
                error(msg);
            }
            
            Class *cls = &classes[class_idx];
            
            // Collect arguments
            int args[MAX_PARAMS];
            int argc = 0;
            int param_count = cls->method_param_counts[method_idx];
            while (argc < param_count) {
                Token next = peek();
                if (next.type == TOK_EOF || next.type == TOK_THEN || 
                    next.type == TOK_DO || next.type == TOK_END ||
                    next.type == TOK_ELSE || next.type == TOK_SET ||
                    next.type == TOK_PRINT || next.type == TOK_IF ||
                    next.type == TOK_WHILE || next.type == TOK_FOR ||
                    next.type == TOK_RETURN || next.type == TOK_BREAK ||
                    next.type == TOK_CONTINUE || is_comparison(next.type) ||
                    next.type == TOK_AND || next.type == TOK_OR) break;
                args[argc++] = parse_expr();
            }
            
            // Execute method
            if (call_depth >= MAX_CALL_DEPTH) error("Stack overflow");
            call_stack[call_depth].local_count = 0;
            call_depth++;
            
            // Set up parameters with their proper names
            int saved = current_token;
            for (int i = 0; i < cls->method_param_counts[method_idx] && i < argc; i++) {
                Variable *p = create_var(cls->method_params[method_idx][i]);
                p->value = args[i];
            }
            
            current_token = cls->method_starts[method_idx];
            return_flag = 0;
            
            while (current_token < cls->method_ends[method_idx] && !return_flag) {
                parse_stmt();
            }
            
            int result = return_value;
            return_flag = 0;
            call_depth--;
            current_token = saved;
            
            return result;
        }
        
        return v->value;
    }
    
    error("Expected value");
    return 0;
}

int parse_power(void) {
    int left = parse_primary();
    while (peek().type == TOK_CARET) {
        advance();
        int right = parse_power();
        int result = 1;
        for (int i = 0; i < right; i++) result *= left;
        left = result;
    }
    return left;
}

int parse_term(void) {
    int left = parse_power();
    while (peek().type == TOK_STAR || peek().type == TOK_SLASH || peek().type == TOK_PERCENT) {
        TokenType op = advance().type;
        int right = parse_power();
        if (op == TOK_STAR) left *= right;
        else if (op == TOK_SLASH) { if (right == 0) error("Division by zero"); left /= right; }
        else left %= right;
    }
    return left;
}

int parse_expr(void) {
    int left = parse_term();
    while (peek().type == TOK_PLUS || peek().type == TOK_MINUS) {
        TokenType op = advance().type;
        int right = parse_term();
        if (op == TOK_PLUS) left += right; else left -= right;
    }
    return left;
}

int parse_comparison(void) {
    int left = parse_expr();
    Token t = peek();
    
    if (t.type == TOK_EQ) { advance(); return left == parse_expr(); }
    if (t.type == TOK_NE) { advance(); return left != parse_expr(); }
    if (t.type == TOK_GT) {
        advance();
        if (peek().type == TOK_THAN) advance();
        if (peek().type == TOK_EQ) { advance(); return left >= parse_expr(); }
        return left > parse_expr();
    }
    if (t.type == TOK_LT) {
        advance();
        if (peek().type == TOK_THAN) advance();
        if (peek().type == TOK_EQ) { advance(); return left <= parse_expr(); }
        return left < parse_expr();
    }
    if (t.type == TOK_GE) { advance(); return left >= parse_expr(); }
    if (t.type == TOK_LE) { advance(); return left <= parse_expr(); }
    if (t.type == TOK_NOT && peek_at(1).type == TOK_EQ) { advance(); advance(); return left != parse_expr(); }
    
    return left;
}

int parse_cond(void) {
    int left = parse_comparison();
    while (peek().type == TOK_AND || peek().type == TOK_OR) {
        TokenType op = advance().type;
        int right = parse_comparison();
        if (op == TOK_AND) left = left && right; else left = left || right;
    }
    return left;
}

// ============================================================
// Statement Parsing
// ============================================================

void parse_print(void) {
    expect(TOK_PRINT);
    Token t = peek();
    
    if (t.type == TOK_STRING) { advance(); printf("%s\n", t.value); return; }
    if (t.type == TOK_TRUE) { advance(); printf("true\n"); return; }
    if (t.type == TOK_FALSE) { advance(); printf("false\n"); return; }
    
    // Time strings
    if (t.type == TOK_TIME) { advance(); printf("%s\n", wl_time_str()); return; }
    if (t.type == TOK_DATE) { advance(); printf("%s\n", wl_date_str()); return; }
    if (t.type == TOK_DATETIME) { advance(); printf("%s\n", wl_datetime_str()); return; }
    
    // String library (print string results)
    if (t.type == TOK_UPPER) { advance(); Token s = advance(); printf("%s\n", wl_upper(get_string_val(s.value, s.type))); return; }
    if (t.type == TOK_LOWER) { advance(); Token s = advance(); printf("%s\n", wl_lower(get_string_val(s.value, s.type))); return; }
    if (t.type == TOK_TRIM) { advance(); Token s = advance(); printf("%s\n", wl_trim(get_string_val(s.value, s.type))); return; }
    if (t.type == TOK_REVERSE) { advance(); Token s = advance(); printf("%s\n", wl_reverse(get_string_val(s.value, s.type))); return; }
    if (t.type == TOK_REPEAT) {
        advance();
        Token s = advance();
        int n = parse_primary();
        printf("%s\n", wl_repeat(get_string_val(s.value, s.type), n));
        return;
    }
    if (t.type == TOK_REPLACE) {
        advance();
        Token s = advance();
        const char *str = get_string_val(s.value, s.type);
        char str_copy[256]; strncpy(str_copy, str, 255); str_copy[255] = '\0';
        Token old_tok = advance();
        const char *old_str = get_string_val(old_tok.value, old_tok.type);
        char old_copy[256]; strncpy(old_copy, old_str, 255); old_copy[255] = '\0';
        Token new_tok = advance();
        printf("%s\n", wl_replace(str_copy, old_copy, get_string_val(new_tok.value, new_tok.type)));
        return;
    }
    
    // Variable
    if (t.type == TOK_IDENTIFIER) {
        Variable *v = find_var(t.value);
        if (v) {
            TokenType next = peek_at(1).type;
            if (next == TOK_EOF || next == TOK_SET || next == TOK_PRINT ||
                next == TOK_IF || next == TOK_WHILE || next == TOK_END ||
                next == TOK_ELSE || next == TOK_FOR || next == TOK_DEFINE ||
                next == TOK_RETURN || next == TOK_BREAK || next == TOK_CONTINUE ||
                next == TOK_IMPORT) {
                advance();
                if (v->is_string) printf("%s\n", v->str_value);
                else if (v->is_array) {
                    printf("[");
                    for (int i = 0; i < v->array_length; i++) {
                        printf("%d", v->array_values[i]);
                        if (i < v->array_length - 1) printf(", ");
                    }
                    printf("]\n");
                } else printf("%d\n", v->value);
                return;
            }
        }
    }
    
    printf("%d\n", parse_expr());
}

void parse_set(void) {
    expect(TOK_SET);
    Token var = advance();
    expect(TOK_TO);
    
    Variable *v = create_var(var.value);
    Token t = peek();
    
    // New instance: set x to new ClassName
    if (t.type == TOK_NEW) {
        advance();
        Token class_name = advance();
        int class_idx = find_class(class_name.value);
        if (class_idx < 0) {
            char msg[128];
            snprintf(msg, 128, "Undefined class: %s", class_name.value);
            error(msg);
        }
        v->is_instance = 1;
        v->class_index = class_idx;
        v->is_string = 0;
        v->is_array = 0;
        v->value = class_idx;  // Store class index as value
        return;
    }
    
    // Input
    if (t.type == TOK_INPUT) {
        advance();
        char buf[256];
        if (fgets(buf, 256, stdin)) {
            buf[strcspn(buf, "\n")] = 0;
            char *end;
            long num = strtol(buf, &end, 10);
            if (*end == '\0') { v->value = (int)num; v->is_string = 0; }
            else { v->is_string = 1; strncpy(v->str_value, buf, 255); }
        }
        v->is_array = 0;
        return;
    }
    
    // Time strings
    if (t.type == TOK_TIME) { advance(); v->is_string = 1; v->is_array = 0; strncpy(v->str_value, wl_time_str(), 255); return; }
    if (t.type == TOK_DATE) { advance(); v->is_string = 1; v->is_array = 0; strncpy(v->str_value, wl_date_str(), 255); return; }
    if (t.type == TOK_DATETIME) { advance(); v->is_string = 1; v->is_array = 0; strncpy(v->str_value, wl_datetime_str(), 255); return; }
    
    // String operations that return strings
    if (t.type == TOK_UPPER) { advance(); Token s = advance(); v->is_string = 1; v->is_array = 0; strncpy(v->str_value, wl_upper(get_string_val(s.value, s.type)), 255); return; }
    if (t.type == TOK_LOWER) { advance(); Token s = advance(); v->is_string = 1; v->is_array = 0; strncpy(v->str_value, wl_lower(get_string_val(s.value, s.type)), 255); return; }
    if (t.type == TOK_TRIM) { advance(); Token s = advance(); v->is_string = 1; v->is_array = 0; strncpy(v->str_value, wl_trim(get_string_val(s.value, s.type)), 255); return; }
    if (t.type == TOK_REVERSE) { advance(); Token s = advance(); v->is_string = 1; v->is_array = 0; strncpy(v->str_value, wl_reverse(get_string_val(s.value, s.type)), 255); return; }
    if (t.type == TOK_REPEAT) {
        advance();
        Token s = advance();
        int n = parse_primary();
        v->is_string = 1; v->is_array = 0;
        strncpy(v->str_value, wl_repeat(get_string_val(s.value, s.type), n), 255);
        return;
    }
    if (t.type == TOK_REPLACE) {
        advance();
        Token s = advance();
        const char *str = get_string_val(s.value, s.type);
        char str_copy[256]; strncpy(str_copy, str, 255); str_copy[255] = '\0';
        Token old_tok = advance();
        const char *old_str = get_string_val(old_tok.value, old_tok.type);
        char old_copy[256]; strncpy(old_copy, old_str, 255); old_copy[255] = '\0';
        Token new_tok = advance();
        v->is_string = 1; v->is_array = 0;
        strncpy(v->str_value, wl_replace(str_copy, old_copy, get_string_val(new_tok.value, new_tok.type)), 255);
        return;
    }
    
    // Array
    if (t.type == TOK_ARRAY) {
        advance();
        v->is_array = 1; v->is_string = 0; v->array_length = 0;
        while (peek().type == TOK_NUMBER || (peek().type == TOK_IDENTIFIER && find_var(peek().value))) {
            if (v->array_length >= MAX_ARRAY_SIZE) break;
            if (peek().type == TOK_NUMBER) v->array_values[v->array_length++] = atoi(advance().value);
            else { Variable *src = find_var(advance().value); v->array_values[v->array_length++] = src->value; }
        }
        return;
    }
    
    // Concat
    if (t.type == TOK_CONCAT) {
        advance();
        char result[256] = "";
        while (peek().type == TOK_STRING || peek().type == TOK_IDENTIFIER || peek().type == TOK_NUMBER) {
            Token part = advance();
            if (part.type == TOK_STRING) strncat(result, part.value, 255 - strlen(result));
            else if (part.type == TOK_NUMBER) {
                char tmp[32]; snprintf(tmp, 32, "%d", atoi(part.value));
                strncat(result, tmp, 255 - strlen(result));
            } else {
                Variable *src = find_var(part.value);
                if (src && src->is_string) strncat(result, src->str_value, 255 - strlen(result));
                else if (src) { char tmp[32]; snprintf(tmp, 32, "%d", src->value); strncat(result, tmp, 255 - strlen(result)); }
            }
        }
        v->is_string = 1; v->is_array = 0; strcpy(v->str_value, result);
        return;
    }
    
    // String literal
    if (t.type == TOK_STRING) { advance(); v->is_string = 1; v->is_array = 0; strncpy(v->str_value, t.value, 255); return; }
    
    // Plain identifier as string
    if (t.type == TOK_IDENTIFIER && !find_var(t.value)) {
        TokenType next = peek_at(1).type;
        if (next == TOK_EOF || next == TOK_SET || next == TOK_PRINT ||
            next == TOK_IF || next == TOK_WHILE || next == TOK_END ||
            next == TOK_ELSE || next == TOK_FOR || next == TOK_DEFINE ||
            next == TOK_RETURN || next == TOK_BREAK || next == TOK_CONTINUE ||
            next == TOK_IMPORT) {
            advance();
            v->is_string = 1; v->is_array = 0; strncpy(v->str_value, t.value, 255);
            return;
        }
    }
    
    // Expression
    v->value = parse_expr();
    v->is_string = 0; v->is_array = 0;
}

/*
 * parse_if - Clean implementation using ELSEIF keyword
 * 
 * Syntax:
 *   if COND then BODY end
 *   if COND then BODY else BODY end
 *   if COND then BODY elseif COND then BODY else BODY end
 *
 * Note: "else" followed by "if" is treated as NESTED if (needs two ENDs)
 *       "elseif" is a single construct (one END for whole chain)
 */
void parse_if(void) {
    expect(TOK_IF);
    
    // Loop handles if/elseif chain
    while (1) {
        int cond = parse_cond();
        expect(TOK_THEN);
        
        int body_start = current_token;
        
        // Scan to find: ELSEIF, ELSE, or END at depth 1
        int depth = 1;
        int branch_pos = -1;    // Position of ELSEIF or ELSE
        TokenType branch_type = TOK_EOF;
        
        while (depth > 0 && peek().type != TOK_EOF) {
            TokenType t = peek().type;
            
            if (t == TOK_IF || t == TOK_WHILE || t == TOK_FOR || t == TOK_DEFINE) {
                depth++;
            } else if (t == TOK_END) {
                depth--;
                if (depth == 0) break;
            } else if (depth == 1 && (t == TOK_ELSEIF || t == TOK_ELSE)) {
                branch_pos = current_token;
                branch_type = t;
                break;
            }
            advance();
        }
        
        int end_pos = current_token;  // At END or branch
        
        if (cond) {
            // Execute this branch's body
            current_token = body_start;
            while (current_token < end_pos) {
                if (break_flag || continue_flag || return_flag) break;
                parse_stmt();
            }
            
            // Skip to final END (skip all remaining elseif/else)
            depth = 1;
            while (depth > 0 && peek().type != TOK_EOF) {
                TokenType t = peek().type;
                if (t == TOK_IF || t == TOK_WHILE || t == TOK_FOR || t == TOK_DEFINE) depth++;
                else if (t == TOK_END) depth--;
                advance();
            }
            return;
        }
        
        // Condition false - check for elseif/else
        if (branch_type == TOK_ELSEIF) {
            // Continue chain
            current_token = branch_pos + 1;  // Skip ELSEIF, loop will parse condition
            continue;
        } else if (branch_type == TOK_ELSE) {
            // Execute else body
            current_token = branch_pos + 1;  // Skip ELSE
            
            // Find END
            depth = 1;
            int else_end = current_token;
            while (depth > 0 && tokens[else_end].type != TOK_EOF) {
                TokenType t = tokens[else_end].type;
                if (t == TOK_IF || t == TOK_WHILE || t == TOK_FOR || t == TOK_DEFINE) depth++;
                else if (t == TOK_END) depth--;
                else_end++;
            }
            
            // Execute else body
            while (current_token < else_end - 1) {
                if (break_flag || continue_flag || return_flag) break;
                parse_stmt();
            }
            current_token = else_end;
            return;
        } else {
            // No else/elseif - skip END
            advance();
            return;
        }
    }
}

void parse_while(void) {
    expect(TOK_WHILE);
    int cond_start = current_token;
    parse_cond();
    expect(TOK_DO);
    
    int body_start = current_token, depth = 1;
    while (depth > 0 && peek().type != TOK_EOF) {
        if (peek().type == TOK_WHILE || peek().type == TOK_FOR || peek().type == TOK_IF) depth++;
        if (peek().type == TOK_END) depth--;
        advance();
    }
    int end = current_token;
    
    while (1) {
        current_token = cond_start;
        if (!parse_cond()) break;
        expect(TOK_DO);
        current_token = body_start;
        while (current_token < end - 1) {
            if (break_flag || return_flag) break;
            if (continue_flag) { continue_flag = 0; break; }
            parse_stmt();
        }
        if (break_flag) { break_flag = 0; break; }
        if (return_flag) break;
    }
    current_token = end;
}

void parse_for(void) {
    expect(TOK_FOR);
    Token var = advance();
    expect(TOK_IN);
    expect(TOK_RANGE);
    
    int start_val = parse_primary(), end_val = parse_primary(), step = 1;
    Token next = peek();
    if (next.type == TOK_NUMBER || (next.type == TOK_IDENTIFIER && find_var(next.value)) || next.type == TOK_MINUS)
        step = parse_primary();
    expect(TOK_DO);
    
    int body_start = current_token, depth = 1;
    while (depth > 0 && peek().type != TOK_EOF) {
        if (peek().type == TOK_WHILE || peek().type == TOK_FOR || peek().type == TOK_IF) depth++;
        if (peek().type == TOK_END) depth--;
        advance();
    }
    int end = current_token;
    
    Variable *loop_var = create_var(var.value);
    for (int i = start_val; (step > 0 ? i < end_val : i > end_val); i += step) {
        loop_var->value = i; loop_var->is_string = 0;
        current_token = body_start;
        while (current_token < end - 1) {
            if (break_flag || return_flag) break;
            if (continue_flag) { continue_flag = 0; break; }
            parse_stmt();
        }
        if (break_flag) { break_flag = 0; break; }
        if (return_flag) break;
    }
    current_token = end;
}

void parse_define(void) {
    expect(TOK_DEFINE);
    Token name = advance();
    if (function_count >= MAX_FUNCTIONS) error("Too many functions");
    
    Function *fn = &functions[function_count++];
    strncpy(fn->name, name.value, 63);
    fn->param_count = 0;
    
    if (peek().type == TOK_WITH) {
        advance();
        while (peek().type == TOK_IDENTIFIER) strncpy(fn->params[fn->param_count++], advance().value, 63);
    }
    expect(TOK_DO);
    fn->body_start = current_token;
    
    // Scan to find function end
    // IF/WHILE/FOR/DEFINE increase depth, END decreases
    // ELSEIF doesn't change depth (it's part of if chain)
    int depth = 1;
    while (depth > 0 && peek().type != TOK_EOF) {
        TokenType curr = peek().type;
        if (curr == TOK_IF || curr == TOK_WHILE || curr == TOK_FOR || curr == TOK_DEFINE) {
            depth++;
        } else if (curr == TOK_END) {
            depth--;
        }
        // ELSEIF doesn't change depth - it's part of the if block
        advance();
    }
    fn->body_end = current_token - 1;
}

void parse_return(void) {
    expect(TOK_RETURN);
    if (peek().type != TOK_END && peek().type != TOK_EOF && peek().type != TOK_ELSE)
        return_value = parse_expr();
    return_flag = 1;
}

void parse_put(void) {
    expect(TOK_PUT);
    Token arr = advance();
    int idx = parse_primary();
    expect(TOK_TO);
    int val = parse_primary();
    
    Variable *v = find_var(arr.value);
    if (!v || !v->is_array) error("Invalid array for put");
    while (v->array_length <= idx && v->array_length < MAX_ARRAY_SIZE) v->array_values[v->array_length++] = 0;
    if (idx >= 0 && idx < MAX_ARRAY_SIZE) v->array_values[idx] = val;
}

void parse_append(void) {
    expect(TOK_APPEND);
    Token arr = advance();
    int val = parse_primary();
    Variable *v = find_var(arr.value);
    if (!v || !v->is_array) error("Invalid array for append");
    if (v->array_length >= MAX_ARRAY_SIZE) error("Array full");
    v->array_values[v->array_length++] = val;
}

void parse_class(void) {
    expect(TOK_CLASS);
    Token name = advance();
    if (class_count >= MAX_CLASSES) error("Too many classes");
    
    Class *cls = &classes[class_count++];
    strncpy(cls->name, name.value, 63);
    cls->method_count = 0;
    expect(TOK_DO);
    
    int depth = 1;
    while (depth > 0 && peek().type != TOK_EOF) {
        if (peek().type == TOK_METHOD) {
            advance();
            Token mname = advance();
            int idx = cls->method_count++;
            strncpy(cls->method_names[idx], mname.value, 63);
            cls->method_param_counts[idx] = 0;
            
            // Parse parameters and store their names
            if (peek().type == TOK_WITH) {
                advance();
                while (peek().type == TOK_IDENTIFIER && cls->method_param_counts[idx] < MAX_PARAMS) {
                    strncpy(cls->method_params[idx][cls->method_param_counts[idx]], advance().value, 63);
                    cls->method_param_counts[idx]++;
                }
            }
            
            expect(TOK_DO);
            cls->method_starts[idx] = current_token;
            int mdepth = 1;
            while (mdepth > 0 && peek().type != TOK_EOF) {
                TokenType mcurr = peek().type;
                if (mcurr == TOK_IF || mcurr == TOK_METHOD || mcurr == TOK_WHILE || mcurr == TOK_FOR) {
                    mdepth++;
                } else if (mcurr == TOK_END) {
                    mdepth--;
                }
                // ELSEIF doesn't change depth
                advance();
            }
            cls->method_ends[idx] = current_token - 1;
        } else if (peek().type == TOK_END) { depth--; advance(); }
        else advance();
    }
}

void parse_sleep(void) {
    expect(TOK_SLEEP);
    int ms = parse_primary();
    wl_sleep_ms(ms);
}

void parse_import(void) {
    expect(TOK_IMPORT);
    Token name = advance();
    
    char filepath[MAX_PATH];
    char *lib_name = name.value;
    
    // If it's a string with quotes, use as path
    if (name.type == TOK_STRING) {
        // Try relative to current file first
        snprintf(filepath, MAX_PATH, "%s%s", base_path, lib_name);
        if (strstr(lib_name, ".wl") == NULL) strcat(filepath, ".wl");
    } else {
        // Try: 1) packages/, 2) lib/std/, 3) current dir
        snprintf(filepath, MAX_PATH, "%spackages/%s.wl", base_path, lib_name);
        FILE *f = fopen(filepath, "r");
        if (!f) {
            snprintf(filepath, MAX_PATH, "%slib/std/%s.wl", base_path, lib_name);
            f = fopen(filepath, "r");
        }
        if (!f) {
            snprintf(filepath, MAX_PATH, "%s%s.wl", base_path, lib_name);
            f = fopen(filepath, "r");
        }
        if (f) fclose(f);
    }
    
    // Check if already imported
    for (int i = 0; i < import_count; i++) {
        if (strcmp(imported_files[i], filepath) == 0) return;
    }
    
    // Open and read file
    FILE *f = fopen(filepath, "r");
    if (!f) {
        char msg[256];
        snprintf(msg, 256, "Cannot import: %s", lib_name);
        error(msg);
    }
    
    // Track import
    if (import_count < MAX_IMPORTS) {
        strncpy(imported_files[import_count++], filepath, MAX_PATH - 1);
    }
    
    fseek(f, 0, SEEK_END);
    long size = ftell(f);
    fseek(f, 0, SEEK_SET);
    
    char *src = malloc(size + 1);
    if (!src) { fclose(f); error("Memory error"); }
    fread(src, 1, size, f);
    src[size] = '\0';
    fclose(f);
    
    // Save current position
    int saved_token = current_token;
    int saved_count = token_count;
    
    // Tokenize and parse imported file
    tokenize_append(src);
    tokens[token_count].type = TOK_EOF;
    token_count++;
    
    // Parse from where new tokens start
    current_token = saved_count > 0 ? saved_count - 1 : 0;
    if (current_token > 0 && tokens[current_token].type == TOK_EOF) current_token++;
    
    while (peek().type != TOK_EOF) {
        parse_stmt();
    }
    
    // Restore position (but keep new functions/variables)
    current_token = saved_token;
    
    free(src);
}

void parse_stmt(void) {
    Token t = peek();
    
    switch (t.type) {
        case TOK_SET: parse_set(); break;
        case TOK_PRINT: parse_print(); break;
        case TOK_IF: parse_if(); break;
        case TOK_WHILE: parse_while(); break;
        case TOK_FOR: parse_for(); break;
        case TOK_DEFINE: parse_define(); break;
        case TOK_RETURN: parse_return(); break;
        case TOK_PUT: parse_put(); break;
        case TOK_APPEND: parse_append(); break;
        case TOK_CLASS: parse_class(); break;
        case TOK_IMPORT: parse_import(); break;
        case TOK_SLEEP: parse_sleep(); break;
        case TOK_BREAK: advance(); break_flag = 1; break;
        case TOK_CONTINUE: advance(); continue_flag = 1; break;
        case TOK_CALL: parse_expr(); break;
        case TOK_END:
        case TOK_ELSE:
            return;
        default:
            if (t.type != TOK_EOF) advance();
            break;
    }
}

void parse_program(void) {
    while (peek().type != TOK_EOF) {
        parse_stmt();
    }
}

