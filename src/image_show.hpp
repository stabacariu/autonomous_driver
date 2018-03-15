/**
 * @file image_show.hpp
 * @author Sergiu-Petru Tabacariu
 * @date 24.10.2017
 */

#ifndef IMAGE_SHOW_HPP
#define IMAGE_SHOW_HPP

#include <iostream>
#include <pthread.h>
#include <ctime>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include "autonomous_driver.hpp"
#include "image_data.hpp"
#include "camera_capture.hpp"
#include "user_interface.hpp"

//! @addtogroup user_interface
//! @{

/**
 * @brief A thread to show the input image
 * 
 * This thread show an input image captured by a camera.
 * 
 * @param arg Input arguments
 */
void *showInputImage (void *arg);

/**
 * @brief A thread to show the output image
 * 
 * This thread show an output image captured by a camera.
 * 
 * @param arg Input arguments
 */
void *showOutputImage (void *arg);

//! @} user_interface

#endif // IMAGE_SHOW_HPP
