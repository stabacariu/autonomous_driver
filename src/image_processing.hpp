/**
 * @file image_processing.hpp
 * @author Sergiu-Petru Tabacariu
 * @date 30.6.2017
 */

#ifndef IMAGE_PROCESSING_HPP
#define IMAGE_PROCESSING_HPP

#include <iostream>
#include <pthread.h>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include "autonomous_driver.hpp"
#include "image_data.hpp"
#include "camera_capture.hpp"
#include "lane_detection.hpp"
#include "traffic_sign_detection.hpp"
#include "user_interface.hpp"

void imageProcessing (void);
void *imageShow (void *arg);

#endif // IMAGE_PROCESSING_HPP
