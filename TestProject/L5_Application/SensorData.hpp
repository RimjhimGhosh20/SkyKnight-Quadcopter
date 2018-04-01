/*
 * SensorData.hpp
 *
 *  Created on: Apr 1, 2017
 *      Author: Admin
 */

#ifndef L5_APPLICATION_SENSORDATA_HPP_
#define L5_APPLICATION_SENSORDATA_HPP_

#include <stdint.h>
#include <stdio.h>
#include "utilities.h"
#include <iostream>
#include <stdlib.h>
#include "i2c2.hpp"

void initSensor(volatile float &yawAngleInitial);
void get_pitch(volatile float &pitch);
void get_roll(volatile float &rollAngle);
void get_yaw(volatile float &yawAngle,volatile float &yawAngleInitial);




#endif /* L5_APPLICATION_SENSORDATA_HPP_ */
