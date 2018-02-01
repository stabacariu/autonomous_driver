/**
 * @file motor_driver.cpp
 * @author Sergiu-Petru Tabacariu
 * @date 30.8.2017
 */
 
#include "motor_driver.hpp"

PCA9685 pwmModule;

void initMotorDriver (void)
{
    pwmModule.init(1,0x40);
    pwmModule.setPWMFreq(50);
    pwmModule.setPWM(ESC, ESC_N);
    // delay_ms(10000); //!< @todo delay function doesn't work!
    // usleep(3*USEC_PER_SEC);
    //~ sleep(3);
    std::this_thread::sleep_for(std::chrono::seconds(3));
}

void setSteeringValue (int steering)
{
    pwmModule.setPWM(STEERING, steering);
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


