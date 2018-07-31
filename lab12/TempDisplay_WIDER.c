#include "mraa.h"
#include <stdio.h>

#define addr 0x7C

mraa_gpio_context reset;
mraa_gpio_context sda;
mraa_gpio_context scl;

mraa_gpio_context MCP3208_DIN;
mraa_gpio_context MCP3208_DOUT;
mraa_gpio_context MCP3208_CLK;
mraa_gpio_context MCP3208_CS;

void delay_time (unsigned int time_end)
{
	unsigned int index;
	for (index = 0; index < time_end; index++);
}

void i2c_start (void)
{
	mraa_gpio_write(sda, 1);
	mraa_gpio_write(scl, 1);
	delay_time (100);
	mraa_gpio_write(sda, 0);
	mraa_gpio_write(scl, 0);
}

void i2c_stop (void)
{
	mraa_gpio_write(scl, 0);
	mraa_gpio_write(sda, 0);
	mraa_gpio_write(scl, 1);
	delay_time (100);
	mraa_gpio_write(sda, 1);
}

void i2c_write (unsigned char output_data)
{
	unsigned char index;

	for(index = 0; index < 8; index++)  	// Send 8 bits to the I2C Bus
	{
        if (output_data & 0x80)
		{
			mraa_gpio_write(sda, 1);			
		}
		else
		{
			mraa_gpio_write(sda, 0);
		}
		output_data <<= 1;            		// Shift the byte by one bit
		mraa_gpio_write(scl, 1);
		delay_time (100);
		mraa_gpio_write(scl, 0);
	}
	
	mraa_gpio_write(scl, 1);
	delay_time (100);
	mraa_gpio_write(scl, 0);		
}

void LCD_Print (char* str)
{
	i2c_start ();                  			
   	i2c_write (addr);
   	i2c_write (0x00);
   	i2c_write (0x01);
	i2c_stop();	
	
	i2c_start ();                  			
   	i2c_write (addr);
	i2c_write (0x40);
	for (; *str != '\0'; str ++)
	{
		i2c_write (*str);
	}
	i2c_stop();
}

void init_LCD (void)
{
	i2c_start ();                  			
   	i2c_write (addr);
   	i2c_write (0x00);
   	i2c_write (0x38);
	i2c_stop();
	
	i2c_start ();                  			
   	i2c_write (addr);
   	i2c_write (0x00);
   	i2c_write (0x39);
	i2c_stop();
	
	i2c_start ();                  			
   	i2c_write (addr);
   	i2c_write (0x00);
   	i2c_write (0x14);
	i2c_stop();
	
	i2c_start ();                  			
   	i2c_write (addr);
   	i2c_write (0x00);
   	i2c_write (0x79);
	i2c_stop();
	
	i2c_start ();                  			
   	i2c_write (addr);
   	i2c_write (0x00);
   	i2c_write (0x50);
	i2c_stop();	
	
	i2c_start ();                  			
   	i2c_write (addr);
   	i2c_write (0x00);
   	i2c_write (0x6C);
	i2c_stop();
	
	delay_time (300);
	
	i2c_start ();                  			
   	i2c_write (addr);
   	i2c_write (0x00);
   	i2c_write (0x0C);
	i2c_stop();
	
	i2c_start ();                  			
   	i2c_write (addr);
   	i2c_write (0x00);
   	i2c_write (0x01);
	i2c_stop();	
}

int GetMCP3208 (int Channel);

int main()
{
	const struct sched_param priority = {1};
	sched_setscheduler (0, SCHED_FIFO, &priority);

	int i;
	char buf [25];
	
	reset = mraa_gpio_init(36);
	sda = mraa_gpio_init(7);
	scl = mraa_gpio_init(19);
	
	MCP3208_DIN = mraa_gpio_init (11);
	MCP3208_DOUT = mraa_gpio_init (24);
	MCP3208_CLK = mraa_gpio_init (10);
	MCP3208_CS = mraa_gpio_init (23);

	mraa_gpio_dir(reset, MRAA_GPIO_OUT);
	mraa_gpio_dir(sda, MRAA_GPIO_OUT);
	mraa_gpio_dir(scl, MRAA_GPIO_OUT);	

	mraa_gpio_use_mmaped (MCP3208_DIN, 1);
	mraa_gpio_use_mmaped (MCP3208_DOUT, 1);
	mraa_gpio_use_mmaped (MCP3208_CLK, 1);
	mraa_gpio_use_mmaped (MCP3208_CS, 1);
	
	mraa_gpio_dir(MCP3208_DIN, MRAA_GPIO_OUT_HIGH);
	mraa_gpio_dir(MCP3208_DOUT, MRAA_GPIO_IN);
	mraa_gpio_dir(MCP3208_CLK, MRAA_GPIO_OUT);
	mraa_gpio_dir(MCP3208_CS, MRAA_GPIO_OUT);
	
	mraa_gpio_write(reset, 0);
	delay_time (500);
	mraa_gpio_write(reset, 1);
	delay_time (500);
    
	init_LCD ();
	while (1)
	{
		sprintf (buf, "WW: Temp: %3.1f%cC", (float) GetMCP3208 (7) * 500 / 4096, 0xDF);

		LCD_Print (buf);
		sleep (1);
	}
	
	return MRAA_SUCCESS;
}

int GetMCP3208 (int Channel)
{
	int i;
	int val;
	
	mraa_gpio_write (MCP3208_DIN, 0);
	mraa_gpio_write (MCP3208_CLK, 0);
	mraa_gpio_write (MCP3208_CS, 0);

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

		mraa_gpio_write (MCP3208_CLK, 0);
		mraa_gpio_write (MCP3208_CLK, 1);
	}

	mraa_gpio_write (MCP3208_CLK, 0);
	mraa_gpio_write (MCP3208_CLK, 1);

	mraa_gpio_write (MCP3208_CLK, 0);
	mraa_gpio_write (MCP3208_CLK, 1);

	val = 0;
	for (i = 0; i < 12; i ++)
	{
		mraa_gpio_write (MCP3208_CLK, 0);
		mraa_gpio_write (MCP3208_CLK, 1);
		
		val = (val << 1) | ((int) mraa_gpio_read (MCP3208_DOUT));	
	}
	
	mraa_gpio_write (MCP3208_CS, 1);
	mraa_gpio_write (MCP3208_DIN, 0);
	mraa_gpio_write (MCP3208_CLK, 0);

	return val;
}