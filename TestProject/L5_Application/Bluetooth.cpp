/*
 * Bluetooth.cpp
 *
 *  Created on: Apr 1, 2017
 *      Author: Admin
 */

#include "Bluetooth.hpp"
Uart3 *u3 = &(Uart3::getInstance());



void uartInit()
{
	u3->init(38400, 1000, 1000);
	u3->flush();
}

void setupBT()
{
	int i = 0;
	delay_ms(3000);
	while(1)
	{
		i++;
		if(i >= 3)
		{
			//printf("BTSETUP");
			i = 0;
			break;
		}

	}
}

void BT(bool &BlueToothStartStopFlag, int &BluetoothDirectionFlag,bool &ThrottleIncrease,bool &ThrottleDecrease,bool& restoreValueFlag)
{
	char c;
	//printf("\nBluetooth Command Received");
	while(u3->getChar(&c, 100))
	{
		//printf("\nBluetooth Command:%c",c);
		if(c == 'R')
		{
			BlueToothStartStopFlag = true;


		}
		else if(c == 'S')
		{
			BlueToothStartStopFlag = false;

		}
		else if (c == 'F')
		{
			BluetoothDirectionFlag = 3;

		}
		else if (c == 'Y')
		{
			BluetoothDirectionFlag = 4;
		}
		else if (c == 'L')
		{
			BluetoothDirectionFlag = 5;
			//printf("L received \n");
		}
		else if (c == 'B')
		{
			BluetoothDirectionFlag = 6;
		}
		else if (c == 'G' )
		{
			BluetoothDirectionFlag = 0;
			//printf(" G received\n");

		}
		else if( c == 'D')
		{

			ThrottleDecrease = true;
			ThrottleIncrease = false;

		}
		else if( c == 'I')
		{
			ThrottleIncrease = true;
			ThrottleDecrease = false;
		}
		else if( c == 'K')
		{
			BlueToothStartStopFlag = false;


		}
		else
		{
			BluetoothDirectionFlag = 0;
			printf(" ELSE \n");

		}

	}

}



