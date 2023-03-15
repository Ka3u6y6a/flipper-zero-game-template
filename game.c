#include <furi.h>
#include <gui/gui.h>
#include <input/input.h>
#include "constants.h"

static void game_update(GameState* game_state) {
    // update position
    if(game_state->left && game_state->hero_x > 0) {
        game_state->hero_x--;
    } else if(game_state->right && game_state->hero_x < HERO_MAX_X) {
        game_state->hero_x++;
    } else if(game_state->up && game_state->hero_y > 0) {
        game_state->hero_y--;
    } else if(game_state->down && game_state->hero_y < HERO_MAX_X) {
        game_state->hero_y++;
    }

    // Update other game logic here

    if(game_state->fire) {
        // Spawn bullets here, for example
    }
}

// draw here ui
static void draw_callback(Canvas* canvas, void* ctx) {
    furi_assert(ctx);

    const GameState* game_state = ctx;
    furi_mutex_acquire(game_state->mutex, FuriWaitForever);

    if(game_state == NULL) {
        return;
    }

    // Draw ui elements here

    // Example
    // draw hero at his position
    canvas_draw_icon(canvas, game_state->hero_x, game_state->hero_y, &I_hero);
    // draw some text
    canvas_draw_str_aligned(
        canvas, SCREEN_WIDTH / 2, 5, AlignCenter, AlignCenter, "<Press arrow button>");

    // Draw end, release mutex
    furi_mutex_release(game_state->mutex);
}

static void input_callback(InputEvent* input_event, FuriMessageQueue* event_queue) {
    furi_assert(event_queue);

    GameEvent event = {.type = EventTypeInput, .input = *input_event};
    furi_message_queue_put(event_queue, &event, FuriWaitForever);
}

static void timer_callback(FuriMessageQueue* event_queue) {
    furi_assert(event_queue);

    GameEvent event = {.type = EventTypeTick};
    furi_message_queue_put(event_queue, &event, 0);
}

int32_t game_main() {
    // Create event queue for 8 elements of GameEvent type size
    FuriMessageQueue* event_queue = furi_message_queue_alloc(8, sizeof(GameEvent));

    // Create game state
    GameState* game_state = malloc(sizeof(GameState));
    // Init game with start values
    game_init(game_state);

    game_state->mutex = furi_mutex_alloc(FuriMutexTypeNormal);
    if(!game_state->mutex) {
        FURI_LOG_E(TAG, "cannot create mutex\r\n");
        free(game_state);
        return 255;
    }

    // Set system callbacks
    ViewPort* view_port = view_port_alloc();
    view_port_draw_callback_set(view_port, draw_callback, game_state);
    view_port_input_callback_set(view_port, input_callback, event_queue);

    // Set timer
    FuriTimer* timer = furi_timer_alloc(timer_callback, FuriTimerTypePeriodic, event_queue);
    furi_timer_start(timer, furi_kernel_get_tick_frequency() / 12);

    // Open GUI and register view_port
    Gui* gui = furi_record_open(RECORD_GUI);
    gui_add_view_port(gui, view_port, GuiLayerFullscreen);

    GameEvent event;
    // Game loop
    for(bool processing = true; processing;) {
        FuriStatus event_status = furi_message_queue_get(event_queue, &event, 100);
        furi_mutex_acquire(game_state->mutex, FuriWaitForever);

        if(event_status == FuriStatusOk) {
            // Game update event
            if(event.type == EventTypeTick) {
                game_update(game_state);
            }

            // Key press events
            if(event.type == EventTypeInput) {
                if(event.input.type == InputTypePress) {
                    if(event.input.key == InputKeyOk) {
                        game_state->fire = true;
                    } else if(event.input.key == InputKeyUp) {
                        game_state->up = true;
                    } else if(event.input.key == InputKeyDown) {
                        game_state->down = true;
                    } else if(event.input.key == InputKeyRight) {
                        game_state->right = true;
                    } else if(event.input.key == InputKeyLeft) {
                        game_state->left = true;
                    }
                }
                if(event.input.type == InputTypeRelease) {
                    if(event.input.key == InputKeyOk) {
                        game_state->fire = false;
                    } else if(event.input.key == InputKeyUp) {
                        game_state->up = false;
                    } else if(event.input.key == InputKeyDown) {
                        game_state->down = false;
                    } else if(event.input.key == InputKeyRight) {
                        game_state->right = false;
                    } else if(event.input.key == InputKeyLeft) {
                        game_state->left = false;
                    }
                }
                if(event.input.key == InputKeyBack) {
                    processing = false;
                }
            }
        } else {
            FURI_LOG_D(TAG, "osMessageQueue: event timeout");
        }

        view_port_update(view_port);
        furi_mutex_release(game_state->mutex);
    }

    // Clear resources
    furi_timer_free(timer);
    furi_message_queue_free(event_queue);
    view_port_enabled_set(view_port, false);
    gui_remove_view_port(gui, view_port);
    view_port_free(view_port);
    furi_record_close(RECORD_GUI);
    furi_mutex_free(game_state->mutex);
    free(game_state);

    return 0;
}