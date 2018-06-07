//////////////////////
//Willard Wider
//5/29/18
//ELEC 3800
//Lab 6
//////////////////////
//P5.5 is analog input
/* DriverLib Includes */
#include <ti/devices/msp432p4xx/driverlib/driverlib.h>

/* Standard Includes */
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>

#define MAX_VALUE 0x3FFF

/* Statics */
static volatile uint16_t curADCResult = 0x0000;
uint16_t off_delay = 0x0000;
uint16_t u = 0x0000;

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

    //setup the output pin
    //remember, setting the pin HIGH turns OFF the led,
    //setting pin LOW turns ON led (current cna flow)
    GPIO_setAsOutputPin(GPIO_PORT_P1,GPIO_PIN0);
    //NOTE: sensor has full range
    while (1)
    {
        //set the led on
        GPIO_setOutputHighOnPin(GPIO_PORT_P1, GPIO_PIN0);
        //on for delay
        for(u = 0x0000; u < curADCResult; u++) ;

        //set led off
        GPIO_setOutputLowOnPin(GPIO_PORT_P1, GPIO_PIN0);
        //off for delay
        off_delay = (0x3FFF >> 2) - curADCResult;
        for(u = 0x0000; u < off_delay; u++) ;
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
        //scale the result so that it can actually look like a digital brightness
        curADCResult = curADCResult >> 2;
        if(0)
        {
            printf("curADCResult=%x\n",curADCResult);
        }

        MAP_ADC14_toggleConversionTrigger();
    }
}
//![Single Sample Result]

