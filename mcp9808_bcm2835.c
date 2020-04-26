/*
** @source MCP9808_BCM2535
**
** This C library supports the MCP9808 sensor implementing the BCM2835
** Raspberry PI GPIO library functions.
**
** @author Copyrite (C) 2020 Brenton Salmi
** @version 0.1   Initial development release</replaceable>
** @modified 4/20/2020  Brenton Salmi  Initial release effort.</replaceable>
** @@
**
** This program is free software; you can redistribute it and/or
** modify it under the terms of the GNU General Public License
** as published by the Free Software Foundation; either version 3
** of the License, or (at your option) any later version.
** 
** This program is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU General Public License for more details.
** 
** You should have received a copy of the GNU General Public License
** along with this program; if not, write to the Free Software
** Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
********************************************************************/


/* ==================================================================== */
/* ========================== include files =========================== */
/* ==================================================================== */

#include <bcm2835.h>
#include "mcp9808_bcm2835.h"
#include <stdio.h>



/* ==================================================================== */
/* ============================ constants ============================= */
/* ==================================================================== */




/* ==================================================================== */
/* ======================== global variables ========================== */
/* ==================================================================== */





/* ==================================================================== */
/* ============================== data ================================ */
/* ==================================================================== */





/* ==================================================================== */
/* ==================== function prototypes =========================== */
/* ==================================================================== */




/* @prog MCP9808_BCM2835 ****************************************************
**
** A simple library implementing functions of the MCP9808 temperature 
** sensor via the BCM2835 raspberry pi library.
**
******************************************************************************/

//int main(int argc, char **argv)
//{
//}


/* ==================================================================== */
/* ============================ functions ============================= */
/* ==================================================================== */

int mcp9808_read_reg(int reg_addr, char* buf , int len)
{
	char tempwr[1] = {reg_addr};
	int mcp9808_reason_code;
	bcm2835_i2c_write(tempwr, 1);
	mcp9808_reason_code = bcm2835_i2c_read(buf, len);
	
	return 0;
	
}

int mcp9808_write_reg(int reg_addr, char databyte)
{
	char tempwr[2] = {reg_addr, databyte};
	int mcp9808_reason_code;
	bcm2835_i2c_write(tempwr, 2);	
	return 0;
}

float mcp9808_get_temp( void )
{
	char rxbuf[2]; //buffer for received values
	int temp_sign = 0;
	unsigned char temp_ta_high;
	unsigned char temp_ta_low;
	int temperature_1, test;
	float temperature_3;
	
	//MCP9808_BCM2835 Read Register Function
	mcp9808_read_reg(REG_TEMP, rxbuf, 2);
	
	// Parse temp register values
	temp_sign = (0b00010000 & rxbuf[0]) >> 4;
	temp_ta_high = 0b00001111 && rxbuf[0];
	temp_ta_low = rxbuf[1];
	
	if(temp_sign == 0){
		//Positive temp
		temperature_1 = (temp_ta_high<<8) | temp_ta_low;
		temperature_3 = (float) temperature_1/16;
	}
	else{
		// Negative temp
		temperature_1 = (temp_ta_high<<8) | temp_ta_low;
		temperature_3 = (float) temperature_1/16;
		temperature_3 = 256.0 - temperature_3;
	}

	return temperature_3;
}

void print_bin(int inputnum, int bitlen )
{
	int c, k;
	//printf("%d\n", inputnum);
	for (c=bitlen; c>=0; c--)
	{
		k=inputnum>>c;
		
		if(k&1)
			printf("1");
		else
			printf("0");
	}
	printf("\n");
}
