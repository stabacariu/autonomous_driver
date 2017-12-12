/**
 * @file traffic_sign_detection.hpp
 * @author Sergiu-Petru Tabacariu
 * @date 30.6.2017
 */

/**
 * @defgroup traffic_sign_detection Traffic Sign Detection
 * @{
 * @}
 */

#ifndef TRAFFIC_SIGN_DETECTION_HPP
#define TRAFFIC_SIGN_DETECTION_HPP

#include <iostream>
#include <pthread.h>
#include <opencv2/opencv.hpp>
#include "autonomous_driver.hpp"
#include "image_data.hpp"
#include "configuration.hpp"

//! @addtogroup traffic_sign_detection
//! @{

/**
 * @brief Thread for traffic sign detection
 *
 * This thread detects traffic signs with Haar cascade classification.
 * It uses a pretrained model with is stored in "input/*.xml".
 * 
 * @param arg Input argument
 */
void *trafficSignDetection (void *arg);

//! @} traffic_sign_detection

#endif // TRAFFIC_SIGN_DETECTION_HPP
