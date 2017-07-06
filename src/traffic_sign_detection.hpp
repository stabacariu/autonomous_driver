/**
 * @file traffic_sign_detection.hpp
 * @author Sergiu-Petru Tabacariu
 * @date 30.6.2017
 */

#ifndef TRAFFIC_SIGN_DETECTION_HPP
#define TRAFFIC_SIGN_DETECTION_HPP

#include <iostream>
#include <pthread.h>
#include <opencv2/opencv.hpp>

void *trafficSignDetection (void *arg);

#endif // TRAFFIC_SIGN_DETECTION_HPP
