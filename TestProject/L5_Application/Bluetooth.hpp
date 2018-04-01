/*
 * Bluetooth.hpp
 *
 *  Created on: Apr 1, 2017
 *      Author: Admin
 */

#ifndef L5_APPLICATION_BLUETOOTH_HPP_
#define L5_APPLICATION_BLUETOOTH_HPP_
#include <stdint.h>
#include <stdio.h>
#include "utilities.h"
#include <iostream>
#include <stdlib.h>
#include "uart3.hpp"

void uartInit();
void setupBT();
void BT(bool &BlueToothStartStopFlag, int &BluetoothDirectionFlag,bool &ThrottleIncrease,bool &ThrottleDecrease,bool& restoreValueFlag);





#endif /* L5_APPLICATION_BLUETOOTH_HPP_ */
