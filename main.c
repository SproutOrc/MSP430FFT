#include <MSP430x14x.h>
#include "fft.h"
#include "config.h"

Complex data[];

int main( void )
{
    // Stop watchdog timer to prevent time out reset
    WDTCTL = WDTPW + WDTHOLD;
    Clock_Init();
    while (1) {
        
    }
    return 0;
}
