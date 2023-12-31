#include <gb/gb.h>
#include <stdint.h>
#include <stdbool.h>

#include "hw_tiles.h"

void position_hello(uint8_t x, uint8_t y) {
    move_sprite(0, x, y);
    move_sprite(1, x+8, y);
    move_sprite(2, x+16, y);
    move_sprite(3, x+24, y);
    move_sprite(4, x+32, y);

}


void position_world(uint8_t x, uint8_t y) {
    move_sprite(5, x, y);
    move_sprite(6, x+8, y);
    move_sprite(7, x+16, y);
    move_sprite(8, x+24, y);
    move_sprite(9, x+32, y);
}

void main(void)
{

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

    uint8_t h_x = 88;
    uint8_t h_y = 68;
    int8_t h_dx = 2;
    int8_t h_dy = 1;

    uint8_t w_x = 88;
    uint8_t w_y = 86;
    int8_t w_dx = -1;
    int8_t w_dy = 2;

    position_hello(h_x, h_y);
    position_world(w_x, w_y);

    SHOW_SPRITES;

#define MAX_X 150
#define MAX_Y 152

    // Loop forever
    while(1) {
		// Game main loop processing goes here

        position_hello(h_x, h_y);
        position_world(w_x, w_y);

        if (h_x + h_dx >= MAX_X
            || h_x + h_dx < 0 ) {
            h_dx *= -1;
        }

        if (h_y + h_dy >= MAX_Y
            || h_y + h_dy < 1 ) {
            h_dy *= -1;
        }

        if (w_x + w_dx >= MAX_X
            || w_x + w_dx < 0 ) {
            w_dx *= -1;
        }

        if (w_y + w_dy >= MAX_Y
            || w_y + w_dy < 1 ) {
            w_dy *= -1;
        }

        h_x += h_dx;
        h_y += h_dy;

        w_x += w_dx;
        w_y += w_dy;

		// Done processing, yield CPU and wait for start of next frame
        vsync();
    }
}
