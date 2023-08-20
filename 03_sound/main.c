#include <gb/gb.h>
#include <stdint.h>

#include "hw_tiles.h"

void position_hello(int x, int y) {
    move_sprite(0, x, y);
    move_sprite(1, x+8, y);
    move_sprite(2, x+16, y);
    move_sprite(3, x+24, y);
    move_sprite(4, x+32, y);

}

void position_world(int x, int y) {
    move_sprite(5, x, y);
    move_sprite(6, x+8, y);
    move_sprite(7, x+16, y);
    move_sprite(8, x+24, y);
    move_sprite(9, x+32, y);
}

void main(void)
{
    NR52_REG = 0x80; // is 1000 0000 in binary and turns on sound
    NR50_REG = 0x77; // sets the volume for both left and right channel just set to max 0x77
    NR51_REG = 0xFF; // is 1111 1111 in binary, select which chanels we want to use in this case all of them. One bit for the L one bit for the R of all four channels


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

    int h_x = 88;
    int h_y = 68;
    int h_dx = 2;
    int h_dy = 1;

    int w_x = 88;
    int w_y = 86;
    int w_dx = -1;
    int w_dy = 2;

    position_hello(h_x, h_y);
    position_world(w_x, w_y);

    SHOW_SPRITES;




#define MAX_X 150
#define MAX_Y 152

    // Loop forever
    while(1) {
		// Game main loop processing goes here
        int should_beep = 0;
        position_hello(h_x, h_y);
        position_world(w_x, w_y);

        if (h_x + h_dx >= MAX_X
            || h_x + h_dx < 0 ) {
            h_dx *= -1;
            should_beep = 1;
        }

        if (h_y + h_dy >= MAX_Y
            || h_y + h_dy < 1 ) {
            h_dy *= -1;
            should_beep = 1;
        }

        if (w_x + w_dx >= MAX_X
            || w_x + w_dx < 0 ) {
            w_dx *= -1;
            should_beep = 1;
        }

        if (w_y + w_dy >= MAX_Y
            || w_y + w_dy < 1 ) {
            w_dy *= -1;
            should_beep = 1;
        }

        h_x += h_dx;
        h_y += h_dy;

        w_x += w_dx;
        w_y += w_dy;

        if (should_beep) {
            // Values taken from fidling with sound example program
            NR10_REG = 0x69;
            NR11_REG = 0x42;
            NR12_REG = 0x53;
            // Last two are frequency, LSB first
            NR13_REG = 0x77;
            NR14_REG = 0x86;

        }

		// Done processing, yield CPU and wait for start of next frame
        vsync();
    }
}
