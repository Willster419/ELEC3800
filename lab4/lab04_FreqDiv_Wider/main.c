////////////////////////////////////////////////////////
//Willard Wider
//Lab 04 - FreqDiv
//05/17/18
//Fequency division
////////////////////////////////////////////////////////

#include <ti/devices/msp432p4xx/driverlib/driverlib.h>

#define DELAY 100

int main(void)
{
    volatile uint32_t i, j;
    unsigned char incriment = 0;

    // Stop watchdog timer
    WDT_A_hold(WDT_A_BASE);

    //set the pins for the fewq div
    GPIO_setAsOutputPin(GPIO_PORT_P4,GPIO_PIN0);
    GPIO_setAsOutputPin(GPIO_PORT_P4,GPIO_PIN1);
    GPIO_setAsOutputPin(GPIO_PORT_P4,GPIO_PIN2);
    GPIO_setAsOutputPin(GPIO_PORT_P4,GPIO_PIN3);
    GPIO_setAsOutputPin(GPIO_PORT_P4,GPIO_PIN4);
    GPIO_setAsOutputPin(GPIO_PORT_P4,GPIO_PIN5);
    GPIO_setAsOutputPin(GPIO_PORT_P4,GPIO_PIN6);
    GPIO_setAsOutputPin(GPIO_PORT_P4,GPIO_PIN7);

    //DEBUG: show at least something is working (like the LED)
    //show that at least the code is being entered
    GPIO_setAsOutputPin(GPIO_PORT_P1,GPIO_PIN0);

    while(1)
    {
        //set them high
        GPIO_setOutputHighOnPin(GPIO_PORT_P4, ++incriment);

        //delay of pause
        for(i = 0; i < DELAY; i++)
        {

        }

        //set the inverts back to low
        GPIO_setOutputLowOnPin(GPIO_PORT_P4, ~incriment);

        //DEBUG: show at least something is working
        GPIO_toggleOutputOnPin(GPIO_PORT_P1,GPIO_PIN0);
    }
}
