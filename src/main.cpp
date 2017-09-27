/**
 * @file main.cpp
 * @author Sergiu-Petru Tabacariu
 * @date 27.6.2017
 * 
 * @brief A autonomous driving development platform software
 * 
 * This program is an autonomous driving system for a model car.
 */

#include <iostream>
#include "autonomous_driver.hpp"
#include "user_interface.hpp"

int main (int argc, char *argv[])
{
    // Startup
    // Init system state
    initSystemState();
    initUiState();
    
    // Start system
    autonomousDriver();
    
    return 0;
}
