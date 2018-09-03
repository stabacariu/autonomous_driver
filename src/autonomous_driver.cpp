/**
 * @file autonomous_driver.cpp
 * @author Sergiu-Petru Tabcariu
 * @date 6.4.2018
 */

#include "autonomous_driver.hpp"
#include "configuration.hpp"

void AutonomousDriver::exec ()
{
    // Load config file to configurator instance
    Configurator& config = Configurator::instance("../config/config.xml");
    //~ Configurator& config = Configurator::instance(); //< Load default.xml
    config.load();
    
    state.run();
    
    while (state.isRunning()) {
        state.run();
    }
    
    quit();
}

void AutonomousDriver::quit ()
{
    if (state.isRunning()) {
        state.quit();
    }
}
