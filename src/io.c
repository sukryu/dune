#include "io.h"
#include <conio.h>
#include <stdio.h>

void goto_xy(position_t pos)
{
    COORD coord = {pos.col, pos.row};  // Windows API uses (x, y) order
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void set_color(int color)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void print_char(position_t pos, char ch, int color)
{
    set_color(color);
    goto_xy(pos);
    putchar(ch);
}

key_t get_key(void)
{
    if (!_kbhit()) {
        return KEY_NONE;
    }

    int ch = _getch();
    switch (ch) {
        case 'q':
        case 'Q':
            return KEY_Q;
        case ' ':
            return KEY_SPACE;
        case 27:  // ESC
            return KEY_ESCAPE;
        case 224:  // Special keys (arrows, function keys, etc.)
            ch = _getch();
            switch (ch) {
                case 72: return KEY_UP;
                case 80: return KEY_DOWN;
                case 75: return KEY_LEFT;
                case 77: return KEY_RIGHT;
            }
        default:
            return KEY_NONE;
    }
}

void clear_screen(void)
{
    system("cls");
}