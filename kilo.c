#include <unistd.h>
#include <termios.h>
#include <stdlib.h>

struct termios orig_termios;

void disableRawMode() {
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios);
}

void enableRawMode() {
    tcgetattr(STDIN_FILENO, &orig_termios);
    // atexit used to register disableRawMode to be called automatically when the program exits
    atexit(disableRawMode);

    struct termios raw = orig_termios;
    // Reading terminal attributes with tcgetattr
    // c_lflag = local flags
    // ECHO is a bitflag
    // The ECHO feature causes each key to be printed out in the terminal.
    // This is only useful in canonical mode (cooked mode), not raw mode
    raw.c_lflag &= ~(ECHO);

    // Using tcsetattr to set terminal attribues after modifying
    // TCSAFLUSH argument specifies when to apply change:
    // Waits for all pending output to be written onto the terminal, and discards any input that has not been read.
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}

int main() {
    enableRawMode();

    char c;
    while (read(STDIN_FILENO, &c, 1) == 1 && c != 'q'); 
    return 0;
}
