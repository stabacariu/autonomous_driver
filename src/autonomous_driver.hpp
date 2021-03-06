/**
 * @file autonomous_driver.hpp
 * @author Sergiu-Petru Tabacariu
 * @date 6.4.2018
 */

#ifndef AUTONOMOUS_DRIVER_HPP
#define AUTONOMOUS_DRIVER_HPP

#include <iostream>
#include <atomic>
#include "system_state.hpp"
#include "standby_mode.hpp"

/**
 * @brief An autonomous driving appilcation class
 * 
 * This class defines an autonomous driving application.
 */
class AutonomousDriver {
public:
    ~AutonomousDriver() = default;
   
    /**
     * @brief Execute system
     * 
     * This function executes the system. It launches the set state.
     */
    void exec (void);
    
    /**
     * @brief Quit system
     * 
     * This function quits the system. It stops all running modes and
     * with that all running modules.
     */
    void quit (void);
    
private:
    SystemState state {new StandbyMode()}; //!< Current system state
};

#endif // AUTONOMOUS_DRIVER_HPP
