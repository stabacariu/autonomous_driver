/**
 * @file motor_driver.hpp
 * @author Sergiu-Tabacariu
 * @date 30.6.2017
 */

#ifndef MOTOR_DRIVER_HPP
#define MOTOR_DRIVER_HPP

#include <iostream>
#include <pthread.h>

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

enum MotorDriverCom {
    MOTOR_DRIVER_I2C,
    MOTOR_DRIVER_SERIAL,
    MOTOR_DRIVER_CAN
};

struct MotorDriver {
    int com;
    int direction;
    int steering;
    pthread_mutex_t lock;
};

#endif // MOTOR_DRIVER_HPP