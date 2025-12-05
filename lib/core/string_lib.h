/*
 * Wordlang String Library
 * Core C library - compiled with interpreter
 */

#ifndef WL_STRING_LIB_H
#define WL_STRING_LIB_H

#include <string.h>
#include <ctype.h>
#include <stdio.h>

// Buffer for string operations
static char _wl_string_buffer[512];

// String length
__attribute__((unused)) static int wl_strlen(const char *s) {
    return (int)strlen(s);
}

// Convert to uppercase (returns static buffer)
static const char* wl_upper(const char *s) {
    int i = 0;
    while (s[i] && i < 510) {
        _wl_string_buffer[i] = toupper((unsigned char)s[i]);
        i++;
    }
    _wl_string_buffer[i] = '\0';
    return _wl_string_buffer;
}

// Convert to lowercase (returns static buffer)
static const char* wl_lower(const char *s) {
    int i = 0;
    while (s[i] && i < 510) {
        _wl_string_buffer[i] = tolower((unsigned char)s[i]);
        i++;
    }
    _wl_string_buffer[i] = '\0';
    return _wl_string_buffer;
}

// Trim whitespace from both ends
static const char* wl_trim(const char *s) {
    while (isspace((unsigned char)*s)) s++;
    if (*s == '\0') {
        _wl_string_buffer[0] = '\0';
        return _wl_string_buffer;
    }
    const char *end = s + strlen(s) - 1;
    while (end > s && isspace((unsigned char)*end)) end--;
    int len = end - s + 1;
    if (len > 510) len = 510;
    strncpy(_wl_string_buffer, s, len);
    _wl_string_buffer[len] = '\0';
    return _wl_string_buffer;
}

// Check if string starts with prefix
static int wl_startswith(const char *s, const char *prefix) {
    return strncmp(s, prefix, strlen(prefix)) == 0;
}

// Check if string ends with suffix
static int wl_endswith(const char *s, const char *suffix) {
    int slen = strlen(s);
    int sufflen = strlen(suffix);
    if (sufflen > slen) return 0;
    return strcmp(s + slen - sufflen, suffix) == 0;
}

// Check if string contains substring
static int wl_contains(const char *s, const char *sub) {
    return strstr(s, sub) != NULL;
}

// Find index of substring (-1 if not found)
static int wl_indexof(const char *s, const char *sub) {
    const char *p = strstr(s, sub);
    if (p == NULL) return -1;
    return (int)(p - s);
}

// Get character at index (returns ASCII code)
static int wl_charat(const char *s, int index) {
    int len = strlen(s);
    if (index < 0 || index >= len) return 0;
    return (unsigned char)s[index];
}

// Reverse string
static const char* wl_reverse(const char *s) {
    int len = strlen(s);
    if (len > 510) len = 510;
    for (int i = 0; i < len; i++) {
        _wl_string_buffer[i] = s[len - 1 - i];
    }
    _wl_string_buffer[len] = '\0';
    return _wl_string_buffer;
}

// Repeat string n times
static const char* wl_repeat(const char *s, int n) {
    _wl_string_buffer[0] = '\0';
    int len = strlen(s);
    int pos = 0;
    for (int i = 0; i < n && pos + len < 510; i++) {
        strcpy(_wl_string_buffer + pos, s);
        pos += len;
    }
    return _wl_string_buffer;
}

// Replace first occurrence
static const char* wl_replace(const char *s, const char *old, const char *new_str) {
    const char *p = strstr(s, old);
    if (p == NULL) {
        strncpy(_wl_string_buffer, s, 510);
        _wl_string_buffer[510] = '\0';
        return _wl_string_buffer;
    }
    int prefix_len = p - s;
    int old_len = strlen(old);
    int new_len = strlen(new_str);
    
    if (prefix_len + new_len + strlen(p + old_len) > 510) {
        strncpy(_wl_string_buffer, s, 510);
        _wl_string_buffer[510] = '\0';
        return _wl_string_buffer;
    }
    
    strncpy(_wl_string_buffer, s, prefix_len);
    strcpy(_wl_string_buffer + prefix_len, new_str);
    strcpy(_wl_string_buffer + prefix_len + new_len, p + old_len);
    return _wl_string_buffer;
}

// Integer to string
__attribute__((unused)) static const char* wl_int_to_str(int n) {
    snprintf(_wl_string_buffer, sizeof(_wl_string_buffer), "%d", n);
    return _wl_string_buffer;
}

// String to integer
__attribute__((unused)) static int wl_str_to_int(const char *s) {
    return atoi(s);
}

// Check if string is numeric
static int wl_is_numeric(const char *s) {
    if (*s == '-' || *s == '+') s++;
    if (*s == '\0') return 0;
    while (*s) {
        if (!isdigit((unsigned char)*s)) return 0;
        s++;
    }
    return 1;
}

// Check if string is alphabetic
static int wl_is_alpha(const char *s) {
    if (*s == '\0') return 0;
    while (*s) {
        if (!isalpha((unsigned char)*s)) return 0;
        s++;
    }
    return 1;
}

#endif

