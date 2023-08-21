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
    move_sprite(1, p->x+8, p->y);
    move_sprite(2, p->x+16, p->y);
    move_sprite(3, p->x+24, p->y);
    move_sprite(4, p->x+32, p->y);
}


void position_world(const struct pos * p) {
    move_sprite(5, p->x, p->y);
    move_sprite(6, p->x+8, p->y);
    move_sprite(7, p->x+16, p->y);
    move_sprite(8, p->x+24, p->y);
    move_sprite(9, p->x+32, p->y);
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

const uint8_t MAX_X = 150;
const uint8_t MAX_Y = 152;
void main(void)
{
    init_sound();

    set_sprite_data(0, 8, HWTiles);
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

    struct pos h_pos = {88U, 78U};

    //uint8_t h_x = 88;
    //uint8_t h_y = 68;
    int8_t h_dx = 2;
    int8_t h_dy = 1;

    struct pos w_pos = {88U, 86U};
    //uint8_t w_x = 88;
    //uint8_t w_y = 86;
    int8_t w_dx = -1;
    int8_t w_dy = 2;

    position_hello(&h_pos);
    position_world(&w_pos);

    SHOW_SPRITES;

    // Loop forever
    while(1) {
		// Game main loop processing goes here
        bool should_beep = false;
        position_hello(&h_pos);
        position_world(&w_pos);

        if (h_pos.x + h_dx >= MAX_X
            || h_pos.x + h_dx < 0 ) {
            h_dx *= -1;
            should_beep = true;
        }

        if (h_pos.y + h_dy >= MAX_Y
            || h_pos.y + h_dy < 1 ) {
            h_dy *= -1;
            should_beep = true;
        }

        if (w_pos.x + w_dx >= MAX_X
            || w_pos.x + w_dx < 0 ) {
            w_dx *= -1;
            should_beep = true;
        }

        if (w_pos.y + w_dy >= MAX_Y
            || w_pos.y + w_dy < 1 ) {
            w_dy *= -1;
            should_beep = true;
        }

        h_pos.x += h_dx;
        h_pos.y += h_dy;

        w_pos.x += w_dx;
        w_pos.y += w_dy;

        if (should_beep) {
            bounce_beep();
        }

		// Done processing, yield CPU and wait for start of next frame
        vsync();
    }
}
