// #!/run/current-system/sw/bin/tcc -run

// Copyright (C) 2023-2025 Roy Pfund. All rights reserved.
//
// Permission is  hereby  granted,  free  of  charge,  to  any  person
// obtaining a copy of  this  software  and  associated  documentation
// files  (the  "Software"),  to  deal   in   the   Software   without
// restriction, including without limitation the rights to use,  copy,
// modify, merge, publish, distribute, sublicense, and/or sell  copies
// of the Software, and to permit persons  to  whom  the  Software  is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and  this  permission  notice  shall  be
// included in all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT  WARRANTY  OF  ANY  KIND,
// EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES  OF
// MERCHANTABILITY,   FITNESS   FOR   A   PARTICULAR    PURPOSE    AND
// NONINFRINGEMENT.  IN  NO  EVENT  SHALL  THE  AUTHORS  OR  COPYRIGHT
// OWNER(S) BE LIABLE FOR  ANY  CLAIM,  DAMAGES  OR  OTHER  LIABILITY,
// WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING  FROM,
// OUT OF OR IN CONNECTION WITH THE  SOFTWARE  OR  THE  USE  OR  OTHER
// DEALINGS IN THE SOFTWARE.

/* build, run, and destroy with:
gcc -m64 -O2 -std=gnu99 CATest.c -o CATest && ./CATest && rm ./CATest

or just uncomment the tcc shebang
*/

// Annex B (informative)_Library_summary____________________ [p419N1256]
// assert inttypes signal  stdlib complex iso646 stdarg string
// ctype  limits   stdbool tgmath errno   locale stddef time
// fenv   math     stdint  wchar  float   setjmp stdio  wctype
#include "annexb.h" // ^^ includes the above .h files ^^     [p419N1256]
// ___________________________printf() directives provided by inttypes.h
// Hex      // %02"PRIX8" // %04"PRIX16" // %08"PRIX32" // %016"PRIX64"
// Signed   // %"PRIi8"   // %"PRIi16"   // %"PRIi32"   // %"PRIi64"
// Unsigned // %"PRIu8"   // %"PRIu16"   // %"PRIu32"   // %"PRIu64"
// Float    //  XXXXXX    //   XXXXXX    //   %.6E      // %.15E
#include "eval_ops.h"
#include "CALLDeck.h"
#include <ncurses.h>

typedef struct { uint8_t x; uint8_t y; } coord;
DEFINE_CALLDECK(coord, 255)

// semantic aliases (no new structs)
typedef coord SnakeSegment;
typedef coord Apple;
typedef coord SpaceCoord;

// deck instances
LLDeck_CA_coord_255 *snake;
LLDeck_CA_coord_255 *apples;
LLDeck_CA_coord_255 *emptyspaces;

/* push/pop segments and apples to queues with:
    popStart_CALLDECK_coord_255(&SomeSegment, &snake));
    pushStart_CALLDECK_coord_255(&SomeSegment, &snake);
    popStart_CALLDECK_coord_255(&SomeSegment, &snake));
    pushStart_CALLDECK_coord_255(&SomeSegment, &snake);

for (uint16_t i = 0; i < snake_length; i++) {
    SnakeSegment seg;
    popStart_CALLDECK_coord_255(&seg, &snake);
    // --- Add your segment-handling code here ---
    pushEnd_CALLDECK_coord_255(&seg, &snake);
}

for (uint16_t i = 0; i < apple_count; i++) {
    Apple a;
    popStart_CALLDECK_Apple_255(&a, &apples);
    if (collision){
        apple_count--;
    } else pushEnd_CALLDECK_Apple_255(&a, &apples);
}
*/

const uint8_t framerate = 60;
const uint8_t snakechar = '#';
const uint8_t applechar = '@';
const uint8_t emptychar = ' ';
const uint8_t width = 20;
const uint8_t height = 20;
const uint8_t moves_per_second = 8;
const uint32_t apple_spawn_interval = 60;  // 1 second at 60fps for testing (was 300 for 5 seconds)

// Direction control variables
int8_t direction_x = 1;  // Start moving right
int8_t direction_y = 0;

void handle_input(int8_t *direction_x, int8_t *direction_y);
void sleepframetime() {
    nanosleep(&(struct timespec){ .tv_sec = 0, .tv_nsec = 1000000000L / framerate }, NULL);
}

int main(int argc, char **argv) {

    // Initialize random seed for apple placement
    srand(time(NULL));

    // Initialize ncurses
    initscr();
    cbreak();           // Disable line buffering
    noecho();           // Don't echo pressed keys
    keypad(stdscr, TRUE); // Enable arrow keys
    nodelay(stdscr, TRUE); // Non-blocking input
    curs_set(0);        // Hide cursor

    // allocate empty‑space deck once
    static LLDeck_CA_coord_255 *emptyspaces = NULL;
    if (!emptyspaces) emptyspaces = zalloc(sizeof(LLDeck_CA_coord_255));

    // Init snake deck and apple deck
    LLDeck_CA_coord_255 *snake  = zalloc(sizeof(LLDeck_CA_coord_255));
    LLDeck_CA_coord_255 *apples = zalloc(sizeof(LLDeck_CA_coord_255));

    // Start with a single head in the center
    coord snake_seg_head = { width / 2, height / 2 };
    pushStart_CALLDECK_coord_255(&snake_seg_head, &snake);

    // Track snake length and apple count manually since CALLDECK doesn't expose size
    uint16_t snake_length = 1;
    uint16_t apple_count = 0;
    uint8_t frame_count = 0;
    uint32_t apple_spawn_timer = 0;  // Timer for apple spawning
    uint16_t space_count = 0;
    uint8_t *snake_world = malloc(width * height);
    if (!snake_world) { endwin(); return 1; } // exit if error

    SnakeSegment initial_head = { width / 2, height / 2 };
    snake_world[initial_head.y * width + initial_head.x] = 1;
    
    for (;;) {
        // Handle input for direction changes
        handle_input(&direction_x, &direction_y);

        // --- NEW UPDATE‑WORLD SECTION USING UNIFIED coord TYPE ---

        // update world only on certain frames
        if (frame_count >= framerate / moves_per_second) {
            frame_count = 0;

            memset(snake_world, emptychar, width * height);
            coord snake_head_current;
            if (popStart_CALLDECK_coord_255(&snake_head_current, &snake)) {

                // restore head
                pushStart_CALLDECK_coord_255(&snake_head_current, &snake);

                // compute new head
                coord snake_head_new = snake_head_current;
                snake_head_new.x = (snake_head_new.x + direction_x + width) % width;
                snake_head_new.y = (snake_head_new.y + direction_y + height) % height;

                bool ate_apple = false;
                for (uint16_t i = 0; i < apple_count; i++) {
                    coord apple_coord;
                    popStart_CALLDECK_coord_255(&apple_coord, &apples);
                    // if (apple_coord == snake_head_new) ate_apple = true;
                    if (memcmp(&apple_coord, &snake_head_new, sizeof(coord)) == 0) ate_apple = true;
                    pushEnd_CALLDECK_coord_255(&apple_coord, &apples);
                }
                // push new head
                pushStart_CALLDECK_coord_255(&snake_head_new, &snake);

                if (ate_apple) {
                    snake_length++;
                    apple_count--;
                } else {
                    popEnd_CALLDECK_coord_255(&snake_head_new, &snake);
                }
            }

            // clear board
            for (uint8_t y = 0; y < height; ++y)
                for (uint8_t x = 0; x < width; ++x)
                    snake_world[y * width + x] = emptychar;

            // draw snake
            for (uint16_t i = 0; i < snake_length; i++) {
                coord snake_seg;
                popStart_CALLDECK_coord_255(&snake_seg, &snake);
                snake_world[snake_seg.y * width + snake_seg.x] = snakechar;
                pushEnd_CALLDECK_coord_255(&snake_seg, &snake);
            }

            // draw apples
            for (uint16_t i = 0; i < apple_count; i++) {
                coord apple_coord;
                popStart_CALLDECK_coord_255(&apple_coord, &apples);
                snake_world[apple_coord.y * width + apple_coord.x] = applechar;
                pushEnd_CALLDECK_coord_255(&apple_coord, &apples);
            }

            // rebuild empty‑space list
            space_count = 0;
            coord space_coord_tmp;
            while (popStart_CALLDECK_coord_255(&space_coord_tmp, &emptyspaces)) { /* clear */ }

            for (uint8_t y = 0; y < height; ++y) {
                for (uint8_t x = 0; x < width; ++x) {
                    if (snake_world[y * width + x] == emptychar) {
                        coord space_coord = { x, y };
                        pushEnd_CALLDECK_coord_255(&space_coord, &emptyspaces);
                        space_count++;
                    }
                }
            }

            // spawn apple
            apple_spawn_timer++;
            if (apple_spawn_timer >= moves_per_second && space_count > 0) {

                uint16_t r = rand() % space_count;

                coord chosen_space;
                for (uint16_t i = 0; i <= r; i++) {
                    popStart_CALLDECK_coord_255(&chosen_space, &emptyspaces);
                    pushEnd_CALLDECK_coord_255(&chosen_space, &emptyspaces);
                }

                popStart_CALLDECK_coord_255(&chosen_space, &emptyspaces);
                pushStart_CALLDECK_coord_255(&chosen_space, &apples);

                apple_count++;
                space_count--;
                apple_spawn_timer = 0;
            }
        }

        // draw board
        // clear();
        erase();
        for (uint8_t y = 0; y < height; ++y)
            for (uint8_t x = 0; x < width; ++x)
                mvaddch(y, x, snake_world[y * width + x]);

        mvprintw(height + 1, 0,
                 "Apples: %d  Snake: %d  Timer: %d  Dir:(%d,%d)",
                 apple_count, snake_length, apple_spawn_timer,
                 direction_x, direction_y);

        refresh();

        ++frame_count;
        sleepframetime();
    }

    // Cleanup ncurses
    endwin();
    free(snake_world);
    return 0;
}

// Input handling function to process arrow key presses
void handle_input(int8_t *direction_x, int8_t *direction_y) {
    int ch = getch();
    
    if (ch != ERR) {  // Key was pressed
        int8_t new_dx = *direction_x;
        int8_t new_dy = *direction_y;
        
        switch (ch) {
            case KEY_UP:
                new_dx = 0;
                new_dy = -1;
                break;
            case KEY_DOWN:
                new_dx = 0;
                new_dy = 1;
                break;
            case KEY_LEFT:
                new_dx = -1;
                new_dy = 0;
                break;
            case KEY_RIGHT:
                new_dx = 1;
                new_dy = 0;
                break;
            default:
                return; // Ignore other keys
        }
        
        // Direction change validation - prevent reverse movement
        // Don't allow moving in the exact opposite direction
        if (new_dx != -*direction_x || new_dy != -*direction_y) {
            *direction_x = new_dx;
            *direction_y = new_dy;
        }
    }
}

