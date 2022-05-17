/**
 * LCD Alarm project
 * This source followed by General Public License 3.0v
 */

#include <LiquidCrystal.h>

#define PIN_BUTTON 9
#define PIN_AUTOPLAY 10
#define PIN_REWRITE 11
#define PIN_CONTRAST 12

#define SPRITE_RUN1 1
#define SPRITE_RUN2 2
#define SPRITE_JUMP 3
#define SPRITE_JUMP_UPPER '.'
#define SPRITE_JUMP_LOWER 4
#define SPRITE_TERRAIN_EMPTY ' '
#define SPRITE_TERRAIN_SOLID 5
#define SPRITE_TERRAIN_SOLID_RIGHT 6
#define SPRITE_TERRAIN_SOLID_LEFT 7

#define HERO_HORIZONTAL_POSITION 1

#define TERRAIN_WIDTH 16
#define TERRAIN_EMPTY 0
#define TERRAIN_LOWER_BLOCK 1
#define TERRAIN_UPPER_BLOCK 2

#define HERO_POSITION_OFF 0
#define HERO_POSITION_RUN_LOWER_1 1
#define HERO_POSITION_RUN_LOWER_2 2
#define HERO_POSITION_JUMP_1 3
#define HERO_POSITION_JUMP_2 4
#define HERO_POSITION_JUMP_3 5
#define HERO_POSITION_JUMP_4 6
#define HERO_POSITION_JUMP_5 7
#define HERO_POSITION_JUMP_6 8
#define HERO_POSITION_JUMP_7 9
#define HERO_POSITION_JUMP_8 10
#define HERO_POSITION_RUN_UPPER_1 11
#define HERO_POSITION_RUN_UPPER_2 12

LiquidCrystal lcd = LiquidCrystal(2, 3, 4, 5, 6, 7);

static char terrain_upper[TERRAIN_WIDTH + 1];
static char terrain_lower[TERRAIN_WIDTH + 1];
static bool button_pushed = false;

void initialize_graphic() {
    static byte *g = {
        // RUN POSITION 1
        B01100,
        B01100,
        B00000,
        B01110,
        B11100,
        B01100,
        B11010,
        B10011,

        // RUN POSITION 2
        B01100,
        B01100,
        B00000,
        B01100,
        B01100,
        B01100,
        B01100,
        B01110,

        // JUMP
        B01100,
        B01100,
        B00000,
        B11110,
        B01101,
        B11111,
        B10000,
        B00000,

        // JUMP LOWER
        B11110,
        B01101,
        B11111,
        B10000,
        B00000,
        B00000,
        B00000,
        B00000,
        
        // GROUND
        B11111,
        B11111,
        B11111,
        B11111,
        B11111,
        B11111,
        B11111,
        B11111,

        // GROUND RIGHT
        B00011,
        B00011,
        B00011,
        B00011,
        B00011,
        B00011,
        B00011,
        B00011,

        // GROUND LEFT
        B11000,
        B11000,
        B11000,
        B11000,
        B11000,
        B11000,
        B11000,
        B11000
    };

    for (int i = 0; i < 7; ++i) {
        lcd.createChar(i + 1, &g[i * 8]);
    }

    for (int i = 0; i < 7; ++i) {
        terrain_upper[i] = SPRITE_TERRAIN_EMPTY;
        terrain_lower[i] = SPRITE_TERRAIN_EMPTY;
    }
}

void advance_terrain(char *terrain, byte new_terrain) {
    for (int i = 0; i < TERRAIN_WIDTH; ++i) {
        char current = terrain[i];
        char next = (i == TERRAIN_WIDTH - 1) ? new_terrain : terrain[i + 1];
    }
}

void setup() {
}

void loop() {
}