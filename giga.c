#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <termios.h>

struct termios orig_termios;

void disableRawMode() {
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios);
}

void enableRawMode() {
    tcgetattr(STDIN_FILENO, &orig_termios);
    atexit(disableRawMode); //this can be called from anywhere
    
    struct termios raw = orig_termios;
    raw.c_iflag &= ~(ICRNL | IXON);
    raw.c_oflag &= ~(OPOST); //no default output processing
    raw.c_lflag &= ~(ECHO | ICANON | IEXTEN | ISIG); //turn off echo, canonical, CTRL sigs
    raw.c_cc[VMIN] = 0;
    raw.c_cc[VTIME] = 10;

    tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw); 
}

int main() {
    enableRawMode();
    
    while (1) {
        char c = '\0';
        read(STDIN_FILENO, &c, 1);
        if iscntrl(c) {
            printf("%d \r\n", c);
        } else {
            printf("%d (%c) \r\n", c, c);
        }
        if (c == 'q') break;
    }
    
    return 0;
}