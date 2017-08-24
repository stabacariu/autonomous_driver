/**
 * @file lane_detection.hpp
 * @author Sergiu-Petru Tabacariu
 * @date 30.6.2017
 */

#ifndef LANE_DETECTION_HPP
#define LANE_DETECTION_HPP

#include <iostream>
#include <pthread.h>
#include <opencv2/opencv.hpp>
#include "autonomous_driver.hpp"
#include "image_data.hpp"
#include "image_filter.hpp"
#include "camera_calibration.hpp"

void *laneDetection (void *arg);

void initLinePrediction (cv::KalmanFilter& kf, int valueCnt);
void predictLine (std::vector<cv::Vec4i> lines, cv::KalmanFilter& kf, int valueCnt, std::vector<cv::Vec4i>& measuredLines, std::vector<cv::Vec4i>& predictedLines);

#endif // LANE_DETECTION_HPP
