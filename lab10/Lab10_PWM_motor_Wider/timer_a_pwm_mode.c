////////////////
//Willard Wider
//6/14/18
//ELEC3800
//Lab10
//PWM
////////////////
//pin 1.1 is the input to change the frequency
/* DriverLib Includes */
#include <ti/devices/msp432p4xx/driverlib/driverlib.h>

/* Standard Includes */
#include <stdint.h>
#include <stdbool.h>

//pre-defined timer values for duty cycle
#define FAST_CCW 256//10% duty cycle -> 2ms
#define SLOW_CCW 198//
#define STOP 192//7.5% duty cycle -> 1.5ms
#define SLOW_CW 186//
#define FAST_CW 128//5% duty cycle -> 1ms
#define PERIOD 2560//period of "carrier wave"
//2560  = 20ms

/* Timer_A PWM Configuration Parameter */
Timer_A_PWMConfig pwmConfig =
{
        TIMER_A_CLOCKSOURCE_SMCLK,
        TIMER_A_CLOCKSOURCE_DIVIDER_1,
        PERIOD,
        TIMER_A_CAPTURECOMPARE_REGISTER_1,
        TIMER_A_OUTPUTMODE_RESET_SET,
        FAST_CW//enabled a 5% duty cycle ->1ms
};

int main(void)
{
    /* Halting the watchdog */
    MAP_WDT_A_holdTimer();

    /* Setting MCLK to REFO at 128Khz for LF mode Setting SMCLK to 64Khz */
    MAP_CS_setReferenceOscillatorFrequency(CS_REFO_128KHZ);
    MAP_CS_initClockSignal(CS_MCLK, CS_REFOCLK_SELECT, CS_CLOCK_DIVIDER_1);
    MAP_CS_initClockSignal(CS_SMCLK, CS_REFOCLK_SELECT, CS_CLOCK_DIVIDER_1);
    MAP_PCM_setPowerState(PCM_AM_LF_VCORE0);

    /* Configuring GPIO2.4 as peripheral output for PWM  and P6.7 for button interrupt */
    MAP_GPIO_setAsPeripheralModuleFunctionOutputPin(GPIO_PORT_P2, GPIO_PIN4, GPIO_PRIMARY_MODULE_FUNCTION);
    MAP_GPIO_setAsInputPinWithPullUpResistor(GPIO_PORT_P1, GPIO_PIN1);
    MAP_GPIO_clearInterruptFlag(GPIO_PORT_P1, GPIO_PIN1);
    MAP_GPIO_enableInterrupt(GPIO_PORT_P1, GPIO_PIN1);

    /* Configuring Timer_A  */
    MAP_Timer_A_generatePWM(TIMER_A0_BASE, &pwmConfig);

    /* Enabling interrupts and starting the watchdog timer */
    MAP_Interrupt_enableInterrupt(INT_PORT1);
    MAP_Interrupt_enableMaster();

    while (1)
    {
    }
}

/* Port1 ISR - This ISR will progressively step up the duty cycle of the PWM
 * on a button press
 */
void PORT1_IRQHandler(void)
{
    uint32_t status = MAP_GPIO_getEnabledInterruptStatus(GPIO_PORT_P1);
    MAP_GPIO_clearInterruptFlag(GPIO_PORT_P1, status);

    if (status & GPIO_PIN1)
    {
        //on button press
        //switch statement to specify which one to move to
        //rather than having a motor_state variable, use the direct pwm frequency itself
        switch(pwmConfig.dutyCycle)
        {
            case FAST_CCW:
                pwmConfig.dutyCycle = SLOW_CCW;
                break;
            case SLOW_CCW:
                pwmConfig.dutyCycle = STOP;
                break;
            case STOP:
                pwmConfig.dutyCycle = SLOW_CW;
                break;
            case SLOW_CW:
                pwmConfig.dutyCycle = FAST_CW;
                break;
            case FAST_CW:
                pwmConfig.dutyCycle = FAST_CCW;
                break;
        }

        MAP_Timer_A_generatePWM(TIMER_A0_BASE, &pwmConfig);
    }
}
