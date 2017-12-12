/**
 * @file vehicle_control.hpp
 * @author Sergiu-Petru Tabacariu
 * @date 3.7.2017
 */

/**
 * @defgroup vehicle_control Vehicle Control
 * @{
 *     @defgroup vehicle Vehicle
 *     @defgroup motor_driver Motor driver
 * @}
 */

#ifndef VEHICLE_CONTROL_HPP
#define VEHICLE_CONTROL_HPP

#include <iostream>
#include <opencv2/opencv.hpp>
#include "autonomous_driver.hpp"
#include "vehicle.hpp"
#include "motor_driver.hpp"

//! @addtogroup vehicle_control
//! @{

/**
 * @brief A thread to control the vehicle
 * 
 * This thread controls the vehicle by converting given values and
 * sending them to the motor driver.
 * 
 * @param arg Input arguments
 */
void *vehicleControl (void* arg);

//! @} vehicle_control

#endif // VEHICLE_CONTROL_HPP
