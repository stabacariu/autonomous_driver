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
#include <opencv2/opencv.hpp>
#include <pthread.h>
#include "autonomous_driver.hpp"
#include "vehicle_control.hpp"

//! @addtogroup remote_control
//! @{

/**
 * @brief A thread to remote control a model vehicle
 * 
 * This thread enables user controling a model vehicle remotly.
 * The key w is used for acceleration.
 * The key s is used for reducing speed and for accalarating backwards.
 * The key a is used for steering to the left.
 * The key d is used for steering to the right.
 * The spacebar is used for breaking.
 * 
 * @param arg Input argument
 */
void *remoteControl (void *arg);

//! @} remote_control

#endif // REMOTE_CONTROL_HPP
