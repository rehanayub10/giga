#include <stdio.h>
#include <unistd.h>
#include <termios.h>

int main() {
    char c;
    while (1) {
        read(STDIN_FILENO, &c, 1);
        printf("%c", c);
        if (c == 'q') break;
    }
    
    return 0;
}