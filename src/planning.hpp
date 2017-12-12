/**
 * @file planning.hpp
 * @author Sergiu-Petru Tabacariu
 * @date 25.8.2017
 */

/**
 * @defgroup planning Path planning
 * @{
 * @}
 */

#ifndef PLANNING_HPP
#define PLANNING_HPP

#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/tracking.hpp>
#include <pthread.h>
#include "autonomous_driver.hpp"
#include "lane_detection.hpp"
#include "vehicle_control.hpp"
#include "vehicle.hpp"

//! @addtogroup planning Path planning
//! @{

/**
 * @brief A thread to plan and drive a long a path
 * 
 * This thread plans a path according to a detected lane makring. It then
 * sets a certain acceleration and steering angle.
 * 
 * @param arg Input argument
 */
void *pathPlanning (void *arg);

/**
 * @brief A thread to plan and drive a long a path
 * 
 * @note This thread is for experimental use only!
 * 
 * This thread plans a path according to a detected lane makring. It then
 * sets a certain acceleration and steering angle.
 * 
 * @param arg Input argument
 */
void *pathPlanning2 (void *arg);

//! @} planning

#endif // PLANNING_HPP
