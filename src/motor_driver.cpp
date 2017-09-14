/**
 * @file motor_driver.cpp
 * @author Sergiu-Petru Tabacariu
 * @date 30.8.2017
 */
 
#include "motor_driver.hpp"
#include <unistd.h>

PCA9685 pwmModule;

void initMotorDriver (void)
{
    pwmModule.init(1,0x40);
    pwmModule.setPWMFreq(50);
    pwmModule.setPWM(ESC, ESC_N);
    usleep(1000);
    // delay_ms(5000); // Doesn't work!!!
}

void setSteeringValue (int direction)
{
    pwmModule.setPWM(STEERING, direction);
}

void setAccelerationValue (int acceleration)
{
    pwmModule.setPWM(ESC, acceleration);
}

void resetMotorDriver (void)
{
    pwmModule.setPWM(STEERING, 0);
    pwmModule.setPWM(ESC, 0);
    pwmModule.reset();
}


