/**
 * @file vehicle_control.hpp
 * @author Sergiu-Petru Tabacariu
 * @date 3.7.2017
 */

/**
 * @defgroup vehicle_control Vehicle Control
 * @{
 *     @defgroup vehicle_data Vehicle Data
 *     @defgroup motor_driver Motor driver
 * @}
 */

#ifndef VEHICLE_CONTROL_HPP
#define VEHICLE_CONTROL_HPP

#include <iostream>
#include <atomic>
#include <opencv2/opencv.hpp>
#include "trajectory_data.hpp"
#include "vehicle_data.hpp"
#include "motor_driver.hpp"

//! @addtogroup vehicle_control
//! @{

class VehicleController {
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
    
    /**
     * @brief Quit vehicle control
     * 
     * This function quits the vehicle control thread.
     */
    void quit (void);
    
    /**
     * @brief Check if vehicle control is running
     * 
     * This function checks if the vehicle control is running…
     * 
     * @return True if vehicle control is running, else false.
     */
    bool isRunning (void);
    
private:
    std::atomic_bool running {false}; //!< Thread running flag
};


//! @} vehicle_control

#endif // VEHICLE_CONTROL_HPP
