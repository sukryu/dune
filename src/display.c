#include "display.h"
#include "io.h"
#include "utils.h"
#include <stdio.h>
#include <string.h>

#define BUFFER_WIDTH TOTAL_WIDTH
#define BUFFER_HEIGHT TOTAL_HEIGHT

static char front_buffer[BUFFER_HEIGHT][BUFFER_WIDTH];  // 프론트 버퍼
static char back_buffer[BUFFER_HEIGHT][BUFFER_WIDTH];   // 백 버퍼

// 버퍼를 초기화하는 함수
void init_display(void)
{
    memset(front_buffer, ' ', sizeof(front_buffer));  // 프론트 버퍼를 초기화
    memset(back_buffer, ' ', sizeof(back_buffer));    // 백 버퍼를 초기화
}

// 백 버퍼를 비우는 함수
void clear_draw_buffer(void)
{
    memset(back_buffer, ' ', sizeof(back_buffer));  // 백 버퍼를 공백 문자로 초기화
}

// 백 버퍼 내용을 화면으로 출력하는 함수
void flip_display(void)
{
    for (int row = 0; row < BUFFER_HEIGHT; row++) {
        for (int col = 0; col < BUFFER_WIDTH; col++) {
            if (back_buffer[row][col] != front_buffer[row][col]) {
                // 백 버퍼와 프론트 버퍼가 다른 경우에만 출력
                position_t pos = {row, col};
                print_char(pos, back_buffer[row][col], COLOR_DEFAULT);
                front_buffer[row][col] = back_buffer[row][col];  // 프론트 버퍼 갱신
            }
        }
    }
}

// 화면 전체를 클리어하는 함수 (매번 호출되지 않도록 주의)
void clear_screen(void)
{
    system("cls");
}

// 전체 게임 화면을 백 버퍼에 그리는 함수
void display_game(const game_state_t* state)
{
    clear_draw_buffer();  // 백 버퍼를 초기화
    
    // 맵을 백 버퍼에 표시
    display_map(state);
    
    // 자원 상태 표시
    display_resource_status(state);
    
    // 상태창 표시 (선택된 유닛/지형 정보)
    display_unit_status(state);
    
    // 시스템 메시지 표시
    display_messages(state);
    
    // 명령어 창 표시
    display_commands(state);

    flip_display();  // 변경된 내용을 화면에 출력
}

// 맵을 백 버퍼에 그리는 함수
static void display_map(const game_state_t* state)
{
    draw_border(0, 0, MAP_HEIGHT, MAP_WIDTH);  // 맵 경계를 그립니다.
    
    for (int row = 1; row < MAP_HEIGHT - 1; row++) {
        for (int col = 1; col < MAP_WIDTH - 1; col++) {
            position_t pos = {row, col};
            char ch = state->map[0][row][col];  // 0번 레이어를 사용해 지형을 출력
            back_buffer[row][col] = ch;  // 백 버퍼에 저장
        }
    }
}

// 자원 상태를 백 버퍼에 그리는 함수
static void display_resource_status(const game_state_t* state)
{
    position_t pos = {1, MAP_WIDTH + 1};
    goto_xy(pos);
    snprintf(back_buffer[pos.row][pos.col], BUFFER_WIDTH - pos.col, "Player Resources:");
    
    pos.row++;
    snprintf(back_buffer[pos.row][pos.col], BUFFER_WIDTH - pos.col, "Spice: %d/%d", state->player_resource.spice, state->player_resource.spice_capacity);
    
    pos.row++;
    snprintf(back_buffer[pos.row][pos.col], BUFFER_WIDTH - pos.col, "Population: %d/%d", state->player_resource.population, state->player_resource.population_capacity);
}

// 상태창을 백 버퍼에 그리는 함수
static void display_unit_status(const game_state_t* state)
{
    position_t pos = {5, MAP_WIDTH + 1};
    
    if (state->selected_object != NULL) {
        game_object_t* obj = state->selected_object;
        snprintf(back_buffer[pos.row][pos.col], BUFFER_WIDTH - pos.col, "Selected Object:");
        
        pos.row++;
        snprintf(back_buffer[pos.row][pos.col], BUFFER_WIDTH - pos.col, "Type: %c", obj->type);
        
        pos.row++;
        snprintf(back_buffer[pos.row][pos.col], BUFFER_WIDTH - pos.col, "HP: %d/%d", obj->hp, obj->max_hp);
    } else {
        snprintf(back_buffer[pos.row][pos.col], BUFFER_WIDTH - pos.col, "No object selected");
    }
}

// 시스템 메시지를 백 버퍼에 그리는 함수
static void display_messages(const game_state_t* state)
{
    position_t pos = {MAP_HEIGHT + 1, 1};
    
    for (int i = 0; i < state->message_count && i < SYSTEM_MESSAGE_HEIGHT; i++) {
        snprintf(back_buffer[pos.row + i][pos.col], BUFFER_WIDTH - pos.col, "%s", state->messages[i]);
    }
}

// 명령어 창을 백 버퍼에 그리는 함수
static void display_commands(const game_state_t* state)
{
    position_t pos = {MAP_HEIGHT + SYSTEM_MESSAGE_HEIGHT + 1, 1};
    snprintf(back_buffer[pos.row][pos.col], BUFFER_WIDTH - pos.col, "Commands:");
    
    pos.row++;
    snprintf(back_buffer[pos.row][pos.col], BUFFER_WIDTH - pos.col, "Arrow keys: Move cursor");
    
    pos.row++;
    snprintf(back_buffer[pos.row][pos.col], BUFFER_WIDTH - pos.col, "Space: Select/Action");
    
    pos.row++;
    snprintf(back_buffer[pos.row][pos.col], BUFFER_WIDTH - pos.col, "Q: Quit game");
}
