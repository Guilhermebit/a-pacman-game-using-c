#include <stdio.h>
#include "headers/utils.h"
#include <ctype.h>

#ifdef _WIN32
    #include <conio.h>

    char getchImpl() {
        return _getch();
    }

#elif defined(__unix__) || defined(__linux__)
    #include <stdio.h>
    #include <termios.h>
    #include <unistd.h>

    char getchImpl() {
        char buf = 0;
        struct termios old = {0};
        fflush(stdout);
        if (tcgetattr(0, &old) < 0)
            perror("tcsetattr()");
        old.c_lflag &= ~ICANON;
        old.c_lflag &= ~ECHO;
        old.c_cc[VMIN] = 1;
        old.c_cc[VTIME] = 0;
        if (tcsetattr(0, TCSANOW, &old) < 0)
            perror("tcsetattr ICANON");
        if (read(0, &buf, 1) < 0)
            perror ("read()");
        old.c_lflag |= ICANON;
        old.c_lflag |= ECHO;
        if (tcsetattr(0, TCSADRAIN, &old) < 0)
            perror ("tcsetattr ~ICANON");
        return buf;
    }

#endif

void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int getInputNumber(int *input) {

    if(scanf("%d", input) == 1) {
        int c;
        while((c = getchar()) != '\n' && c != EOF) {
             // check for any trailing characters
             if(!isspace(c)) {
                clearInputBuffer();
			    return 1;
            }
        }

        // At this point, input contains a valid integer
        return 0;

    } else {
        //printf("Invalid input. Please enter a number.\n");
        clearInputBuffer();
        return 1;  // Failure
    }

    return 1;
}