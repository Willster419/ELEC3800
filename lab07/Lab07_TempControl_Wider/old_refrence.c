/* 
 * File:   main.c
 * Author: Willard Wider
 *
 * Created on March 17, 2016, 12:55 PM
 * Simulates a heater
 */
/*
#include <stdio.h>
#include <stdlib.h>
#include <wiringPi.h>
#include <wiringPiSPI.h>//this must be included to use the SPI interface

#define CHANNEL_CONFIG_SINGLE 8//using one wire's node voltage
#define CHANNEL_CONFIG_DIFF 0//using the difference to two wires
#define TEMP_THRESHOLD_LOW 0x00d0//the low tempature for the temp sensor
//to turn on the heator (208 in dec)
#define LED_PIN 17//LED and MOSFET are off the same pin
#define TEMP_THRESHOLD_HIGH 0x00e0//the high tempature for the temp sensor
//to turn off the heator (224 in dec)

int main(int argc, char** argv) {
    //max digital voltage is 3ff
    //min digital voltage is 0
    int dataDisplay; //the number read from the analog chip output
    int theChannelConfig = CHANNEL_CONFIG_DIFF;
    int spiChannelt = 0; //the spi channel in terms of the pi. eithor 1 or 0
    int analogChannelt = 0; //the analog channel(s) on the chip since this is
    //Difference, is uses channels 0 and 1.
    int clockFrequency = 1000000;
    int index = 0;
    int adcBuffer[100];
    int adder;
    int average;
    int keepOff;
    keepOff = 1;

    wiringPiSetupGpio();
    wiringPiSPISetup(spiChannelt, clockFrequency); //setting up the pi's 
    //SPI interface
    adder = 0;
    average = 0;
    pinMode(LED_PIN, OUTPUT); //setup a GPIO pin to give a digital brightness
    while (1) {//forever!
        while (index < 100) {
            adcBuffer[index] = myAnalogRead(spiChannelt, theChannelConfig, analogChannelt);
            adder = adder + adcBuffer[index];
            index++;
        }
        dataDisplay = (adder / 100);
        if ((TEMP_THRESHOLD_HIGH > dataDisplay) && (keepOff == 0)) {
            toggleHeat(0);
            keepOff = 1;
            //printf("Turn on\n");
        }
        if ((TEMP_THRESHOLD_LOW > dataDisplay) && (keepOff == 1)) {
            toggleHeat(1);
            //printf("Turn on\n");
            keepOff = 0;
        }
        delay(100);
        index = 0;
        adder = 0;
        average = 0;
    }

    //The following was for getting a single value. Was used for testing and
    //part 1 of the lab
    //dataDisplay = myAnalogRead(spiChannelt, theChannelConfig, analogChannelt);
    //delayMicroseconds(1000);
    //printf("Data Display is %x\n",dataDisplay);

    //The following was used for getting multiple values over time. Was used
    //for part 2 of the lab
    while (index<3)
    {
        adcBuffer[index] = myAnalogRead(spiChannelt, theChannelConfig, analogChannelt);
        index++;
        delay(1000);
    }
    printf("Data 0 is %x\n",adcBuffer[0]);
    printf("Data 1 is %x\n",adcBuffer[1]);
    printf("Data 2 is %x\n",adcBuffer[2]);
    return (EXIT_SUCCESS);
}
*/
//Reads the analog voltage difference from the two analog channel pins and
//converts it to a digital voltage
/*
int myAnalogRead(int spiChannel, int channelConfig, int analogChannel) {
    unsigned char buffer[3] = {1}; // start bit
    buffer[1] = (channelConfig + analogChannel) << 4;
    wiringPiSPIDataRW(spiChannel, buffer, 3);
    return ( (buffer[1] & 3) << 8) +buffer[2]; // get last 10 bits
}

void toggleHeat(int turnOn) {
    if (turnOn == 1) {
        digitalWrite(LED_PIN, HIGH);
    } else {
        digitalWrite(LED_PIN, LOW);
    }
}
*/
