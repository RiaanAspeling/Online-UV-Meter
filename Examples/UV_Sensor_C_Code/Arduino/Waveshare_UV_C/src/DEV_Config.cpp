/*****************************************************************************
* | File      	:   DEV_Config.c
* | Author      :   Waveshare team
* | Function    :   Hardware underlying interface
* | Info        :
*----------------
* |	This version:   V2.0
* | Date        :   2019-07-08
* | Info        :   Basic version
*
******************************************************************************/
#include "DEV_Config.h"

uint8_t DEV_SPI_Device = 0, DEV_I2C_Device = 0;
uint8_t I2C_ADDR;
/******************************************************************************
function:	GPIO Function initialization and transfer
parameter:
Info:
******************************************************************************/
void DEV_GPIO_Mode(UWORD Pin, UWORD mode)
{
	/*
	    0:  INPT
	    1:  OUTP
	*/
	if(mode == INPUT || mode == 0) {
		pinMode(Pin, INPUT);
	} else if(mode == OUTPUT || mode == 1) {
		pinMode(Pin, OUTPUT);
	}
}


/**
 * delay x ms
**/
void DEV_Delay_ms(UDOUBLE xms)
{
	delay(xms);
}


void GPIO_Config(void)
{
	//DEV_GPIO_Mode(INT_PIN, 0);
}

/******************************************************************************
function:	I2C Function initialization and transfer
parameter:
Info:
******************************************************************************/
void DEV_I2C_Init(uint8_t Add)
{
#if DEV_I2C
	DEV_I2C_Device = 1;
	I2C_ADDR =  Add;
	Wire.begin();
#endif
}

void I2C_Write_Byte(uint8_t Cmd, uint8_t value)
{
#if DEV_I2C
	Wire.beginTransmission(I2C_ADDR);
	Wire.write(Cmd);
	Wire.write(value & 0xFF);
	Wire.endTransmission();
#endif
}

int I2C_Read_Byte(uint8_t Cmd)
{
#if DEV_I2C
	Wire.beginTransmission(I2C_ADDR);
	Wire.write(Cmd);
	Wire.endTransmission();
    
    Wire.requestFrom(I2C_ADDR, 1, 1);
    
	if (Wire.available()) {
		return Wire.read();
	}
    
	return 0;
#endif
}

int I2C_Read_Word(uint8_t Cmd)
{
#if DEV_I2C
	uint16_t x;
	uint16_t t;

	Wire.beginTransmission(I2C_ADDR);
	Wire.write(Cmd);
	Wire.endTransmission();
	// Wire.requestFrom(I2C_ADDR, 2);
	t = Wire.read();
	x = Wire.read();
	x <<= 8;
	x |= t;
	return x;
#endif
}

void I2C_Write_Nbyte(UBYTE *data, UBYTE num)
{
#if DEV_I2C
	Wire.beginTransmission(I2C_ADDR);
	Wire.write(data, num);
	// UBYTE i = 0;
	// for(i = 0; i < num; i++){
	// Wire.write(data[i]);
	// }

	Wire.endTransmission();
#endif
}

UWORD I2C_Read_Nbyte(UBYTE Cmd, UBYTE num)
{
#if DEV_I2C
	Wire.beginTransmission(I2C_ADDR);
	Wire.write(Cmd);
	// Wire.endTransmission();
	Wire.requestFrom(I2C_ADDR, num);

	UBYTE rbuf[num];
	UBYTE i = 0;
	for(i = 0; i < num; i++) {
		rbuf[i] =  Wire.read();
	}
	Wire.endTransmission();
	UWORD data = 0;
	data = (rbuf[0] << 8) | rbuf[1];
	return data;
#endif
}


/******************************************************************************
function:	Module Initialize, the library and initialize the pins, SPI protocol
parameter:
Info:
******************************************************************************/
UBYTE DEV_ModuleInit(void)
{
	Serial.begin(115200);
	return 0;
}

/******************************************************************************
function:	Module exits, closes SPI and BCM2835 library
parameter:
Info:
******************************************************************************/
void DEV_ModuleExit(void)
{

}
