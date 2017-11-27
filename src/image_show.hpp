/**
 * @file image_show.hpp
 * @author Sergiu-Petru Tabacariu
 * @date 24.10.2017
 */

#ifndef IMAGE_SHOW_HPP
#define IMAGE_SHOW_HPP

#include <iostream>
#include <pthread.h>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include "autonomous_driver.hpp"
#include "image_data.hpp"
#include "camera_capture.hpp"
#include "user_interface.hpp"

bool compareImage (const cv::Mat m1, const cv::Mat m2);

void *showInputImage (void *arg);
void *showOutputImage (void *arg);

#endif // IMAGE_SHOW_HPP
