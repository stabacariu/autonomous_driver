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
#include <opencv2/opencv.hpp>
#include "vehicle_data.hpp"
#include "motor_driver.hpp"

//! @addtogroup vehicle_control
//! @{

class VehicleControler {
public:
    ~VehicleControler() = default;
    
    /**
     * @brief Start vehicle control
     * 
     * This function starts the vehicle control thread.
     * This thread controls the vehicle by converting given values and
     * sending them to the motor driver.
     * 
     * @param vehicle Vehicle to control
     */
    void start (VehicleData& vehicle);
    
    /**
     * @brief Stop vehicle control
     * 
     * This function stops the vehicle control thread.
     */
    void stop (void);
    
    /**
     * @brief Check if vehicle control is running
     * 
     * This function checks if the vehicle control is running…
     * 
     * @return True if vehicle control is running, else false.
     */
    bool isRunning (void);
    
private:
    bool running {false}; //!< Thread running flag
};

//! @} vehicle_control

#endif // VEHICLE_CONTROL_HPP
