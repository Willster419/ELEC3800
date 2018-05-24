////////////////////////////////////////////////////////
//Willard Wider
//Lab 05 - Seg7Dspl
//05/22/18
//7 Segment Display
////////////////////////////////////////////////////////

#include <ti/devices/msp432p4xx/driverlib/driverlib.h>

#define DELAY 50000

int main(void)
{
    volatile uint32_t i, j;
    unsigned char seq = 0x00;

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

    //DEBUG: show at least something is working
    GPIO_setOutputHighOnPin(GPIO_PORT_P1,GPIO_PIN0);

    //usefull methods
    //GPIO_setOutputHighOnPin(GPIO_PORT_P4, ++incriment);
    //GPIO_setOutputLowOnPin(GPIO_PORT_P4, ~incriment);

    //hex to 7 seg values are as follows


    while(1)
    {
        //set the displays back off
        GPIO_setOutputHighOnPin(GPIO_PORT_P4, 0x7F);

        //set the displays on based on case
        displayNumberz(seq);

        //delay of pause
        for(i = 0; i < DELAY; i++)
        {

        }
        if (seq == 0x0F)
        {
            //set it to FF os that when it's incrimented it will go back to 0
            seq = 0xFF;
        }
        seq++;
    }
}

void displayNumberz(char num)
{
    switch (num)
    {
        case 0x00:
            GPIO_setOutputLowOnPin(GPIO_PORT_P4,0x3F);
            break;
        case 0x01:
            GPIO_setOutputLowOnPin(GPIO_PORT_P4,0x06);
            break;
        case 0x02:
            GPIO_setOutputLowOnPin(GPIO_PORT_P4,0x5B);
            break;
        case 0x03:
            GPIO_setOutputLowOnPin(GPIO_PORT_P4,0x4F);
            break;
        case 0x04:
            GPIO_setOutputLowOnPin(GPIO_PORT_P4,0x66);
            break;
        case 0x05:
            GPIO_setOutputLowOnPin(GPIO_PORT_P4,0x6D);
            break;
        case 0x06:
            GPIO_setOutputLowOnPin(GPIO_PORT_P4,0x7D);
            break;
        case 0x07:
            GPIO_setOutputLowOnPin(GPIO_PORT_P4,0x07);
            break;
        case 0x08:
            GPIO_setOutputLowOnPin(GPIO_PORT_P4,0x7F);
            break;
        case 0x09:
            GPIO_setOutputLowOnPin(GPIO_PORT_P4,0x67);
            break;
        case 0x0A:
            GPIO_setOutputLowOnPin(GPIO_PORT_P4,0x77);
            break;
        case 0x0B:
            GPIO_setOutputLowOnPin(GPIO_PORT_P4,0x7C);
            break;
        case 0x0C:
            GPIO_setOutputLowOnPin(GPIO_PORT_P4,0x39);
            break;
        case 0x0D:
            GPIO_setOutputLowOnPin(GPIO_PORT_P4,0x5E);
            break;
        case 0x0E:
            GPIO_setOutputLowOnPin(GPIO_PORT_P4,0x79);
            break;
        case 0x0F:
            GPIO_setOutputLowOnPin(GPIO_PORT_P4,0x71);
            break;
    }
    printf("%x\n",num);
}
