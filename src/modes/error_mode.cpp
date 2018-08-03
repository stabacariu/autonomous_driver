/**
 * @file error_mode.cpp
 * @author Sergiu-Petru Tabacariu
 * @date 5.4.2018
 */

#include "error_mode.hpp"
#include "closing_mode.hpp"

void ErrorMode::run (SystemState* s)
{
    //! @todo Implement Error mode
    std::cout << "---------------------------------" << std::endl;
    std::cout << "MODE: Error Mode started." << std::endl;
    running = true;
    
    quit();
    s->setMode(new ClosingMode());
    delete this;
}

void ErrorMode::quit ()
{
    running = false;
    std::cout << "MODE: Error Mode stopped." << std::endl;
}

