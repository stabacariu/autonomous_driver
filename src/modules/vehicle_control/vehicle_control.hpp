/**
 * @file vehicle_control.hpp
 * @author Sergiu-Petru Tabacariu
 * @date 3.7.2017
 */

/**
 * @ingroup module
 * @defgroup vehicle_control Vehicle Control
 * @brief A module to control the vehicle state
 */

#ifndef VEHICLE_CONTROL_HPP
#define VEHICLE_CONTROL_HPP

#include <iostream>
#include <atomic>
#include <opencv2/opencv.hpp>
#include "module.hpp"
#include "trajectory_data.hpp"
#include "vehicle_data.hpp"
#include "motor_driver.hpp"

//! @addtogroup vehicle_control
//! @{

class VehicleController : public Module {
public:
    ~VehicleController() = default;
    
    /**
     * @brief Run vehicle control
     * 
     * This function runs the vehicle control thread.
     * This thread controls the vehicle by converting given values and
     * sending them to the motor driver.
     * 
     * @param trajectory Trajectory data
     * @param vehicle Vehicle to control
     */
    void run (TrajectoryData& trajectory, VehicleModel& vehicle);
};


//! @} vehicle_control

#endif // VEHICLE_CONTROL_HPP
