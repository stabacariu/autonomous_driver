/**
 * @file camera_capture.hpp
 * @author Sergiu-Petru Tabacariu
 * @date 30.6.2017
 */

#ifndef CAMERA_CAPTURE_HPP
#define CAMERA_CAPTURE_HPP

#include <iostream>
#include <opencv2/opencv.hpp>
#include "configuration.hpp"
#include "autonomous_driver.hpp"
#include "image_data.hpp"

/**
 * @brief Thread for capturing a camera image
 * 
 * This function implements a thread that captures an image from a webcam.
 * 
 * @param void
 * @return void
 */
void *cameraCapture (void *arg);

#endif // CAMERA_CAPTURE_HPP
