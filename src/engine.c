#include "game_state.h"
#include "display.h"
#include "io.h"
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// 전역 게임 상태
static game_state_t game_state;


// 샘플 오브젝트 (나중에 제거 예정)
typedef struct {
    position_t pos;
    position_t dest;
    char symbol;
    int speed;
    int next_move_time;
} sample_object_t;

static sample_object_t sample_obj = {
    .pos = {1, 1},
    .dest = {MAP_HEIGHT - 2, MAP_WIDTH - 2},
    .symbol = 'o',
    .speed = 300,
    .next_move_time = 300
};

// 함수 선언
static void init_game(void);
static void intro(void);
static void outro(void);
static void process_input(void);
static void update_game(void);
static void move_cursor(direction_t dir);
static void move_sample_object(void);
static position_t get_sample_object_next_position(void);

int main(void) {
    srand((unsigned int)time(NULL));

    init_game();
    intro();
    display_game(&game_state);

    while (1) {
        process_input();
        update_game();
        display_game(&game_state);
        Sleep(TICK);
        game_state.game_time += TICK;
    }

    return 0;
}

static void init_game(void) {
    // 맵 초기화
    for (int j = 0; j < MAP_WIDTH; j++) {
        game_state.map[0][0][j] = '#';
        game_state.map[0][MAP_HEIGHT - 1][j] = '#';
    }

    for (int i = 1; i < MAP_HEIGHT - 1; i++) {
        game_state.map[0][i][0] = '#';
        game_state.map[0][i][MAP_WIDTH - 1] = '#';
        for (int j = 1; j < MAP_WIDTH - 1; j++) {
            game_state.map[0][i][j] = ' ';
        }
    }

    // Layer 1 초기화
    for (int i = 0; i < MAP_HEIGHT; i++) {
        for (int j = 0; j < MAP_WIDTH; j++) {
            game_state.map[1][i][j] = 0;
        }
    }

    // 샘플 오브젝트 초기화
    game_state.map[1][sample_obj.pos.row][sample_obj.pos.col] = sample_obj.symbol;

    // 커서 초기화
    game_state.cursor.current = (position_t){1, 1};
    game_state.cursor.previous = (position_t){1, 1};

    // 자원 초기화
    game_state.player_resource = (resource_t){0, 1000, 0, 100};
    game_state.ai_resource = (resource_t){ 0, 1000, 0, 100 };

    // 게임 시간 초기화
    game_state.game_time = 0;
}

static void intro(void) {
    printf("DUNE 1.5\n");
    Sleep(2000);
    //clear_screen();
    system("cls");
}

static void outro(void) {
    printf("Exiting...\n");
    exit(0);
}

static void process_input(void) {
    key_t key = get_key();

    if (is_arrow_key(key)) {
        move_cursor(key_to_direction(key));
    } else {
        switch (key) {
            case KEY_Q:
                outro();
                break;
            case KEY_SPACE:
                // TODO: 선택 또는 행동 수행
                break;
            case KEY_ESCAPE:
                // TODO: 메뉴 열기 또는 선택 취소
                break;
            default:
                break;
        }
    }
}

static void update_game(void) {
    move_sample_object();
    // TODO: Add more game logic here
}

static void move_cursor(direction_t dir) {
    position_t new_pos = move_position(game_state.cursor.current, dir);

    // 유효성 검사
    if (1 <= new_pos.row && new_pos.row <= MAP_HEIGHT - 2 &&
        1 <= new_pos.col && new_pos.col <= MAP_WIDTH - 2) {
        game_state.cursor.previous = game_state.cursor.current;
        game_state.cursor.current = new_pos;
    }
}

static void move_sample_object(void) {
    if (game_state.game_time <= sample_obj.next_move_time) {
        return;
    }

    game_state.map[1][sample_obj.pos.row][sample_obj.pos.col] = 0;
    sample_obj.pos = get_sample_object_next_position();
    game_state.map[1][sample_obj.pos.row][sample_obj.pos.col] = sample_obj.symbol;

    sample_obj.next_move_time = game_state.game_time + sample_obj.speed;
}

static position_t get_sample_object_next_position(void) {
    position_t diff = sub_position(sample_obj.dest, sample_obj.pos);
    direction_t dir;

    // 목적지 도착 시 새로운 목적지 설정
    if (diff.row == 0 && diff.col == 0) {
        if (sample_obj.dest.row == 1 && sample_obj.dest.col == 1) {
            sample_obj.dest = (position_t){MAP_HEIGHT - 2, MAP_WIDTH - 2};
        } else {
            sample_obj.dest = (position_t){1, 1};
        }
        return sample_obj.pos;
    }

    // 이동 방향 결정
    if (abs(diff.row) >= abs(diff.col)) {
        dir = (diff.row >= 0) ? DIRECTION_DOWN : DIRECTION_UP;
    } else {
        dir = (diff.col >= 0) ? DIRECTION_RIGHT : DIRECTION_LEFT;
    }

    // 다음 위치 계산 및 유효성 검사
    position_t next_pos = move_position(sample_obj.pos, dir);
    if (1 <= next_pos.row && next_pos.row <= MAP_HEIGHT - 2 &&
        1 <= next_pos.col && next_pos.col <= MAP_WIDTH - 2 &&
        game_state.map[1][next_pos.row][next_pos.col] == 0) {
        return next_pos;
    } else {
        return sample_obj.pos;  // 이동 불가능한 경우 제자리
    }
}
