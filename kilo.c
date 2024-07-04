#include <unistd.h>
#include <termios.h>

struct termois orig_termois;

void disableRawMode() {
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termois);
}

void enableRawMode() {
    struct termios raw;

    tcgetattr(STDIN_FILENO, &raw);
    
    // c_lflag = local flags
    // ECHO is a bitflag
    raw.c_lflag &= ~(ECHO);

    tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}

int main() {
    enableRawMode();

    char c;
    while (read(STDIN_FILENO, &c, 1) == 1 && c != 'q'); 
    return 0;
}
