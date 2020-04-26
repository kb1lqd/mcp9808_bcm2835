/* This is a simple test program to first interface to the mcp9808 
 * using the BCM2835 library.
*/
#include <stdio.h>
#include <unistd.h>
#include <bcm2835.h>
#include <signal.h>
#include <time.h>
#include "../mcp9808_bcm2835.h"

#define SLAVE_ADDRESS 24 //0x18
#define I2C_FREQ_HZ 100000 
#define BUF_SIZE 4

#define TESTMASK 0b00010000

void sigintHandler( int sig_num );
void i2csetup( char config );
void disableI2c( void );
void enableI2c( void );


//Global Variables
char infLoopFlag = 1;
float floatTempVal;

int main (int argc, char *argv[])
{
	
		
	//function variables
	char current_reg = 0x05;
	int clk_div = 2000;
	int intervaltime_s;	
	int mcp9808_reason_code;
	int i; //for loops
	time_t t;
	struct tm *tmp;
	char file_time[50];
	char data_time[50];
	
	//Create file time
	time(&t);
	tmp = localtime( &t );
	// using strftime to display time 
    strftime(file_time, sizeof(file_time), "%Y%m%d-%H%M%S_templog.csv", tmp);   
    printf("Formatted date & time : %s\n", file_time );
    
	
	//Parse arguments
	if(argc<2)
		{
			printf("Incorrect argument count.\n");
			printf("savecsv {interval (s)}\n");
			return 1;
		}
	else
	{
		intervaltime_s = atoi(argv[1]);
		if(intervaltime_s == 0)
		{
			intervaltime_s = 1;
			printf("Incorrect time interval, default set to 1 second.\n");
		}
	}
	
	// Enable I2C
	i2csetup(1);
	//initialize bcm2835 library
	
	// Create signal handler to allouw CNTL-C to quit loop
	signal(SIGINT, sigintHandler);

	while(infLoopFlag)
	{
		FILE *f = fopen(file_time, "a");
		floatTempVal = mcp9808_get_temp();
		printf("TEMP 3 = Value: %0.2f\n", floatTempVal);
		
		// Update data time log
		time(&t);
		tmp = localtime( &t );
		strftime(data_time, sizeof(data_time), "%Y-%m-%d %H:%M:%S", tmp);   
		printf("Formatted date & time : %s\n", data_time );
		
		fprintf(f, "%s,%0.2f\n", data_time, floatTempVal);
		usleep(intervaltime_s*1000000);
		fclose(f);

	}
	
	// Disable I2C
	i2csetup(0);

	return 0;
}

void i2csetup( char config )
{
	switch(config)
	{
		case 0: //disable I2C
			disableI2c();
			break;
		case 1: //initialize I2C
			enableI2c();
			break;
		default: //default
			disableI2c();
			break;
			
	}	
}

void enableI2c(void)
{
	//initialize bcm2835 library
	if(!bcm2835_init())
	{
		printf("Failed to initialize.");
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
	
	printf("I2C Initialized with slave address %d at %dKHz.\n", 24, 100000/1000);
}

void disableI2c(void)
{
	bcm2835_i2c_end();
	bcm2835_close();
	printf("I2C Disabled.\n");
}

void sigintHandler(int sig_num)
{
	printf("CNTL-C Pressed.\n");
	infLoopFlag = 0;
	
}




