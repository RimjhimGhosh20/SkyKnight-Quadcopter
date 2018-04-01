/*
 * PID.hpp
 *
 *  Created on: Apr 1, 2017
 *      Author: Admin
 */

#ifndef L5_APPLICATION_PID_HPP_
#define L5_APPLICATION_PID_HPP_

#include <stdint.h>
#include <stdio.h>
#include "utilities.h"
#include "io.hpp"
#include <iostream>
#include <stdlib.h>
#include "lpc_pwm.hpp"

/* Pitch variables */
static float P_Pitch = 0;
static float D_Pitch = 0;
static float I_Pitch = 0;

/* Roll variables */
static float P_Roll = 0;
static float D_Roll = 0;
static float I_Roll = 0;

/* Yaw variables */
static float P_Yaw = 0;
static float D_Yaw = 0;
static float I_Yaw = 0;

static float initialBaseVal = 55;
static float baseVal = initialBaseVal;
static float FR_DCPWM = 40;
static float FL_DCPWM = 40;
static float BR_DCPWM = 40;
static float BL_DCPWM = 40;



void PID_Algorithm_Pitch(bool &BlueToothStartStopFlag,bool &BlueToothStopFlag,int &BluetoothDirectionFlag,bool &ThrottleIncrease,bool &ThrottleDecrease,bool& restoreValueFlag, uint32_t &count,float &pitchAngle,float &rollAngle,float &yawAngle);
void PID_Algorithm_Roll(bool &BlueToothStartStopFlag,bool &BlueToothStopFlag,int &BluetoothDirectionFlag,bool &ThrottleIncrease,bool &ThrottleDecrease, uint32_t &count,float &pitchAngle,float &rollAngle,float &yawAngle);
void PID_Algorithm_Yaw(bool &BlueToothStartStopFlag,bool &BlueToothStopFlag,int &BluetoothDirectionFlag,bool &ThrottleIncrease,bool &ThrottleDecrease, uint32_t &count,float &pitchAngle,float &rollAngle,float &yawAngle);
void PID_Function(int &BluetoothDirectionFlag,bool &BlueToothStopFlag,bool &ThrottleIncrease,bool &ThrottleDecrease);
void ESC_CALIB(uint32_t& count);




#endif /* L5_APPLICATION_PID_HPP_ */
