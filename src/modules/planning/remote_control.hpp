/**
 * @file remote_control.hpp
 * @author Sergiu-Petru Tabacariu
 * @date 11.10.2017
 */

/**
 * @ingroup planning
 * @defgroup remote_control Remote Control
 * @brief A module to remote control the system by an user
 */

#ifndef REMOTE_CONTROL_HPP
#define REMOTE_CONTROL_HPP

#include <iostream>
#include <atomic>
#include <opencv2/opencv.hpp>
#include "module.hpp"
#include "user_interface.hpp"
#include "vehicle_data.hpp"

//! @addtogroup remote_control
//! @{

class RemoteController : public Module {
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
     * @param vehicle Vehicle data
     * @param uiState User interface
     */
    void run (VehicleModel& vehicle, UserInterfaceState& uiState);
};

//! @} remote_control

#endif // REMOTE_CONTROL_HPP
