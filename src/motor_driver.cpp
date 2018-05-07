/**
 * @file motor_driver.cpp
 * @author Sergiu-Petru Tabacariu
 * @date 30.8.2017
 */
 
#include "motor_driver.hpp"

MotorDriver::MotorDriver ()
{
    pwmModule.init(1, 0x40);
    pwmModule.setPWMFreq(50);
    pwmModule.setPWM(ESC, ESC_N);
    std::this_thread::sleep_for(std::chrono::seconds(3));
}

void MotorDriver::setSteering (int value)
{
    pwmModule.setPWM(STEERING, value);
}

void MotorDriver::setAcceleration (int value)
{
    pwmModule.setPWM(ESC, value);
}

void MotorDriver::reset (void)
{
    pwmModule.setPWM(STEERING, 0);
    pwmModule.setPWM(ESC, 0);
    pwmModule.reset();
}


