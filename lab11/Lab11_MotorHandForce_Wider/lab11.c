//////////////////////////////
//Willard Wider
//07/01/18
//ELEC3800
//Lab11
//Analog control of PWM motor
//////////////////////////////

/* DriverLib Includes */
#include <ti/devices/msp432p4xx/driverlib/driverlib.h>

/* Standard Includes */
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>

//pre-defined timer values for each speed (all CW)
#define REAL_STOP 0//let's be real. don't have to calibrate for middle if you don't send a signal #rollSafe
#define STOP 192//7.5% duty cycle -> 1.5ms - theoretical stop
#define REALLY_REALLY_SLOW 190//
#define REALLY_SLOW 186//
#define QUITE_SLOW 180//
#define MEDIUM 170//
#define FAST 128//5% duty cycle -> 1ms
#define PERIOD 2560//period of "carrier wave"
//2560  = 20ms

//pre-defined analog values for speeds
//ADC for 3.3 volts goes from 0 to 3FFF
#define SPEED_1 0x0300//slowest
#define SPEED_2 0x0700//
#define SPEED_3 0x1000//
#define SPEED_4 0x1200//
#define SPEED_5 0x1400//fastest

//statics
static volatile uint16_t curADCResult = 0x0000;
static volatile long avg100Results = 0;
static volatile int counter = 0;
static uint_fast16_t newPWMMode = STOP;

uint_fast16_t GetNewPWMSpeed();

/* Timer_A PWM Configuration Parameter */
Timer_A_PWMConfig pwmConfig =
{
        TIMER_A_CLOCKSOURCE_SMCLK,
        TIMER_A_CLOCKSOURCE_DIVIDER_1,
        PERIOD,
        TIMER_A_CAPTURECOMPARE_REGISTER_1,
        TIMER_A_OUTPUTMODE_RESET_SET,
        STOP//stop it first off
};

int main(void)
{
    printf("Halting watchdog...\n");
    /* Halting the watchdog */
    MAP_WDT_A_holdTimer();

    printf("Compleet, init PWM...\n");
    //PWM_CODE/////////////////////////////////////////////////////////////////////////////////////////////////
    /* Setting MCLK to REFO at 128Khz for LF mode Setting SMCLK to 64Khz */
    MAP_CS_setReferenceOscillatorFrequency(CS_REFO_128KHZ);
    MAP_CS_initClockSignal(CS_MCLK, CS_REFOCLK_SELECT, CS_CLOCK_DIVIDER_1);
    MAP_CS_initClockSignal(CS_SMCLK, CS_REFOCLK_SELECT, CS_CLOCK_DIVIDER_1);
    MAP_PCM_setPowerState(PCM_AM_LF_VCORE0);

    /* Configuring GPIO2.4 as peripheral output for PWM */
    MAP_GPIO_setAsPeripheralModuleFunctionOutputPin(GPIO_PORT_P2, GPIO_PIN4, GPIO_PRIMARY_MODULE_FUNCTION);

    /* Configuring Timer_A  */
    MAP_Timer_A_generatePWM(TIMER_A0_BASE, &pwmConfig);
    //!PWM_CODE////////////////////////////////////////////////////////////////////////////////////////////////

    printf("Complete, init ADC...\n");
    //ADC_CODE/////////////////////////////////////////////////////////////////////////////////////////////////
    /* Setting Flash wait state */
    MAP_FlashCtl_setWaitState(FLASH_BANK0, 1);

    /* Setting DCO to 48MHz  */
    MAP_CS_setDCOCenteredFrequency(CS_DCO_FREQUENCY_48);

    //![Single Sample Mode Configure]
    /* Initializing ADC (MCLK/1/4) */
    MAP_ADC14_enableModule();
    MAP_ADC14_initModule(ADC_CLOCKSOURCE_MCLK, ADC_PREDIVIDER_1, ADC_DIVIDER_4, 0);//needed now

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
    //!ADC_CODE////////////////////////////////////////////////////////////////////////////////////////////////

    printf("Complete, starting loop\n");
    while (1)
    {
        newPWMMode = GetNewPWMSpeed();
        if(newPWMMode != pwmConfig.dutyCycle)
        {
            //update the value
            printf("Updating PWM value to %d\n",newPWMMode);
            pwmConfig.dutyCycle = newPWMMode;
            MAP_Timer_A_generatePWM(TIMER_A0_BASE, &pwmConfig);
        }
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
       //curADCResult = MAP_ADC14_getResult(ADC_MEM0);
       avg100Results+=MAP_ADC14_getResult(ADC_MEM0);
       counter++;
       if(counter >= 100)
       {
           curADCResult = avg100Results / 100;
           avg100Results = 0;
           counter=0;
           //for debugging
           if(0)
           {
               printf("curADCResult=%x\n",curADCResult);
           }
       }
       MAP_ADC14_toggleConversionTrigger();
   }
}
//![Single Sample Result]

uint_fast16_t GetNewPWMSpeed()
{
    //since it's cascading if statements, check ADC level from low to high
    if(curADCResult <= SPEED_1)
    {
        return REAL_STOP;
    }
    else if (curADCResult <= SPEED_2)
    {
        //means it's between speed 1 and speed 2, etc.
        return REALLY_REALLY_SLOW;
    }
    else if (curADCResult <= SPEED_3)
    {
        return REALLY_SLOW;
    }
    else if (curADCResult <= SPEED_4)
    {
        return QUITE_SLOW;
    }
    else if (curADCResult <= SPEED_5)
    {
        return MEDIUM;
    }
    else//it's above SPEED_5
    {
        return FAST;
    }
}
