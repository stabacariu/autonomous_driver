/**
 * @file system_state.cpp
 * @author Sergiu-Petru Tabacariu
 * @date 6.12.2017
 */

#include "system_state.hpp"
#include "system_mode.hpp"
//~ #include "standby_mode.hpp"

void SystemState::setMode (SystemMode* m)
{
    mode = m;
    std::cout << "System state changed." << std::endl;
}

SystemMode* SystemState::getMode ()
{
    return mode;
}

void SystemState::start ()
{
    std::cout << "SYSTEM: Starting..." << std::endl;
    running = true;
    mode->start(this);
}

void SystemState::stop ()
{
    std::cout << "SYSTEM: Stopping..." << std::endl;
    running = false;
    if (mode->isRunning()) {
        mode->stop();
    }
}

bool SystemState::isRunning ()
{
    return running;
}
