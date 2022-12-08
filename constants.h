#include "game_app_icons.h"

#define TAG "GameTemplate" // Change this to your app name

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define HERO_SIZE 10

#define HERO_MAX_X SCREEN_WIDTH - HERO_SIZE
#define HERO_MAX_Y SCREEN_HEIGHT - HERO_SIZE

typedef enum {
    EventTypeTick,
    EventTypeInput,
} EventType;

typedef struct {
    EventType type;
    InputEvent input;
} GameEvent;

typedef struct {
    u_int8_t hero_x;
    u_int8_t hero_y;

    bool fire;
    bool left;
    bool right;
    bool up;
    bool down;
} GameState;

void game_init(GameState* const state) {
    // Set initial values for GameState here

    // Hero position at the center of the screen
    state->hero_x = (HERO_MAX_X) / 2;
    state->hero_y = (HERO_MAX_Y) / 2;
}