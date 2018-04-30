/**
 * @file closing_mode.cpp
 * @author Sergiu-Petru Tabacariu
 * @date 5.4.2018
 */

#include "closing_mode.hpp"

void ClosingMode::start (SystemState* s)
{
    std::cout << "---------------------------------" << std::endl;
    std::cout << "MODE: Closing Mode started." << std::endl;
    running = true;
    
    //~ resetMotorDriver();
    stop();
    s->stop();
}

void ClosingMode::stop ()
{
    running = false;
    std::cout << "MODE: Closing Mode stopped." << std::endl;
}

