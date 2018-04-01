/*
 * SensorData.cpp/
 *
 *  Created on: Apr 1, 2017
 *      Author: Admin
 */
#include "SensorData.hpp"

char reg_address; //command register
char dev_address; //device address
uint8_t dataMSB;
uint8_t dataLSB;
uint16_t data;

I2C2& i2c2 = I2C2::getInstance();


void initSensor(volatile float &yawAngleInitial)
{
	dev_address = 0x60;
	reg_address = 0x85;
	bool flag3 = i2c2.writeReg(dev_address,reg_address,0x14);
	dev_address = 0x43;
	reg_address = 0x54;
	dataMSB = i2c2.readReg(dev_address,reg_address);
	reg_address = 0x1A;
	dataLSB = i2c2.readReg(dev_address,reg_address);
	data = ((dataMSB & 0xFFFF) << 8) | dataLSB;
	yawAngleInitial = (float)data/7.9;
}


void get_pitch(volatile float &pitchAngle)
{

	dev_address = 0x60;

	reg_address = 0x5D;
	dataMSB = i2c2.readReg(dev_address,reg_address);
	reg_address = 0x1F;
	dataLSB = i2c2.readReg(dev_address,reg_address);
	data = ((dataMSB & 0xFFFF) << 8) | dataLSB;
	pitchAngle = (float)data/1.96;
	if(pitchAngle > 8000)
		pitchAngle = -(5002 - pitchAngle);
	pitchAngle = pitchAngle - 1.5;
}

void get_roll(volatile float &rollAngle)
{
	dev_address = 0x60;
	reg_address = 0x1A;
	dataMSB = i2c2.readReg(dev_address,reg_address);
	reg_address = 0x17;
	dataLSB = i2c2.readReg(dev_address,reg_address);
	data = ((dataMSB & 0xFFFF) << 8) | dataLSB;
	if(data > 60000)
		rollAngle = (65536 - (float)data)/9.89;
	else
		rollAngle = -1 * (float)data/9.89;
	rollAngle = rollAngle - 0.2;
}

void get_yaw(volatile float &yawAngle,volatile float &yawAngleInitial)
{
	dev_address = 0x51;
	reg_address = 0x1B;
	dataMSB = i2c2.readReg(dev_address,reg_address);
	reg_address = 0x1A;
	dataLSB = i2c2.readReg(dev_address,reg_address);
	data = ((dataMSB & 0xFFFF) << 8) | dataLSB;
	yawAngle = (float)data/5.9972;
	if(yawAngle < yawAngleInitial)
		yawAngle = 320 + yawAngle - yawAngleInitial;
	else
		yawAngle = yawAngle - yawAngleInitial;
	if(yawAngle > 150)
		yawAngle = yawAngle - 320;

}




