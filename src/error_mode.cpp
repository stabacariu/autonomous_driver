/**
 * @file error_mode.cpp
 * @author Sergiu-Petru Tabacariu
 * @date 5.4.2018
 */

#include "error_mode.hpp"
#include "closing_mode.hpp"

void ErrorMode::start (SystemState* s)
{
    //! @todo Implement Error mode
    std::cout << "---------------------------------" << std::endl;
    std::cout << "MODE: Error Mode started." << std::endl;
    running = true;
    
    s->setMode(new ClosingMode());
    delete this;
}

void ErrorMode::stop ()
{
    //! @todo Implement Error mode
    running = false;
    std::cout << "MODE: Error Mode stopped." << std::endl;
}

