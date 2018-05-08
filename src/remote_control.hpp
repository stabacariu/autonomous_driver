/**
 * @file remote_control.hpp
 * @author Sergiu-Petru Tabacariu
 * @date 11.10.2017
 */

/**
 * @defgroup remote_control Remote Control
 * @{
 * @}
 */

#ifndef REMOTE_CONTROL_HPP
#define REMOTE_CONTROL_HPP

#include <iostream>
#include <atomic>
#include <opencv2/opencv.hpp>
#include "user_interface.hpp"
#include "vehicle_data.hpp"

//! @addtogroup remote_control
//! @{

class RemoteController {
public:
    ~RemoteController() = default;
    
    /**
     * @brief Run remote control the system
     * 
     * This thread enables user to control the system remotly.
     * The key w is used for acceleration.
     * The key s is used for reducing speed and for accalarating backwards.
     * The key a is used for steering to the left.
     * The key d is used for steering to the right.
     * The spacebar is used for breaking.
     * 
     * @param ui User interface
     * @param vehicle Vehicle data
     */
    void run (VehicleModel& vehicle, UserInterfaceState& uiState);
    
    /**
     * @brief Quit remote control the system
     * 
     * This function quits remote control.
     */
    void quit (void);
    
    /**
     * @brief Check if remote controling is running
     * 
     * This function checks if the remote controling is running.
     * 
     * @return True if remote controling is running, else false.
     */
    bool isRunning (void);
    
private:
    std::atomic_bool running {false}; //!< Thread running flag
};

//! @} remote_control

#endif // REMOTE_CONTROL_HPP
