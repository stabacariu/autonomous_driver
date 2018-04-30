/**
 * @file autonomous_driver.cpp
 * @author Sergiu-Petru Tabcariu
 * @date 6.4.2018
 */

#include "autonomous_driver.hpp"

void AutonomousDriver::exec ()
{
    running = true;
    
    state.start();
    
    while (state.isRunning()) {
        state.start();
    }
    
    quit();
}

void AutonomousDriver::quit ()
{
    running = false;
    if (state.isRunning()) {
        state.stop();
    }
}
