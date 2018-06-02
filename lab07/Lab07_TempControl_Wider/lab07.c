//////////////////////
//Willard Wider
//5/29/18
//ELEC 3800
//Lab 07
//////////////////////

/* DriverLib Includes */
#include <ti/devices/msp432p4xx/driverlib/driverlib.h>

/* Standard Includes */
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>

#define TEMP_THRESHOLD_LOW 0x0100//the low tempature for the temp sensor
#define TEMP_THRESHOLD_HIGH 0x0FFF//the high tempature for the temp sensor
#define MODE_TOO_COLD 0
#define MODE_TOO_HOT 1
#define DELAY 1000

/* Statics */
static volatile uint16_t curADCResult = 0x0000;
//0 = too cold, keep on untill we get to high threshold
//1 = too warm, keep off untill we get to low threshold
static int mode = 0;

int i = 0;

int main(void)
{
    /* Halting the Watchdog  */
    MAP_WDT_A_holdTimer();

    /* Setting Flash wait state */
    MAP_FlashCtl_setWaitState(FLASH_BANK0, 1);
    
    /* Setting DCO to 48MHz  */
    MAP_CS_setDCOCenteredFrequency(CS_DCO_FREQUENCY_48);

    //![Single Sample Mode Configure]
    /* Initializing ADC (MCLK/1/4) */
    MAP_ADC14_enableModule();
    //MAP_ADC14_initModule(ADC_CLOCKSOURCE_MCLK, ADC_PREDIVIDER_1, ADC_DIVIDER_4, 0);
            
    /* Configuring GPIOs (5.5 A0) */
    //now it's 4.0
    MAP_GPIO_setAsInputPin(GPIO_PORT_P4,GPIO_PIN0);//clears pull up resistors i guess
    MAP_GPIO_setAsPeripheralModuleFunctionInputPin(GPIO_PORT_P4, GPIO_PIN0, GPIO_TERTIARY_MODULE_FUNCTION);

    /* Configuring ADC Memory */
    MAP_ADC14_configureSingleSampleMode(ADC_MEM0, true);
    MAP_ADC14_configureConversionMemory(ADC_MEM0, ADC_VREFPOS_AVCC_VREFNEG_VSS, ADC_INPUT_A13, false);

    /* Configuring Sample Timer */
    MAP_ADC14_enableSampleTimer(ADC_MANUAL_ITERATION);

    /* Enabling/Toggling Conversion */
    MAP_ADC14_enableConversion();
    MAP_ADC14_toggleConversionTrigger();
    //![Single Sample Mode Configure]

    /* Enabling interrupts */
    MAP_ADC14_enableInterrupt(ADC_INT0);
    MAP_Interrupt_enableInterrupt(INT_ADC14);
    MAP_Interrupt_enableMaster();

    //setup the output pin for relay and LED
    //high = turn heater on
    //low = turn header off
    //use pin 4.2 for the output
    //GPIO_setAsOutputPin(GPIO_PORT_P4,GPIO_PIN2);
    //tmep use default led as output
    GPIO_setAsOutputPin(GPIO_PORT_P1, GPIO_PIN0);

    //get the initial value for logick set before the loop
    //if it's below the low threshold, set mode to 0
    //else if it's inbetween both threholds, set mode to 1
    //else if it's above high threshold, set mode to 1
    printf("heater init, result is...");
    if(curADCResult < TEMP_THRESHOLD_LOW)
    {
        printf("value below low, turn on heater\n");
        GPIO_setOutputHighOnPin(GPIO_PORT_P1, GPIO_PIN0);
    }
    else if ((curADCResult > TEMP_THRESHOLD_LOW) && (curADCResult < TEMP_THRESHOLD_HIGH))
    {
        printf("value in middle, turn on heater\n");
        GPIO_setOutputHighOnPin(GPIO_PORT_P1, GPIO_PIN0);
    }
    else if (curADCResult > TEMP_THRESHOLD_HIGH)
    {
        printf("value above high, turn off heater");
        GPIO_setOutputLowOnPin(GPIO_PORT_P1, GPIO_PIN0);
    }
    else
    {
        printf("ERROR: this condition should not be reached on init!\n");
        return 1;
    }
    while (1)
    {
        //look at logik above
        if(curADCResult < TEMP_THRESHOLD_LOW && mode == MODE_TOO_HOT)
        {
            printf("temp below low threshold from fall, turning heater on\n");
            mode = MODE_TOO_COLD;
            //toggle pin on
            GPIO_setOutputHighOnPin(GPIO_PORT_P1, GPIO_PIN0);
        }
        else if (curADCResult > TEMP_THRESHOLD_HIGH && mode == MODE_TOO_COLD)
        {
            printf("temp above high threshold from rise, turning heater off\n");
            mode = MODE_TOO_HOT;
            //toggle pin off
            GPIO_setOutputLowOnPin(GPIO_PORT_P1, GPIO_PIN0);
        }
        //delay so it's not running 24/7
        for(i = 0; i < DELAY; i++);
    }
    
}

 //![Single Sample Result]
/* ADC Interrupt Handler. This handler is called whenever there is a conversion
 * that is finished for ADC_MEM0.
 */
void ADC14_IRQHandler(void)
{
    uint64_t status = MAP_ADC14_getEnabledInterruptStatus();
    MAP_ADC14_clearInterruptFlag(status);

    if (ADC_INT0 & status)
    {
        curADCResult = MAP_ADC14_getResult(ADC_MEM0);
        //for debugging
        if(0)
        {
            printf("curADCResult=%x\n",curADCResult);
        }

        MAP_ADC14_toggleConversionTrigger();
    }
}
//![Single Sample Result]

