#include <gb/gb.h>
#include <stdint.h>

#include "hw_tiles.h"


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

    move_sprite(0, 88, 78);
    move_sprite(1, 96, 78);
    move_sprite(2, 104, 78);
    move_sprite(3, 112, 78);
    move_sprite(4, 120, 78);


    move_sprite(5, 88, 86);
    move_sprite(6, 96, 86);
    move_sprite(7, 104, 86);
    move_sprite(8, 112, 86);
    move_sprite(9, 120, 86);

    SHOW_SPRITES;


    // Loop forever
    while(1) {


		// Game main loop processing goes here


		// Done processing, yield CPU and wait for start of next frame
        vsync();
    }
}
