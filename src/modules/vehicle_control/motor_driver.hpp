/**
 * @file motor_driver.hpp
 * @author Sergiu-Tabacariu
 * @date 30.6.2017
 */

#ifndef MOTOR_DRIVER_HPP
#define MOTOR_DRIVER_HPP

#include <iostream>
#include <mutex>
#include <thread>
#include <chrono>
#include <wiringPi.h>
#include "PCA9685.h"

//! @addtogroup motor_driver
//! @{

/**
 * @brief An enum with PWM steering boundaries
 */
enum SteeringPWM {
    STEERING = 0,
    STEERING_MIN = 204,
    STEERING_MAX = 409,
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
 * @brief A class for the motor driver direction and acceleration
 */
class MotorDriver {
public:
    ~MotorDriver() = default;
    
    /**
     * @brief Initialize motor driver
     * 
     * This function initializes the motor driver.
     * 
     * @return Init done
     */
    bool init ();
    
    /**
     * @brief Set steering motor value
     * 
     * This function sets the steering motor value.
     * 
     * @param value Steering value from 0 to 4095
     */
    void setSteering (int value);
    
    /**
     * @brief Get steering motor value
     * 
     * This function gets the steering motor value.
     * 
     * @return Steering value beween 0 to 4095
     */
    int getSteering (void);
    
    /**
     * @brief Set acceleration motor value
     * 
     * This function sets the acceleration motor value.
     * 
     * @param value Acceleration value from 0 to 4095
     */
    void setAcceleration (int value);
    
    /**
     * @brief Get acceleration motor value
     * 
     * This function gets the acceleration motor value.
     * 
     * @return acceleration value beween 0 to 4095
     */
    int getAcceleration (void);
    
    /**
     * @brief A function to reset the motor driver
     * 
     * This function resets the motor driver.
     */
    void reset (void);
    
    /**
     * @brief A function to stop the motor driver
     * 
     * This function stops the motor driver.
     */
    void stop (void);
    
private:
    PCA9685 pwmModule; //!< PWM Motor driver
    int outputEnablePin {0}; //! WiringPi pin number
    int steering {STEERING_STRAIGHT}; //!< VehicleDirection from 0 to 4095
    int acceleration {ESC_N}; //!< Accerelration from 0 to 4095
    bool initFlag {false};
    //~ std::mutex lock; //!< Mutex lock for synchronized access
};

//! @} motor_driver

#endif // MOTOR_DRIVER_HPP
