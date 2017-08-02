/**
 * @file main.cpp
 * @author Sergiu-Petru Tabacariu
 * @date 27.6.2017
 * 
 * @brief This program is an autonomous driving system for a model car.
 */

#include <iostream>
#include "autonomous_driver.hpp"
#include "user_interface.hpp"
#include "image_processing.hpp"

int main (int argc, char *argv[])
{
    // TODO: Write code:
    // Init system state
    systemStateInit();
    uiStateInit();
    // Load config
    
    // Start image acquisition
    //~ imageAcquisition();
    // Start image aquisition
    imageProcessing();
    // Start UI
    
    return 0;
}
