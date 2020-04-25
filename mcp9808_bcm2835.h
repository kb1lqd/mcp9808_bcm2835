// Register definitions
#define REG_RFU 0x00
#define REG_CONFIG 0x01
#define REG_ALERT_TUPPER 0x02
#define REG_ALERT_TLOWER 0x03
#define REG_TCRIT 0x04
#define REG_TEMP 0X05
#define REG_MANUFACTURER_ID 0X06
#define REG_DEVICE_ID 0x07 
#define REG_RESOLUTION 0X08

// Resolution mode definitions
#define RESOLUTION_0C5 0x00
#define RESOLUTION_0C25 0x01
#define RESOLUTION_0C125 0x02
#define RESOLUTION_0C0625 0x03

int mcp9808_read_reg(int reg_addr, char* buf , int len);
int mcp9808_write_reg(int reg_addr, char databyte);
float mcp9808_get_temp( void );
void print_bin(int inputnum, int bitlen );
