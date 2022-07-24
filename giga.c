/*** includes ***/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <termios.h>

/*** defines ***/
#define CTRL_KEY(k) (k & 0x1f)

/*** data ***/

struct termios orig_termios;

/*** terminal ***/

void die(const char* str) {
    perror(str);
    exit(1);
}

void disableRawMode() {
    if(tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios) == -1) die("tcsetattr");
}

void enableRawMode() {
    if (tcgetattr(STDIN_FILENO, &orig_termios) == -1) die("tcgetattr");
    atexit(disableRawMode); //needs to have return type of void
    
    struct termios termios_p = orig_termios;
    termios_p.c_iflag &= ~(IGNBRK | BRKINT | PARMRK | ISTRIP
                           | INLCR | IGNCR | ICRNL | IXON);
    termios_p.c_oflag &= ~OPOST;
    termios_p.c_lflag &= ~(ECHO | ECHONL | ICANON | ISIG | IEXTEN);
    termios_p.c_cflag &= ~(CSIZE | PARENB);
    termios_p.c_cflag |= CS8;
    termios_p.c_cc[VMIN] = 0;
    termios_p.c_cc[VTIME] = 10;

    if(tcsetattr(STDIN_FILENO, TCSAFLUSH, &termios_p) == -1) die("tcsetattr");
}

/*** input ***/

/*** init ***/

int main() {
    enableRawMode();
    
    while (1) {
        char c = '\0';
        read(STDIN_FILENO, &c, 1);
        if (c == CTRL_KEY('q')) break;
        printf("%c\r\n", c);
    }
    
    return 0;
}