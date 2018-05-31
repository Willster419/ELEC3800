////////////////////////////////////////////////////////
//Willard Wider
//Lab 03 - BlinkLED
//05/15/18
//Modified blink LED example program
////////////////////////////////////////////////////////

#include <ti/devices/msp432p4xx/driverlib/driverlib.h>

#define ORIG_DELAY 100000
#define SHORT_DELAY 10
#define LONG_DELAY
#define S_DELAY 50000
#define O_DELAY 100000
#define S_BLINKS 6
#define O_BLINKS 6
#define FULL_DELAY 500000

int main(void)
{
    volatile uint32_t i, j;

    // Stop watchdog timer
    WDT_A_hold(WDT_A_BASE);

    // Set P1.0 to output direction
    GPIO_setAsOutputPin(GPIO_PORT_P1,GPIO_PIN0);

    while(1)
    {
        // Toggle P1.0 output
        //GPIO_toggleOutputOnPin(GPIO_PORT_P1,GPIO_PIN0);
        //toggle implies switcing it one way or other, a full on of cycle takes 2 toggles

        /* original code
        // Delay
        //for(i=100000; i>0; i--);
        //makeing it incriment instead of decriment
        for(i=0; i < 100000; i++)
        {

        }
        */

        //4 fast blinks
        //needs to be 8 cause a blink it a toggle on/off (two code hits)
        for(i = 0; i < 8; i++)
        {
            GPIO_toggleOutputOnPin(GPIO_PORT_P1,GPIO_PIN0);
            for(j = 0; j < S_DELAY; j++)
            {

            }
        }

        //2 slow blinks
        for(i = 0; i < 4; i++)
        {
            GPIO_toggleOutputOnPin(GPIO_PORT_P1,GPIO_PIN0);
            for(j = 0; j < O_DELAY; j++)
            {

            }
        }

        //and a reset delay
        //delay of pause
        //turn it back off
        for(i = 0; i < FULL_DELAY; i++)
        {

        }

        /*delay for SOS
        //first S
        for(i = 0; i < S_BLINKS; i++)
        {
            GPIO_toggleOutputOnPin(GPIO_PORT_P1,GPIO_PIN0);
            for(j = 0; j < S_DELAY; j++)
            {

            }
        }

        //O
        for(i = 0; i < O_BLINKS; i++)
        {
            GPIO_toggleOutputOnPin(GPIO_PORT_P1,GPIO_PIN0);
            for(j = 0; j < O_DELAY; j++)
            {

            }
        }

        //second s
        for(i = 0; i < S_BLINKS; i++)
        {
            GPIO_toggleOutputOnPin(GPIO_PORT_P1,GPIO_PIN0);
            for(j = 0; j < S_DELAY; j++)
            {

            }
        }

        //delay of pause
        for(i = 0; i < FULL_DELAY; i++)
        {

        }
        */

    }
}
