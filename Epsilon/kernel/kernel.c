/*
    * this is the Epsilon kernel. Dont forget because this is hobby project.
    * Since I’m still new to ASM, I might make mistakes in some sector addresses, 
    * 
    * so feel free to critique my code!
    * Since there are no standard libraries in this kernel code, writing, being able to write,
    * and debugging the libraries or C code needed to communicate with the hardware is really painful for me right now, 
    * but I’m sure that if I can stick with it, this type of kernel could be helpful to everyone.
    * 
    * BY CasTolax 2026.
*/


#include "kernel.h"
#include "eprint.h"
#include <stdint.h>

void kernel_main()
{   

    //Test: OK!
    volatile uint16_t* vga = (uint16_t*)0xB8000;
    vga[0] = 0x04F;
    vga[1] = 0x046; 

    eprint("Hello Epsilon! \n");
    eprint_color("Hello Epsilon",RED);

    while(1);
}   