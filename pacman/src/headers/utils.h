#ifndef _UTILS_H_
#define _UTILS_H_

#ifdef _WIN32

char getchImpl(void);

// Unix-like systems and Linux
#elif defined(__unix__) || defined(__linux__)
/* This modification includes a getch() function that emulates the behavior of getch() in Windows using termios
 */
char getchImpl(void);

#endif

// Clear the input buffer to prevent issues with non-integer inputs
void clearInputBuffer();

// Custom function to get numeric characters only
int getInputNumber(int *input);

#endif // _UTILS_H_