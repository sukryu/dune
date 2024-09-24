#ifndef _IO_H_
#define _IO_H_

#include "game_state.h"
#include <Windows.h>

// 키 입력을 받는 함수
key_t get_key(void);

// 특정 위치에 특정 색상으로 문자를 출력하는 함수
void print_char(position_t pos, char ch, int color);

// 커서를 특정 위치로 이동시키는 함수
void goto_xy(position_t pos);

// 텍스트 색상을 설정하는 함수
void set_color(int color);

// 화면을 지우는 함수
void clear_screen(void);

#endif