#ifndef _SYSTEM_MACROS_H
#define _SYSTEM_MACROS_H

/* Definitions for system-specific commands
 */
#ifdef _WIN32
    #define CLEAR_SCREEN system("cls")
// Unix-like systems and Linux
#elif defined(__unix__) || defined(__linux__)
    #define CLEAR_SCREEN system("clear")
#endif

#endif // SYSTEM_MACROS_H