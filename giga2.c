/*** includes ***/

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <termios.h>

/*** defines ***/
#define CTRL_KEY(k) (k & 0x1f)

/*** data ***/

struct termios orig_termios;

/*** terminal ***/
void die (const char* s) {
    perror(s);
    exit(1);
}

void disableRawMode() {
    if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios) == -1) die("tcsetattr");
}

void enableRawMode() {
    if (tcgetattr(STDIN_FILENO, &orig_termios) == -1) die("tcgetattr");
    atexit(disableRawMode); //this can be called from anywhere
    
    struct termios raw = orig_termios;
    raw.c_iflag &= ~(BRKINT | ICRNL | INPCK | ISTRIP | IXON);
    raw.c_oflag &= ~(OPOST); //no default output processing
    raw.c_cflag |= (CS8);
    raw.c_lflag &= ~(ECHO | ICANON | IEXTEN | ISIG); //turn off echo, canonical, CTRL sigs
    raw.c_cc[VMIN] = 0;
    raw.c_cc[VTIME] = 10;

    if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw) == -1) die("tcsetattr"); 
}

void editorProcessKeypress() {
    char c = '\0';
    if (read(STDIN_FILENO, &c, 1) == -1 && errno != EAGAIN) die ("read");
    if iscntrl(c) {
        printf("%d \r\n", c);
    } else {
        printf("%d (%c) \r\n", c, c);
    }
    if (c == CTRL_KEY('q')) break;
}

/*** init ***/

int main() {
    enableRawMode();
    
    while (1) {
        
        
    }
    
    return 0;
}