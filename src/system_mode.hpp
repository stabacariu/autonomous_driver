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
    ~SystemMode () = default;
    
    virtual void start (SystemState* s) = 0;
    virtual void stop (void) = 0;
    virtual bool isRunning (void) { return running; };

protected:
    bool running {false};
};

//! @} system_modes

#endif // SYSTEM_MODE_HPP
