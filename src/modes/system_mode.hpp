/**
 * @file    system_mode.hpp
 * @author  Sergiu-Petru Tabacariu
 * @date    5.5.2018
 */

/**
 * @defgroup system_modes System Modes
 * @{
 *      @defgroup standby_mode Standby Mode
 *      @defgroup autonomous_driving_mode Autonomous Driving Mode
 *      @defgroup remote_control_mode Remote Control Mode
 *      @defgroup configuration_mode  Configuration Mode
 *      @defgroup about_mode About Mode
 *      @defgroup error_mode Error Mode
 *      @defgroup closing_mode Closing Mode
 * @}
 */

#ifndef SYSTEM_MODE_HPP
#define SYSTEM_MODE_HPP

#include <atomic>
#include "system_state.hpp"

//! @addtogroup system_modes
//! @brief Modes for the autonomous driving system
//! @{

/**
 * @brief A system mode abstract class
 * 
 * This class is a system mode abstract class for interfacing system modes.
 */
class SystemMode {
public:
    virtual ~SystemMode () = default;
    
    /**
     * @brief Run system mode
     * 
     * This function runs the system mode.
     * 
     * @param s System state pointer
     */
    virtual void run (SystemState* s) = 0;
    
    /**
     * @brief Quit system mode
     * 
     * This function quits the system mode.
     */
    virtual void quit (void) = 0;
    
    /**
     * @brief Check if system mode is running
     * 
     * This function checks if the system mode is running.
     * 
     * @return True if system mode is running, else false.
     */
    virtual bool isRunning (void) { return running; };

protected:
    std::atomic_bool running {false}; //!< Running flag
    std::atomic_bool error {false}; //!< Error flag
};

//! @} system_modes

#endif // SYSTEM_MODE_HPP
