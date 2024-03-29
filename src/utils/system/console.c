#include "console.h"

#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>

#include "../defines.h"

#if WIN
    #include <Windows.h>
#elif UNIX
    #include <unistd.h>
    #include <termios.h>
    #include <sys/ioctl.h>
#endif

override
void get_screen_size(int* width, int* height) {
    #if WIN
        CONSOLE_SCREEN_BUFFER_INFO csbi;
        GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
        
        *width = csbi.srWindow.Right - csbi.srWindow.Left + 1;
        *height = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
    #elif UNIX
        struct winsize w;
        ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);

        *width = w.ws_col;
        *height = w.ws_row;
    #endif
}

override
void clear_screen() {
    #if WIN
        system("cls");
    #elif UNIX
        system("clear");
    #endif
}

override
void set_console_title(string title) {
    #if WIN
        system(concat("title ", title));
    #elif UNIX
        printf("\033]0;%s\007", title);
    #endif
}

override
void pause_console() {
    getchar();
}

override
void print(string s, ...) {
    va_list args;
    va_start(args, s);
    vprintf(s, args);
    va_end(args);
}

override
void println(string s, ...) {
    va_list args;
    va_start(args, s);
    vprintf(s, args);
    printf("\n");
    va_end(args);
}

#if WIN
private HANDLE hInput;
private INPUT_RECORD input_record;
private DWORD events_read;

override
void start_capture() {
    hInput = GetStdHandle(STD_INPUT_HANDLE);
}

override
int read_capture() {
    if (ReadConsoleInput(hInput, &input_record, 1, &events_read)) {
        if (input_record.EventType == KEY_EVENT && input_record.Event.KeyEvent.bKeyDown) {
            int ca = input_record.Event.KeyEvent.uChar.AsciiChar;
            int cv = input_record.Event.KeyEvent.wVirtualKeyCode;
            int key = ca == 0 ? -cv : ca + (ca > 0 ? 0 : 256);

            if (key >= 0 && key <= 7) return 0;
            if (key >= 10 && key <= 12) return 0;
            if (key >= 14 && key <= 26) return 0;
            if (key >= -18 && key <= -16) return 0;
            if (key >= -54 && key <= -52) return 0;
            if (key == -220 || key == -221 || key == -191 || key == -12) return 0;

            switch (key) {
                case   13: return  K_RETURN;
                case  -46: return K_DELETE;
                //case  -49: return 251; // ¹
            }

            return key; // any other ASCII/virtual character
        }
    }
    return 0;
}

override
void stop_capture() {
}
#elif UNIX
private struct termios term;

override
void start_capture() {
    tcgetattr(0, &term);

    term.c_lflag &= ~(ICANON | ECHO); // turn off line buffering and echoing
    tcsetattr(0, TCSANOW, &term);
}

// https://stackoverflow.com/questions/421860/capture-characters-from-standard-input-without-waiting-for-enter-to-be-pressed
override
int read_capture() {
    int nbbytes;
    ioctl(0, FIONREAD, &nbbytes); // 0 is STDIN
    if (!nbbytes) return 0; // no key pressed
    
    int key = getchar();
    if (key == 27 && nbbytes == 1) return K_ESCAPE; // stupid fix
    if (key == 27 || key == 194 || key == 195) { // escape, 194/195 is escape for °ß´äöüÄÖÜ
        key = getchar();
        if (key == 91) { // [ following escape
            key = getchar(); // get code of next char after \e[
            if (key == 49) { // F5-F8
                key = 62 + getchar(); // 53, 55-57
                if (key == 115) key++; // F5 code is too low by 1
                getchar(); // take in following ~ (126), but discard code
            } else if (key == 50) { // insert or F9-F12
                key = getchar();
                if (key == 126) { // insert
                    key = 45;
                } else { // F9-F12
                    key += 71; // 48, 49, 51, 52
                    if (key < 121) key++; // F11 and F12 are too low by 1
                    getchar(); // take in following ~ (126), but discard code
                }
            } else if (key == 51 || key == 53 || key == 54) { // delete, page up/down
                getchar(); // take in following ~ (126), but discard code
            }
        } else if (key == 79) { // F1-F4
            key = 32 + getchar(); // 80-83
        } else if (key == 10) {
            key = 27;
        }
        key = -key; // use negative numbers for escaped keys
    }

    if (key >= 0 && key <= 8) return 0;
    if (key >= 11 && key <= 26) return 0;
    
    switch (key) {
        case  127: return K_BACKSPACE;
        case  -27: return K_ESCAPE;
        case  -65: return K_UP;
        case  -66: return K_DOWN;
        case  -68: return K_LEFT;
        case  -67: return K_RIGHT;
        case  -51: return K_DELETE;
        case  -53: return K_PAGE_UP;
        case  -54: return K_PAGE_DOWN;
        case  -72: return K_HOME;
        case  -70: return K_END;
        /*case -164: return 132; // ä
        case -182: return 148; // ö
        case -188: return 129; // ü
        case -132: return 142; // Ä
        case -150: return 153; // Ö
        case -156: return 154; // Ü
        case -159: return 225; // ß
        case -181: return 230; // µ
        case -167: return 245; // §
        case -176: return 248; // °
        case -178: return 253; // ²
        case -179: return 252; // ³
        case -180: return 239; // ´*/
    }
    return key; // any other ASCII character
}

override
void stop_capture() {
    term.c_lflag |= (ICANON | ECHO); // turn on line buffering and echoing
    tcsetattr(0, TCSANOW, &term);
}
#endif
