/**
 * @file main.cpp
 * @author Sergiu-Petru Tabacariu
 * @date 27.6.2017
 * 
 * @mainpage An autonomous driving development platform
 * 
 * This program is an autonomous driving development platform for a model
 * car. It offers a ready to go autonomous driving system and
 * functions for custom system development.
 * 
 * The autonomous driver system is designed to work with a generic USB
 * webcam, a Raspberry Pi 2/3, a PWM-servo-module and an ultrasonic sensor.
 * The driving base is an off-the-shelf ready-to-run remote controlled model
 * car with an ESC, a brushed driving motor and a servo steering motor.
 * The radio controller of the R/C car is replaced with the PWM-servo-module.
 * This module is connected to the Raspberry Pi 3 and communicates via I2C
 * with it.
 */

#include <iostream>
#include <csignal>
#include <opencv2/opencv.hpp>
#include "autonomous_driver.hpp"

AutonomousDriver app;

void signalHandler (int signal)
{
    std::cout << "ERROR: Signal caught: " << signal << std::endl;
    //! @todo Change state to error
    app.quit();
}

void exceptionHandler (const char* errMsg)
{
    std::cerr << "ERROR: Exception caught: " << errMsg << std::endl;
    //! @todo Change state to error
    app.quit();
}

/**
 * @brief The main function is the programs starting point
 * 
 * The main funnction initializes the configuration, the system state
 * machine and the user interface. Then it starts the system state machine.
 * 
 * @param argc The input argument counter
 * @param argv The input argument vector
 * @return System state value
 */
int main (int argc, char *argv[])
{
    std::signal(SIGINT, signalHandler);
    std::signal(SIGTERM, signalHandler);
    
    try {
        // Start system
        app.exec();
    }
    catch (cv::Exception& e) {
        exceptionHandler(e.what());
        app.quit();
    }
    
    
    return 0;
}
