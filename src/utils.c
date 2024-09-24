#include "utils.h"

position_t add_position(position_t p1, position_t p2)
{
    return (position_t){p1.row + p2.row, p1.col + p2.col};
}

position_t sub_position(position_t p1, position_t p2)
{
    return (position_t){p1.row - p2.row, p1.col - p2.col};
}

direction_t key_to_direction(key_t key)
{
    switch (key) {
        case KEY_UP:    return DIRECTION_UP;
        case KEY_DOWN:  return DIRECTION_DOWN;
        case KEY_LEFT:  return DIRECTION_LEFT;
        case KEY_RIGHT: return DIRECTION_RIGHT;
        default:        return DIRECTION_NONE;
    }
}

position_t direction_to_position(direction_t d)
{
    static const position_t direction_vectors[] = {
        [DIRECTION_NONE]  = {0, 0},
        [DIRECTION_UP]    = {-1, 0},
        [DIRECTION_DOWN]  = {1, 0},
        [DIRECTION_LEFT]  = {0, -1},
        [DIRECTION_RIGHT] = {0, 1}
    };
    return direction_vectors[d];
}

position_t move_position(position_t p, direction_t d)
{
    return add_position(p, direction_to_position(d));
}

int calculate_distance(position_t p1, position_t p2)
{
    position_t diff = sub_position(p1, p2);
    return (int)sqrt(diff.row * diff.row + diff.col * diff.col);
}

game_object_t* create_game_object(char type, char symbol, position_t pos, int team)
{
    game_object_t* obj = (game_object_t*)malloc(sizeof(game_object_t));
    if (obj == NULL) {
        return NULL;
    }

    obj->type = type;
    obj->symbol = symbol;
    obj->pos = pos;
    obj->hp = 100;  // Default value, should be set properly for each object type
    obj->max_hp = 100;
    obj->team = team;
    obj->update = NULL;
    obj->render = NULL;

    return obj;
}

void destroy_game_object(game_object_t* obj)
{
    if (obj != NULL) {
        free(obj);
    }
}

game_object_t* find_object_at(const game_state_t* state, position_t pos)
{
    for (int i = 0; i < state->object_count; i++) {
        if (state->objects[i]->pos.row == pos.row && state->objects[i]->pos.col == pos.col) {
            return state->objects[i];
        }
    }
    return NULL;
}

bool is_position_valid(position_t pos)
{
    return pos.row >= 0 && pos.row < MAP_HEIGHT && pos.col >= 0 && pos.col < MAP_WIDTH;
}

bool is_position_empty(const game_state_t* state, position_t pos)
{
    return is_position_valid(pos) && find_object_at(state, pos) == NULL;
}

void add_message(game_state_t* state, const char* message)
{
    if (state->message_count < MAX_MESSAGES) {
        strncpy(state->messages[state->message_count], message, MESSAGE_LENGTH - 1);
        state->messages[state->message_count][MESSAGE_LENGTH - 1] = '\0';
        state->message_count++;
    } else {
        // Shift messages up
        for (int i = 0; i < MAX_MESSAGES - 1; i++) {
            strncpy(state->messages[i], state->messages[i + 1], MESSAGE_LENGTH);
        }
        strncpy(state->messages[MAX_MESSAGES - 1], message, MESSAGE_LENGTH - 1);
        state->messages[MAX_MESSAGES - 1][MESSAGE_LENGTH - 1] = '\0';
    }
}