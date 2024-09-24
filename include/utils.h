#ifndef _UTILS_H_
#define _UTILS_H_

#include "game_state.h"
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

// 두 위치를 더하는 함수
position_t add_position(position_t p1, position_t p2);

// 두 위치를 빼는 함수
position_t sub_position(position_t p1, position_t p2);

// 방향키인지 확인하는 함수
#define is_arrow_key(k) ((k) == KEY_UP || (k) == KEY_DOWN || (k) == KEY_LEFT || (k) == KEY_RIGHT)

// 키를 방향으로 변환하는 함수
direction_t key_to_direction(key_t key);

// 방향을 위치 벡터로 변환하는 함수
position_t direction_to_position(direction_t d);

// 위치를 특정 방향으로 이동시키는 함수
position_t move_position(position_t p, direction_t d);

// 두 위치 사이의 거리를 계산하는 함수
int calculate_distance(position_t p1, position_t p2);

// 게임 오브젝트를 생성하는 함수
game_object_t* create_game_object(char type, char symbol, position_t pos, int team);

// 게임 오브젝트를 제거하는 함수
void destroy_game_object(game_object_t* obj);

// 특정 위치에 있는 게임 오브젝트를 찾는 함수
game_object_t* find_object_at(const game_state_t* state, position_t pos);

bool is_position_valid(position_t pos);
bool is_position_empty(const game_state_t* state, position_t pos);
void add_message(game_state_t* state, const char* message);

#endif