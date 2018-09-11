/**
 * @file    module.hpp
 * @author  Sergiu-Petru Tabacariu
 * @date    5.6.2018
 */

/**
 * @defgroup module Modules
 * @brief Autonomous Driving System modules
 */
 
#ifndef MODULE_HPP
#define MODULE_HPP

#include <atomic>

//! @addtogroup module
//! @{

/**
 * @brief A module interface class
 * 
 * This class defines an module acquistor interface.
 */
class Module {
public:
    ~Module() = default;
    
    /**
     * @brief Run module
     * 
     * This function runs a module. Implement this function end start it
     * as thread.
     */
    //~ virtual void run (void) = 0;
    
    /**
     * @brief Quit module
     * 
     * This function quits the module.
     */
    virtual void quit (void) { running = false; };
    
    /**
     * @brief Checks if module is running
     * 
     * This function checks if the module is running.
     * 
     * @return True if module is running, else false.
     */
    virtual bool isRunning (void) { return running; };
    
    /**
     * @brief Checks if module error has occurred
     * 
     * This function checks if a module error has occurred.
     * 
     * @return True if module error, else false.
     */
    virtual bool isError (void) { return error; };
    
protected:
    std::atomic_bool running {false};
    std::atomic_bool error {false};
};

//! @} module

#endif // MODULE_HPP
