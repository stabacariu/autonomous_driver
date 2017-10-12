/**
 * @file motor_driver.hpp
 * @author Sergiu-Tabacariu
 * @date 30.6.2017
 */

#ifndef MOTOR_DRIVER_HPP
#define MOTOR_DRIVER_HPP

#include <iostream>
#include <ctime>
#include <unistd.h>
#include "timer_tools.hpp"
#include "../lib/PCA9685.h"

#define STEERING 0
#define STEERING_MIN 204
#define STEERING_MAX 409
#define STEERING_MID 307
#define STEERING_LEFT STEERING_MIN
#define STEERING_RIGHT STEERING_MAX
#define STEERING_STRAIGHT (STEERING_MIN+(STEERING_MAX-STEERING_MIN)/2)

#define ESC 1
#define ESC_MIN 204
#define ESC_MAX 409
#define ESC_D 358
#define ESC_R 250
#define ESC_N (ESC_MIN+(ESC_MAX-ESC_MIN)/2)

enum MotorDriverDirection {
    MOTOR_DRIVER_DIRECTION_NONE,
    MOTOR_DRIVER_DIRECTION_FORWARD,
    MOTOR_DRIVER_DIRECTION_BACKWARD
};

enum MotorDriverSteering {
    MOTOR_DRIVER_STEERING_NONE,
    MOTOR_DRIVER_STEERING_STRAIGHT,
    MOTOR_DRIVER_STEERING_LEFT,
    MOTOR_DRIVER_STEERING_RIGHT
};

struct MotorDriver {
    int direction;      //!< Direction from 0 to 4095
    int acceleration;   //!< Accerelration from 0 to 4095
    pthread_mutex_t lock;
};

void initMotorDriver (void);
void setSteeringValue (int direction);
void setAccelerationValue (int acceleration);
void resetMotorDriver (void);

#endif // MOTOR_DRIVER_HPP
