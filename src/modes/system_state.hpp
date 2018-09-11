/**
 * @file system_state.hpp
 * @author Sergiu-Petru Tabacariu
 * @date 10.4.2018
 */

/**
 * @defgroup system_state System State
 * @brief The system state
 */

#ifndef SYSTEM_STATE_HPP
#define SYSTEM_STATE_HPP

#include <iostream>
#include <thread>
#include <atomic>

//! @addtogroup system_state
//! @{

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
     * @param m Reference to new system state to be set
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
     * @brief Run system state
     * 
     * This function runs the system state.
     */
    void run (void);
    
    /**
     * @brief Quit system state
     * 
     * This function quits the system state. It quits the running system
     * mode.
     */
    void quit (void);
    
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

//! @} system_state

#endif // SYSTEM_STATE_HPP
