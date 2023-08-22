#include <gb/gb.h>
#include <stdint.h>


void main(void)
{
    while(1) {
		// Yield CPU and wait for start of next frame
        vsync();
    }
}
