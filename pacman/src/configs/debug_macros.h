#ifndef _DEBUG_MACROS_H
#define _DEBUG_MACROS_H

/*
 * debug_macros.h
 *
 * Some macro definitions of this application
 * 
*/

/* Debug configs
 */

// Enable DEBUG mode
//#define DEBUG

#ifdef DEBUG
#include <assert.h>
#include <stdio.h>
#include <string.h>

// ANSI color codes for printing in color
#define ANSI_RESET_COLOR  "\x1B[0m"
#define ANSI_GREEN_COLOR  "\x1B[32m"
#define ANSI_RED_COLOR "\x1b[31m"

// Macro to extract only the file name from the full path
#define FILENAME_ONLY(file) \
    (strrchr(file, '/') ? strrchr(file, '/') + 1 : \
    (strrchr(file, '\\') ? strrchr(file, '\\') + 1 : file))

// Debug assert macro
#define debug_assert(expr, message) \
    do { \
        if (!(expr)) { \
            fprintf(stderr, ANSI_RED_COLOR "Assertion failed" ANSI_RESET_COLOR ": %s, file %s, line %d, function %s()\n", message, FILENAME_ONLY(__FILE__), __LINE__, __func__); \
            assert(expr); \
        } \
    } while (0)

// Debug print macro
#define debug_print(fmt, ...) \
    do { \
        fprintf(stderr, ANSI_GREEN_COLOR "Debug" ANSI_RESET_COLOR ": %s:%d:%s(): " fmt, FILENAME_ONLY(__FILE__), __LINE__, __func__, __VA_ARGS__); \
    } while (0)

#elif NDEBUG
// If NDEBUG is defined, provide empty macros for debug features
#define debug_assert(expr, message) ((void)0)
#define debug_print(fmt, ...) ((void)0)
#endif // DEBUG

#endif // _DEBUG_MACROS_H