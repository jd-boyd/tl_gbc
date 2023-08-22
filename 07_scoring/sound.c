#include <gb/gb.h>

#include "sound.h"

inline void init_sound(void) {
    NR52_REG = 0x80; // is 1000 0000 in binary and turns on sound
    NR50_REG = 0x77; // sets the volume for both left and right channel just set to max 0x77
    NR51_REG = 0xFF; // is 1111 1111 in binary, select which chanels we want to use in this case all of them. One bit for the L one bit for the R of all four channels
}

inline void wall_bounce_beep(void) {
    // Values taken from fidling with sound example program
    NR10_REG = 0x69;
    NR11_REG = 0x42;
    NR12_REG = 0x53;
    // Last two are frequency, LSB first
    NR13_REG = 0x77;
    NR14_REG = 0x86;
}

inline void paddle_bounce_beep(void) {
    // Values taken from fidling with sound example program
    NR10_REG = 0x69;
    NR11_REG = 0x42;
    NR12_REG = 0x53;
    // Last two are frequency, LSB first
    NR13_REG = 0xff;
    NR14_REG = 0x86;
}
