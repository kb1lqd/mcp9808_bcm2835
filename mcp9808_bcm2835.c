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


