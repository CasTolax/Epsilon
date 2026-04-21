#include "kernel.h"
#include "eprint.h"
#include <stdint.h>

#define EPRINT_STATE_NORMAL             0
#define EPRINT_STATE_LENGTH             1
#define EPRINT_STATE_SHORT              2    
#define EPRINT_STATE_LONG               3

#define EPRINT_LENGTH_DEFAULT           0
#define EPRINT_LENGTH_SHORT_SHORT       1
#define EPRINT_LENGTH_SHORT             2
#define EPRINT_LENGHT_LONG              3
#define EPRINT_LENGHT_LONG_LONG         4


void eprint(const char* fmt , ...);

void eprint(const char* fmt , ...)
{   
    int* argp = (int*)&fmt;
    int state = EPRINT_STATE_NORMAL;
    int lenght = EPRINT_LENGTH_DEFAULT;

    while(*fmt)
    {   
        switch (state)
        {
        case EPRINT_STATE_NORMAL :
                switch (*fmt)
                {
                    case '%': state = EPRINT_STATE_LENGTH;
                               break;
                    default:   eput(*fmt);
                               break;
                }
            break;
        case EPRINT_STATE_LENGTH:
                switch (*fmt)
                    case 'h': lenght = EPRINT_LENGTH_SHORT;
                              state = EPRINT_STATE_SHORT;
                              break;
                    case 'l': lenght = EPRINT_LENGHT_LONG;
                              state = EPRINT_STATE_LONG;
                              break;
                    default:
                        break;
                        // These codes are not complete yet.
                
        
        }
        fmt++;
    }
}