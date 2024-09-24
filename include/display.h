#ifndef _DISPLAY_H_
#define _DISPLAY_H_

#include "game_state.h"

void init_display(void);
void close_display(void);
void clear_draw_buffer(void);
void flip_display(void);
void display_game(const game_state_t* state);
void update_display(const game_state_t* state);
void clear_screen(void);

#endif
