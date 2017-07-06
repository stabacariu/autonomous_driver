/**
 * @file camera_capture.hpp
 * @author Sergiu-Petru Tabacariu
 * @date 30.6.2017
 */

#ifndef CAMERA_CAPTURE_HPP
#define CAMERA_CAPTURE_HPP

#include <iostream>
#include <opencv2/opencv.hpp>
#include "autonomous_driver.hpp"
#include "image_data.hpp"

//void cameraCaptureInit (void);
void *cameraCapture (void *v);

#endif // CAMERA_CAPTURE_HPP
