/**
 * @file system_state.hpp
 * @author Sergiu-Petru Tabacariu
 * @date 10.4.2018
 */

#ifndef SYSTEM_STATE_HPP
#define SYSTEM_STATE_HPP

#include <iostream>
#include <thread>
#include <atomic>

class SystemMode; //!< Forward declaration

/**
 * @brief A system state class
 * 
 * This class describes the system state of the autonomous driver.
 */
class SystemState {
public:
    SystemState (SystemMode* m) : mode(m) {};
    ~SystemState () = default; //!< Default destructor
    
    /**
     * @brief Set the system state
     * 
     * This function sets the system state. First it locks the state
     * information resource.
     * 
     * @param state Reference to new system state to be set
     */
    void setMode (SystemMode* m);
    
    /**
     * @brief Get the system state
     * 
     * This function gets the actual system state. First it locks the
     * state information resource.
     * 
     * @return The referance to the system state
     */
    SystemMode* getMode (void);
    
    /**
     * @brief Start system state
     * 
     * This function starts the system state. It runs the set system
     * mode.
     */
    void start (void);
    
    /**
     * @brief Stop system state
     * 
     * This function stops the system state. It stops the running system
     * mode.
     */
    void stop (void);
    
    /**
     * @brief Is system running
     * 
     * This function checks if the system is running.
     * 
     * @return True if system is running, else false.
     */
    bool isRunning (void);
    
private:
    SystemMode* mode; //!< Actual system mode
    std::atomic_bool running {false}; //!< Running flag
};

#endif // SYSTEM_STATE_HPP
