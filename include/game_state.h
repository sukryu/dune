#ifndef _GAME_STATE_H_
#define _GAME_STATE_H_

#include <stdio.h>
#include "constants.h"

// 방향을 나타내는 열거형
typedef enum {
    DIRECTION_NONE = 0,
    DIRECTION_UP,
    DIRECTION_RIGHT,
    DIRECTION_DOWN,
    DIRECTION_LEFT
} direction_t;

// 키 입력을 나타내는 열거형
typedef enum {
    KEY_NONE = 0,
    KEY_UP,
    KEY_RIGHT,
    KEY_DOWN,
    KEY_LEFT,
    KEY_SPACE,
    KEY_ESCAPE,
    KEY_Q,
    // 추가 키들...
} key_t;

// 위치를 나타내는 구조체
typedef struct {
    int row;
    int col;
} position_t;

// 커서를 나타내는 구조체
typedef struct {
    position_t current;
    position_t previous;
} cursor_t;

// 자원을 나타내는 구조체
typedef struct {
    int spice;
    int spice_capacity;
    int population;
    int population_capacity;
} resource_t;

// 게임 오브젝트의 기본 구조체
typedef struct game_object_t {
    char type;        // 'B': 건물, 'U': 유닛, 'T': 지형
    char symbol;      // 화면에 표시될 심볼
    position_t pos;   // 오브젝트의 위치
    int hp;           // 현재 체력
    int max_hp;       // 최대 체력
    int team;         // 소속 팀 (0: 중립, 1: 플레이어, 2: AI)
    void (*update)(struct game_object_t* self, void* game_state);  // 업데이트 함수 포인터
    void (*render)(struct game_object_t* self, void* game_state);  // 렌더링 함수 포인터
} game_object_t;

// 유닛 구조체 (game_object_t를 확장)
typedef struct {
    game_object_t base;  // 기본 게임 오브젝트 구조체
    int attack;          // 공격력
    int defense;         // 방어력
    int speed;           // 이동 속도
    int sight;           // 시야 범위
    int next_move_time;  // 다음 이동 시간
    void (*move)(struct game_object_t* self, position_t target);  // 이동 함수 포인터
    void (*attack_func)(struct game_object_t* self, struct game_object_t* target);  // 공격 함수 포인터
} unit_t;

// 건물 구조체 (game_object_t를 확장)
typedef struct {
    game_object_t base;  // 기본 게임 오브젝트 구조체
    int build_time;      // 건설에 필요한 시간
    int cost;            // 건설 비용
    void (*produce)(struct game_object_t* self, char unit_type);  // 생산 함수 포인터
} building_t;

// 게임 상태를 나타내는 구조체
typedef struct {
    char map[N_LAYER][MAP_HEIGHT][MAP_WIDTH];  // 다중 레이어 맵
    resource_t player_resource;   // 플레이어 자원
    resource_t ai_resource;       // AI 자원
    game_object_t* objects[MAX_OBJECTS];  // 게임 오브젝트 배열
    int object_count;             // 현재 게임 오브젝트 수
    cursor_t cursor;              // 커서 정보
    int game_time;                // 현재 게임 시간 (ms)
    char messages[MAX_MESSAGES][MESSAGE_LENGTH];  // 시스템 메시지 배열
    int message_count;            // 현재 메시지 수
    game_object_t* selected_object;  // 현재 선택된 오브젝트
} game_state_t;

// 게임 상태 초기화 함수
void init_game_state(game_state_t* state);

// 게임 오브젝트 추가 함수
int add_game_object(game_state_t* state, game_object_t* obj);

// 게임 오브젝트 제거 함수
void remove_game_object(game_state_t* state, game_object_t* obj);

// 메시지 추가 함수
void add_message(game_state_t* state, const char* message);

#endif // _GAME_STATE_H_