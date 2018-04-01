/*
 * PID.cpp
 *
 *  Created on: Apr 1, 2017
 *      Author: Admin
 */
#include "PID.hpp"



/* Pitch variables */
float error_pitch = 0, lasterror_pitch = 0, set_pitch = 0;
float errorIntegralPitch[6] = {0};
float sumIntegralPitch = 0;

/* Roll variables */
float error_roll = 0, lasterror_roll = 0, set_roll = 0;
float errorIntegralRoll[6] = {0};
float sumIntegralRoll = 0;

/* Yaw variables */
float error_yaw = 0, lasterror_yaw = 0, set_yaw = 0;
float errorIntegralYaw[6] = {0};
float sumIntegralYaw = 0;

float FR_TELEM = 0;
float FL_TELEM = 0;


void PID_Algorithm_Pitch(bool &BlueToothStartStopFlag,bool &BlueToothStopFlag,int &BluetoothDirectionFlag,bool &ThrottleIncrease,bool &ThrottleDecrease,bool& restoreValueFlag, uint32_t &count,float &pitchAngle,float &rollAngle,float &yawAngle)
{
	static PWM FR(PWM::pwm1,400.0);
	static PWM FL(PWM::pwm2,400.0);
	static PWM BR(PWM::pwm3,400.0);
	static PWM BL(PWM::pwm4,400.0);

	if(count < 300)
	{
		FR.set(40);
		FL.set(40);
		BR.set(40);
		BL.set(40);
	}
	else
	{
		if(BlueToothStartStopFlag)
		{
			PID_Function(BluetoothDirectionFlag,BlueToothStopFlag,ThrottleIncrease,ThrottleDecrease);

			FR_DCPWM = 50;
			FL_DCPWM = 50;
			BR_DCPWM = 50;
			BL_DCPWM = 50;

			error_pitch = ((pitchAngle) - set_pitch);

			P_Pitch = 0;
			errorIntegralPitch[5] = error_pitch;

			I_Pitch = (sumIntegralPitch * 0.01);

			D_Pitch = (lasterror_pitch)/0.01;
			float n = P_Pitch * 0.4 + D_Pitch * 0.01 + I_Pitch * 5;

			lasterror_pitch = error_pitch;
			FR_DCPWM -= n;
			FL_DCPWM -= n;
			BR_DCPWM += n;
			BL_DCPWM += n;

		}
		else
		{
			FR.set(40);
			FL.set(40);
			BR.set(40);
			BL.set(40);


			lasterror_pitch = 0;
			for(int i = 0; i < 6; i++)
			{
				errorIntegralPitch[i] = 0;
			}
			set_pitch = 0;
		}
	}
}

void PID_Algorithm_Roll(bool &BlueToothStartStopFlag,bool &BlueToothStopFlag,int &BluetoothDirectionFlag,bool &ThrottleIncrease,bool &ThrottleDecrease, uint32_t &count,float &pitchAngle,float &rollAngle,float &yawAngle)
{
	static PWM FR(PWM::pwm1,400.0);
	static PWM FL(PWM::pwm2,400.0);
	static PWM BR(PWM::pwm3,400.0);
	static PWM BL(PWM::pwm4,400.0);

	if(count < 300)
	{
		FR.set(40);
		FL.set(40);
		BR.set(40);
		BL.set(40);
	}
	else
	{
		if(BlueToothStartStopFlag)
		{

			error_roll = ((rollAngle) - set_roll );

			P_Roll = error_roll;

			errorIntegralRoll[5] = error_roll;
			sumIntegralRoll = 0;
			for(int i = 0; i < 6; i++)
			{
				sumIntegralRoll = abs(errorIntegralRoll[i]);
			}


			I_Roll = (sumIntegralRoll * 0.01);

			D_Roll = (error_roll)/0.01;


			float n = P_Roll * 0.4 + D_Roll * 0.01 + I_Roll * 5;

			n = 0.11 * n;

			lasterror_roll = error_roll;
			FR_DCPWM += n;
			FL_DCPWM += n;
			BR_DCPWM += n;
			BL_DCPWM -= n;





		}
		else
		{
			FR.set(40);
			FL.set(40);
			BR.set(40);
			BL.set(40);
			lasterror_roll = 0;
			for(int i = 0; i < 6; i++)
			{
				errorIntegralRoll[i] = 0;
			}
			set_roll = 0;
		}
	}

}



void PID_Algorithm_Yaw(bool &BlueToothStartStopFlag,bool &BlueToothStopFlag,int &BluetoothDirectionFlag,bool &ThrottleIncrease,bool &ThrottleDecrease, uint32_t &count,float &pitchAngle,float &rollAngle,float &yawAngle)
{
	static PWM FR(PWM::pwm1,400.0);
	static PWM FL(PWM::pwm2,400.0);
	static PWM BR(PWM::pwm3,400.0);
	static PWM BL(PWM::pwm4,400.0);

	if(count < 300)
	{
		FR.set(40);
		FL.set(40);
		BR.set(40);
		BL.set(40);
	}
	else
	{
		if(BlueToothStartStopFlag)
		{
			error_yaw = ((yawAngle) - set_yaw);

			P_Yaw = error_yaw;

			errorIntegralYaw[5] = error_yaw;
			sumIntegralYaw = 0;

			I_Yaw = (sumIntegralYaw * 0.01);

			D_Yaw = (error_yaw)/0.01;


			float n = P_Yaw * 0.01 + D_Yaw * 0.049 + I_Yaw * 0.5;

			n = 0.11 * n;

			lasterror_yaw = error_yaw;
			FR_DCPWM += n;
			FL_DCPWM -= n;
			BR_DCPWM -= n;
			BL_DCPWM -= n;


			FR.set(FR_DCPWM);
			FL.set(FL_DCPWM);
			BR.set(BR_DCPWM);
			BL.set(BL_DCPWM);

			LE.on(1);

		}

	}




}

void PID_Function(int &BluetoothDirectionFlag,bool &BlueToothStopFlag,bool &ThrottleIncrease,bool &ThrottleDecrease)
{


	if(BlueToothStopFlag == true)
	{
		baseVal -= 0.005;
	}

	if (BluetoothDirectionFlag == 3)
	{
		set_pitch = 8;
		set_roll = 0;
		set_yaw = 0;  // Forward
		printf("Forward.....\n");
	}
	else if (BluetoothDirectionFlag == 4)
	{
		set_pitch = 0;
		set_roll = 5;
		set_yaw = 0;// Right

		printf("Right.....\n");
	}
	else if (BluetoothDirectionFlag == 5)
	{
		set_pitch = 0;
		set_roll = -8;
		set_yaw = 0; //Left
		printf("Left.....\n");
	}
	else if (BluetoothDirectionFlag == 6)
	{
		set_pitch = -5;
		set_roll = 0;
		set_yaw = 0; //Back
		printf("Back.....\n");
	}

}



void ESC_CALIB(uint32_t& count)
{
	static PWM FR(PWM::pwm1,400.0);
	static PWM FL(PWM::pwm2,400.0);
	static PWM BR(PWM::pwm3,400.0);
	static PWM BL(PWM::pwm4,400.0);
	if(count < 30)
	{
		FR.set(80);
		FL.set(80);
		BR.set(80);
		BL.set(80);
	}
	else if(count >= 30 && count < 60)
	{
		FR.set(40);
		FL.set(40);
		BR.set(40);
		BL.set(40);
	}

}


