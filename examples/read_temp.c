/* This is a simple test program to first interface to the mcp9808 
 * using the BCM2835 library.
*/
#include <stdio.h>
#include <bcm2835.h>
#include "../mcp9808_bcm2835.h"

#define SLAVE_ADDRESS 24 //0x18
#define BUF_SIZE 4

#define TESTMASK 0b00010000

int main (void)
{
	
	//function variables
	char current_reg = 0x05;
	int clk_div = 2000;
	char rxbuf[BUF_SIZE]; //buffer for received values
	int mcp9808_reason_code;
	int i; //for loops
	
	//initialize bcm2835 library
	if(!bcm2835_init())
	{
		printf("Failed to initialize.");
		return 1;
	}	

	//initialize I2C pins for I2C operations (ALT mode)
	if(!bcm2835_i2c_begin())
	{
		printf("I2C Init Failed. Are you running as root?");
	}
	
	//set slave address
	bcm2835_i2c_setSlaveAddress(24);
	
	//set baudrate (standard is 100kbaud)
	bcm2835_i2c_set_baudrate(100000);

	//MCP9808_BCM2835 Read Register Function
	mcp9808_read_reg(REG_TEMP, rxbuf, 2);
	
	// Parse temp register values
	int temp_sign = 0;
	temp_sign = (0b00010000 & rxbuf[0]) >> 4;	
	printf("TEMP SIGN Value: %d\n", temp_sign);
	
	unsigned char temp_ta_high;
	unsigned char temp_ta_low;
	int temperature_1 = 0;
	int temperature_2 = 0;
	int temperature_3 = 0;
	
	temp_ta_high = 0b00001111 && rxbuf[0];
	temp_ta_low = rxbuf[1];
	
	if(temp_sign == 0){
		temperature_1 = (temp_ta_high<<8) | temp_ta_low;
		temperature_2 = temperature_1;
		temperature_3 = temperature_2/16;
	}
	else{
		// Write negative temp conversion...
	}
	
	
	printf("TEMP 1 = Value: %d\n", temperature_1);
	printf("TEMP 2 = Value: %d\n", temperature_2);
	printf("TEMP 3 = Value: %d\n", temperature_3);

	
	
	//Display the resulting register read
	for(i=0;i<BUF_SIZE;i++)
	{
		printf("RXBUF[%d] Value: %d\n", i, rxbuf[i]);
	}
	
	
	bcm2835_i2c_end();
	bcm2835_close();
	
	
	

		return 0;
}
