/**
 * @file camera_capture.hpp
 * @author Sergiu-Petru Tabacariu
 * @date 30.6.2017
 */

/**
 * @defgroup camera Camera
 * @brief A module to calibrates a camera and captures an image.
 * @{
 *     @defgroup camera_capture Camera Capture
 *     @defgroup camera_calibration Camera Calibration
 * @}
 */

#ifndef CAMERA_CAPTURE_HPP
#define CAMERA_CAPTURE_HPP

#include <iostream>
#include <opencv2/opencv.hpp>
#include "configuration.hpp"
#include "autonomous_driver.hpp"
#include "image_data.hpp"

//! @addtogroup camera_capture
//! @brief A module to caputure a camera image
//! @{

/**
 * @brief Thread for capturing a camera image
 * 
 * This function implements a thread that captures an image from a webcam.
 * 
 * @param arg Input arguments
 */
void *cameraCapture (void *arg);

//! @} camera_capture

#endif // CAMERA_CAPTURE_HPP
