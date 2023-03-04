#include "LTR390.h"

/******************************************************************************
  function:	Send one byte of data to  I2C dev
  parameter:
            Addr: Register address
            Value: Write to the value of the register
  Info:
******************************************************************************/
static void LTR390_Write(UBYTE cmd, UBYTE val)
{
	I2C_Write_Byte(cmd, val);
}

/******************************************************************************
  function:	 read one byte of data to  I2C dev
  parameter:
            Addr: Register address
  Info:
******************************************************************************/
static UBYTE LTR390_Read(UBYTE val)
{
	return I2C_Read_Byte(val);
}


/******************************************************************************
  function:	TSL2591 Initialization
  parameter:
  Info:
******************************************************************************/
UBYTE LTR390_Init(void)
{
//	DEV_ModuleInit();
//	DEV_I2C_Init(LTR390_ADDR << 1);

	printf("LTR390 VOC Sensor Init\r\n");

	//ID
	UBYTE Rdata = LTR390_Read(0x06);
	if(Rdata != 0xb2) { 
		printf("should = 0xb2, but val = 0X%d\r\n", Rdata);
		return 1;
	}

    LTR390_Write(LTR390_MEAS_RATE, RESOLUTION_18BIT_TIME100MS | RATE_100MS);// default
    LTR390_Write(LTR390_GAIN, GAIN_3); //default
    
	return 0;
}

UDOUBLE LTR390_UVS(void)
{
    LTR390_Write(LTR390_INT_CFG, 0x34); // UVS_INT_EN=1, Command=0x34
    LTR390_Write(LTR390_MAIN_CTRL, 0x0A); //  UVS in Active Mode
    UDOUBLE Data1 = LTR390_Read(LTR390_UVSDATA);
    UDOUBLE Data2 = LTR390_Read(LTR390_UVSDATA + 1);
    UDOUBLE Data3 = LTR390_Read(LTR390_UVSDATA + 2);
    UDOUBLE uv;
    uv =  (Data3<<16)| (Data2<<8) | Data1;
    return uv;
}

UDOUBLE LTR390_ALS(void)
{
    LTR390_Write(LTR390_INT_CFG, 0x34); // UVS_INT_EN=1, Command=0x34
    LTR390_Write(LTR390_MAIN_CTRL, 0x0A); //  UVS in Active Mode
    UDOUBLE Data1 = LTR390_Read(LTR390_UVSDATA);
    UDOUBLE Data2 = LTR390_Read(LTR390_UVSDATA + 1);
    UDOUBLE Data3 = LTR390_Read(LTR390_UVSDATA + 2);
    UDOUBLE als;
    als =  (Data3<<16)| (Data2<<8) | Data1;
    return als; 
}

void LTR390_SetIntVal(UDOUBLE low, UDOUBLE high)//LTR390_THRESH_UP and LTR390_THRESH_LOW
{
    LTR390_Write(0x21, high&0xff);
    LTR390_Write(0x22, (high>>8)&0xff);
    LTR390_Write(0x23, (high>>16)&0x0f);
    LTR390_Write(0x24, low&0xff);
    LTR390_Write(0x25, (low>>8)&0xff);
    LTR390_Write(0x26, (low>>16)&0x0f);
}


