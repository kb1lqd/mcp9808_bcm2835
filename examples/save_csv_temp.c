/* This is a simple test program to first interface to the mcp9808 
 * using the BCM2835 library.
*/
#include <stdio.h>
#include <unistd.h>
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

	float test;

	while(1)
	{
		FILE *f = fopen("test.csv", "a");
		test = mcp9808_get_temp();
		printf("TEMP 3 = Value: %0.2f\n", test);
		fprintf(f, "%0.2f\n", test);
		usleep(100000);
		fclose(f);

	}
	
	bcm2835_i2c_end();
	bcm2835_close();
	
	
	

		return 0;
}



