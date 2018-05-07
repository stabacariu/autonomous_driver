/**
 * @file closing_mode.cpp
 * @author Sergiu-Petru Tabacariu
 * @date 5.4.2018
 */

#include "closing_mode.hpp"

void ClosingMode::run (SystemState* s)
{
    std::cout << "---------------------------------" << std::endl;
    std::cout << "MODE: Closing Mode started." << std::endl;
    running = true;
    
    //~ resetMotorDriver();
    quit();
    s->quit();
}

void ClosingMode::quit ()
{
    running = false;
    std::cout << "MODE: Quitting closing mode..." << std::endl;
}

