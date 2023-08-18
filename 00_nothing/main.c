#include <gb/gb.h>
#include <stdint.h>


void main(void)
{
    while(1) {

		// Done processing, yield CPU and wait for start of next frame
        vsync();
    }
}
