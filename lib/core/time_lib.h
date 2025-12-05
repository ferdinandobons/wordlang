/*
 * Wordlang Time Library
 * Core C library - compiled with interpreter
 */

#ifndef WL_TIME_LIB_H
#define WL_TIME_LIB_H

#include <time.h>
#include <stdio.h>

// Buffer for formatted strings
static char _wl_time_buffer[64];

// Get current Unix timestamp
static int wl_now() {
    return (int)time(NULL);
}

// Get current hour (0-23)
static int wl_hour() {
    time_t t = time(NULL);
    struct tm *tm = localtime(&t);
    return tm->tm_hour;
}

// Get current minute (0-59)
static int wl_minute() {
    time_t t = time(NULL);
    struct tm *tm = localtime(&t);
    return tm->tm_min;
}

// Get current second (0-59)
static int wl_second() {
    time_t t = time(NULL);
    struct tm *tm = localtime(&t);
    return tm->tm_sec;
}

// Get current day of month (1-31)
static int wl_day() {
    time_t t = time(NULL);
    struct tm *tm = localtime(&t);
    return tm->tm_mday;
}

// Get current month (1-12)
static int wl_month() {
    time_t t = time(NULL);
    struct tm *tm = localtime(&t);
    return tm->tm_mon + 1;
}

// Get current year
static int wl_year() {
    time_t t = time(NULL);
    struct tm *tm = localtime(&t);
    return tm->tm_year + 1900;
}

// Get day of week (0=Sunday, 6=Saturday)
static int wl_weekday() {
    time_t t = time(NULL);
    struct tm *tm = localtime(&t);
    return tm->tm_wday;
}

// Get day of year (1-366)
static int wl_yearday() {
    time_t t = time(NULL);
    struct tm *tm = localtime(&t);
    return tm->tm_yday + 1;
}

// Format current time as "HH:MM:SS"
static const char* wl_time_str() {
    time_t t = time(NULL);
    struct tm *tm = localtime(&t);
    snprintf(_wl_time_buffer, sizeof(_wl_time_buffer),
             "%02d:%02d:%02d", tm->tm_hour, tm->tm_min, tm->tm_sec);
    return _wl_time_buffer;
}

// Format current date as "YYYY-MM-DD"
static const char* wl_date_str() {
    time_t t = time(NULL);
    struct tm *tm = localtime(&t);
    snprintf(_wl_time_buffer, sizeof(_wl_time_buffer),
             "%04d-%02d-%02d", tm->tm_year + 1900, tm->tm_mon + 1, tm->tm_mday);
    return _wl_time_buffer;
}

// Format full datetime as "YYYY-MM-DD HH:MM:SS"
static const char* wl_datetime_str() {
    time_t t = time(NULL);
    struct tm *tm = localtime(&t);
    snprintf(_wl_time_buffer, sizeof(_wl_time_buffer),
             "%04d-%02d-%02d %02d:%02d:%02d",
             tm->tm_year + 1900, tm->tm_mon + 1, tm->tm_mday,
             tm->tm_hour, tm->tm_min, tm->tm_sec);
    return _wl_time_buffer;
}

// Sleep for milliseconds (approximation using busy loop or sleep)
static void wl_sleep_ms(int ms) {
    if (ms <= 0) return;
    #ifdef _WIN32
    Sleep(ms);
    #else
    struct timespec ts;
    ts.tv_sec = ms / 1000;
    ts.tv_nsec = (ms % 1000) * 1000000;
    nanosleep(&ts, NULL);
    #endif
}

#endif

