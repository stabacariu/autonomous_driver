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

//! @addtogroup motor_driver
//! @{

/**
 * @brief An enum with PWM steering boundaries
 */
enum SteeringPWM {
    STEERING = 0,
    STEERING_MIN = 204,
    STEERING_MAX = 409,
    STEERING_MID = 307,
    STEERING_LEFT = STEERING_MIN,
    STEERING_RIGHT = STEERING_MAX,
    STEERING_STRAIGHT = (STEERING_MIN+(STEERING_MAX-STEERING_MIN)/2)
};

/**
 * @brief An enum with PWM ESC boundaries
 */
enum ESCPWM {
    ESC = 1,
    ESC_MIN = 204,
    ESC_MAX = 409,
    ESC_D = 358,
    ESC_R = 250,
    ESC_N = (ESC_MIN+(ESC_MAX-ESC_MIN)/2)
};

/**
 * @brief An enum for motor driver driving direction
 */
enum MotorDriverDirection {
    MOTOR_DRIVER_DIRECTION_NONE,
    MOTOR_DRIVER_DIRECTION_FORWARD,
    MOTOR_DRIVER_DIRECTION_BACKWARD
};

/**
 * @brief An enum for motor driver steering direction
 */
enum MotorDriverSteering {
    MOTOR_DRIVER_STEERING_NONE,
    MOTOR_DRIVER_STEERING_STRAIGHT,
    MOTOR_DRIVER_STEERING_LEFT,
    MOTOR_DRIVER_STEERING_RIGHT
};

/**
 * @brief A struct for the motor driver direction and acceleration
 */
struct MotorDriver {
    int direction;      //!< Direction from 0 to 4095
    int acceleration;   //!< Accerelration from 0 to 4095
    pthread_mutex_t lock; //!< Mutex lock for synchronized access
};

/**
 * @brief A function to initialize motor driver
 * 
 * This function initializes the motor driver
 */
void initMotorDriver (void);

/**
 * @brief A function to set the steering value
 * 
 * This function sets the steering value from 0 to 4095.
 * 
 * @param steering Steering value from 0 to 4095
 */
void setSteeringValue (int steering);

/**
 * @brief A function to set the acceleration value
 * 
 * This function sets the acceleration value from 0 to 4095.
 * 
 * @param acceleration Acceleration value from 0 to 4095
 */
void setAccelerationValue (int acceleration);

/**
 * @brief A function to reset the motor driver
 * 
 * This function resets the motordriver.
 */
void resetMotorDriver (void);

//! @} motor_driver

#endif // MOTOR_DRIVER_HPP
