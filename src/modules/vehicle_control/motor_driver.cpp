/**
 * @file motor_driver.cpp
 * @author Sergiu-Petru Tabacariu
 * @date 30.8.2017
 */
 
#include "motor_driver.hpp"

bool MotorDriver::init ()
{
    if (pwmModule.init(1, 0x40)) {
        pwmModule.setPWMFreq(50);
        pwmModule.setPWM(ESC, ESC_N);
        std::this_thread::sleep_for(std::chrono::seconds(3));
        initFlag = true;
        return true;
    }
    else {
        std::cerr << "ERROR: Couldn't ínitialize motor driver!" << std::endl;
        return false;
    }
}

void MotorDriver::setSteering (int value)
{
    if (initFlag) {
        pwmModule.setPWM(STEERING, value);
    }
}

void MotorDriver::setAcceleration (int value)
{
    if (initFlag) {
        pwmModule.setPWM(ESC, value);
    }
}

void MotorDriver::reset (void)
{
    if (initFlag) {
        pwmModule.setPWM(STEERING, 0);
        pwmModule.setPWM(ESC, 0);
        pwmModule.reset();
    }
}


