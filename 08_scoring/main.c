#include <gb/gb.h>
#include <stdint.h>
#include <stdbool.h>
#include <rand.h>

#include "sound.h"

#include "hw_tiles.h"
#include "hw_bg.h"

typedef struct  {
    uint8_t x;
    uint8_t y;
} Point;

typedef struct {
    int8_t dx;
    int8_t dy;
} Vec;

typedef struct {
    Point origin;
    Point size;
} Obj;

void move_hello(const Point * p) {
    move_sprite(0, p->x, p->y);
    move_sprite(1, p->x, p->y+8);
    move_sprite(2, p->x, p->y+16);
    move_sprite(3, p->x, p->y+24);
    move_sprite(4, p->x, p->y+32);
}


void move_world(const Point * p) {
    move_sprite(5, p->x, p->y);
    move_sprite(6, p->x, p->y+8);
    move_sprite(7, p->x, p->y+16);
    move_sprite(8, p->x, p->y+24);
    move_sprite(9, p->x, p->y+32);
}

void hide_start(void) { // Sprites at y=0 or y=8 are hidden.
    move_sprite(11, 65U, 0U); //S
    move_sprite(12, 71U, 0U); //T
    move_sprite(13, 77U, 0U); //A
    move_sprite(14, 83U, 0U); //R
    move_sprite(15, 89U, 0U); //T
}


inline void move_point(Point * p, const Vec * v) {
    p->x += v->dx;
    p->y += v->dy;
}

bool checkcollisions(const Obj* one, Obj* two){
    return (one->origin.x >= two->origin.x && one->origin.x <= two->origin.x + two->size.x) && (one->origin.y >= two->origin.y && one->origin.y <= two->origin.y + two->size.y) || (two->origin.x >= one->origin.x && two->origin.x <= one->origin.x + one->size.x) && (two->origin.y >= one->origin.y && two->origin.y <= one->origin.y + one->size.y);
}



const uint8_t ball_sprite = 10;

const uint8_t BALL_MIN_X = 8;
const uint8_t BALL_MAX_X = 160;

const uint8_t BALL_MIN_Y = 16;
const uint8_t BALL_MAX_Y = 160;

const uint8_t PADDLE_MIN_Y = 16;
const uint8_t PADDLE_MAX_Y = 160 - (5*8);
const uint8_t BTN_INC = 2;

uint16_t seed;

void setup_rand(void) {
    seed = LY_REG;
    seed |= (uint16_t)DIV_REG << 8;
    initrand(seed);
}

bool get_rand_bit(void) {
    UINT8 r = ((UINT8)rand()) % 2U;
    if (r == 0) return false;
    else return true;
}

void main(void)
{
    init_sound();

    set_sprite_data(0, 28, HWTiles);

    set_sprite_tile(0, 1); //H
    set_sprite_tile(1, 2); //E
    set_sprite_tile(2, 3); //L
    set_sprite_tile(3, 3); //L
    set_sprite_tile(4, 4); //O

    set_sprite_tile(5, 5); //W
    set_sprite_tile(6, 4); //O
    set_sprite_tile(7, 6); //R
    set_sprite_tile(8, 3); //L
    set_sprite_tile(9, 7); //D

    set_sprite_tile(ball_sprite, 18); // Ball

    set_sprite_tile(11, 25); //S
    set_sprite_tile(12, 26); //T
    set_sprite_tile(13, 27); //A
    set_sprite_tile(14, 6); //R
    set_sprite_tile(15, 26); //T

    move_sprite(11, 65U, 72U); //S
    move_sprite(12, 71U, 72U); //T
    move_sprite(13, 77U, 72U); //A
    move_sprite(14, 83U, 72U); //R
    move_sprite(15, 89U, 72U); //T

    // Tiles 8-17 are 1-9,0
    set_sprite_tile(16, 17);
    set_sprite_tile(17, 17);
    set_sprite_tile(18, 17);

    set_sprite_tile(19, 17);
    set_sprite_tile(20, 17);
    set_sprite_tile(21, 17);

    move_sprite(16, 8U, 16U);
    move_sprite(17, 14U, 16U);
    move_sprite(18, 20U, 16U);

    move_sprite(19, 148U, 16U);
    move_sprite(20, 154U, 16U);
    move_sprite(21, 160U, 16U);


    set_bkg_data(0, 32, HWTiles);
    set_bkg_tiles(0, 0, 20, 18, HW_BG_DATA);

    Obj hello_obj = {{16U, 68U}, {8U, 40U}};
    Obj world_obj = {{154U, 68U}, {8U, 40U}};

    Obj hello_gate_obj = {{0U, 48U}, {8U, 48U}};
    Obj world_gate_obj = {{160U, 48U}, {8U, 48U}};

    Obj ball_obj = {{80U, 80U}, {8U, 8U}};
    Vec ball_v = {2, 1};

    move_hello(&(hello_obj.origin));
    move_world(&(world_obj.origin));
    move_sprite(ball_sprite, ball_obj.origin.x, 0);

    SHOW_SPRITES;
    SHOW_BKG;
    DISPLAY_ON;

    uint8_t game_mode = 0; // 0 = start, 1 = run

    // Loop forever
    while(1) {

        uint8_t keys;
        keys = joypad();

        if (game_mode == 0) {
            if (keys & J_START) {
                game_mode = 1;
                hide_start();

                setup_rand();
                if (get_rand_bit()) {
                    ball_v.dy *= -1;
                }

                if (get_rand_bit()) {
                    ball_v.dx *= -1;
                }
                continue;
            }
            vsync();
            continue;
        }

        if (keys & J_B && world_obj.origin.y > 16) {
            world_obj.origin.y -= BTN_INC;
        }
        if (keys & J_A && world_obj.origin.y < PADDLE_MAX_Y) {
            world_obj.origin.y += BTN_INC;
        }

        if (keys & J_UP && hello_obj.origin.y > 16) {
            hello_obj.origin.y -= BTN_INC;
        }
        if (keys & J_DOWN && hello_obj.origin.y < PADDLE_MAX_Y) {
            hello_obj.origin.y += BTN_INC;
        }
        move_hello(&(hello_obj.origin));
        move_world(&(world_obj.origin));

		// Game main loop processing goes here
        bool should_paddle_beep = false;
        bool should_wall_beep = false;


        if (ball_obj.origin.x + ball_v.dx >= BALL_MAX_X
            || ball_obj.origin.x + ball_v.dx < BALL_MIN_X ) {
            ball_v.dx *= -1;
            should_wall_beep = true;
        }

        if (ball_obj.origin.y + ball_v.dy >= BALL_MAX_Y
            || ball_obj.origin.y + ball_v.dy < BALL_MIN_Y ) {
            ball_v.dy *= -1;
            should_wall_beep = true;
        }

        if(checkcollisions(&hello_obj, &ball_obj)) {
            should_paddle_beep = true;
            ball_v.dx *= -1;
            if (get_rand_bit()) {
                ball_v.dy *= -1;
            }
        }

        if(checkcollisions(&world_obj, &ball_obj)) {
            should_paddle_beep = true;
            ball_v.dx *= -1;
            if (get_rand_bit()) {
                ball_v.dy *= -1;
            }
        }

        move_point(&ball_obj.origin, &ball_v);
        move_sprite(ball_sprite, ball_obj.origin.x, ball_obj.origin.y);

        if (should_paddle_beep) {
            paddle_bounce_beep();
        }


        if (should_wall_beep) {
            //wall_bounce_beep();
        }

		// Done processing, yield CPU and wait for start of next frame
        vsync();
    }
}
