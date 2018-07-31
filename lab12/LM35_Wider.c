/////////////////
//Willard Wider
//7/19/18
//ELEC3800
//Lab12
//Keysignt demo
/////////////////

#include "mraa.h"
#include <stdio.h>

mraa_gpio_context MCP3208_DIN;
mraa_gpio_context MCP3208_DOUT;
mraa_gpio_context MCP3208_CLK;
mraa_gpio_context MCP3208_CS;

//vals for lab edit
char counter = 0;

int GetMCP3208 (int Channel);

int main()
{
  const struct sched_param priority = {1};
  sched_setscheduler (0, SCHED_FIFO, &priority);

  int i;
  
  //init the GPIO pins
  MCP3208_DIN = mraa_gpio_init (11);
  MCP3208_DOUT = mraa_gpio_init (24);
  MCP3208_CLK = mraa_gpio_init (10);
  MCP3208_CS = mraa_gpio_init (23);
  
  mraa_gpio_use_mmaped (MCP3208_DIN, 1);
  mraa_gpio_use_mmaped (MCP3208_DOUT, 1);
  mraa_gpio_use_mmaped (MCP3208_CLK, 1);
  mraa_gpio_use_mmaped (MCP3208_CS, 1);
  //init SPI interface
  mraa_gpio_dir(MCP3208_DIN, MRAA_GPIO_OUT_HIGH);
  mraa_gpio_dir(MCP3208_DOUT, MRAA_GPIO_IN);
  mraa_gpio_dir(MCP3208_CLK, MRAA_GPIO_OUT);
  mraa_gpio_dir(MCP3208_CS, MRAA_GPIO_OUT);

  //this loop is for getting each channel (if you adjusted the loop paremters)
  /*
  for (i = 7; i < 8; i ++)
  {
    printf("A%d: 0x%x\n", i, GetMCP3208 (i));
      
  }*/
  int channel = 7;
  printf("Willard Wider lab 12\n");
  for (i = 0; i < 50; i++)
  {
    int raw_vale = GetMCP3208(channel);
    int decimal_value = (int)raw_vale;
    decimal_value = decimal_value*500;
    decimal_value = decimal_value/4096;//digital resolution
    printf("Loop iteration %d, hex value of port %d is 0x%x, which is %d deg C\n",
    i,channel,raw_vale,decimal_value);
  }
  
  return MRAA_SUCCESS;
}

int GetMCP3208 (int Channel)
{
  int i;
  int val;
  
  mraa_gpio_write (MCP3208_DIN, 0);
  //more clocking to the device
  mraa_gpio_write (MCP3208_CLK, 0);
  //enable the device by setting cable select to 0
  mraa_gpio_write (MCP3208_CS, 0);
  //0x18 = 00011000
  //the 0x08 part makes it single ended config
  //the 0x10 part makes it init the conversion
  Channel = Channel | 0x18;
  for (i = 0; i < 5; i ++)
  {
    if (Channel & 0x10)
    {
      mraa_gpio_write (MCP3208_DIN, 1);
    }
    else
    {
      mraa_gpio_write (MCP3208_DIN, 0);
    }
    Channel <<= 1;
    //clocking
    mraa_gpio_write (MCP3208_CLK, 0);
    mraa_gpio_write (MCP3208_CLK, 1);
  }
  //send the clock thorugh for the conversion...
  mraa_gpio_write (MCP3208_CLK, 0);
  mraa_gpio_write (MCP3208_CLK, 1);

  mraa_gpio_write (MCP3208_CLK, 0);
  mraa_gpio_write (MCP3208_CLK, 1);

  val = 0;
  for (i = 0; i < 12; i ++)
  {
    //more clocking...
    mraa_gpio_write (MCP3208_CLK, 0);
    mraa_gpio_write (MCP3208_CLK, 1);
    //...and finally get the value
    val = (val << 1) | ((int) mraa_gpio_read (MCP3208_DOUT));
  }
  
  mraa_gpio_write (MCP3208_CS, 1);
  mraa_gpio_write (MCP3208_DIN, 0);
  mraa_gpio_write (MCP3208_CLK, 0);

  return val;
}
