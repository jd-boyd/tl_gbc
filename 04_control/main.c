#include <gb/gb.h>
#include <stdint.h>
#include <stdbool.h>

#include "hw_tiles.h"

struct pos {
    uint8_t x;
    uint8_t y;
};

struct vel {
    int8_t dx;
    int8_t dy;
};

void position_hello(const struct pos * p) {
    move_sprite(0, p->x, p->y);
    move_sprite(1, p->x, p->y+8);
    move_sprite(2, p->x, p->y+16);
    move_sprite(3, p->x, p->y+24);
    move_sprite(4, p->x, p->y+32);
}


void position_world(const struct pos * p) {
    move_sprite(5, p->x, p->y);
    move_sprite(6, p->x, p->y+8);
    move_sprite(7, p->x, p->y+16);
    move_sprite(8, p->x, p->y+24);
    move_sprite(9, p->x, p->y+32);
}

inline void move_pos(struct pos * p, const struct vel * v) {
        p->x += v->dx;
        p->y += v->dy;
}

inline void init_sound(void) {
    NR52_REG = 0x80; // is 1000 0000 in binary and turns on sound
    NR50_REG = 0x77; // sets the volume for both left and right channel just set to max 0x77
    NR51_REG = 0xFF; // is 1111 1111 in binary, select which chanels we want to use in this case all of them. One bit for the L one bit for the R of all four channels
}

inline void bounce_beep(void) {
    // Values taken from fidling with sound example program
    NR10_REG = 0x69;
    NR11_REG = 0x42;
    NR12_REG = 0x53;
    // Last two are frequency, LSB first
    NR13_REG = 0x77;
    NR14_REG = 0x86;
}

const uint8_t ball_sprite = 10;

const uint8_t BALL_MIN_X = 8;
const uint8_t BALL_MAX_X = 160;

const uint8_t BALL_MIN_Y = 8;
const uint8_t BALL_MAX_Y = 160;

const uint8_t PADDLE_MIN_Y = 16;
const uint8_t PADDLE_MAX_Y = 160 - (5*8);
const uint8_t BTN_INC = 2;

void main(void)
{
    init_sound();

    set_sprite_data(0, 32, HWTiles);
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

    struct pos h_pos = {16U, 78U};
    struct pos w_pos = {154U, 86U};

    struct pos ball_pos = {80U, 80U};
    struct vel ball_v = {2, 1};

    position_hello(&h_pos);
    position_world(&w_pos);
    move_sprite(ball_sprite, ball_pos.x, ball_pos.y);

    SHOW_SPRITES;

    // Loop forever
    while(1) {
		// Game main loop processing goes here
        bool should_beep = false;
        position_hello(&h_pos);
        position_world(&w_pos);

        uint8_t keys;
        keys = joypad();
        if (keys & J_B && w_pos.y > 16) {
            w_pos.y -= BTN_INC;
        }
        if (keys & J_A && w_pos.y < PADDLE_MAX_Y) {
            w_pos.y += BTN_INC;
        }

        if (keys & J_UP && h_pos.y > 16) {
            h_pos.y -= BTN_INC;
        }
        if (keys & J_DOWN && h_pos.y < PADDLE_MAX_Y) {
            h_pos.y += BTN_INC;
        }

        if (ball_pos.x + ball_v.dx >= BALL_MAX_X
            || ball_pos.x + ball_v.dx < BALL_MIN_X ) {
            ball_v.dx *= -1;
            should_beep = true;
        }

        if (ball_pos.y + ball_v.dy >= BALL_MAX_Y
            || ball_pos.y + ball_v.dy < BALL_MIN_Y ) {
            ball_v.dy *= -1;
            should_beep = true;
        }

        move_pos(&ball_pos, &ball_v);
        move_sprite(ball_sprite, ball_pos.x, ball_pos.y);


        if (should_beep) {
            bounce_beep();
        }

		// Done processing, yield CPU and wait for start of next frame
        vsync();
    }
}
