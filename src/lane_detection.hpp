/**
 * @file lane_detection.hpp
 * @author Sergiu-Petru Tabacariu
 * @date 30.6.2017
 */

#ifndef LANE_DETECTION_HPP
#define LANE_DETECTION_HPP

#include <iostream>
#include <fstream>
#include <pthread.h>
#include <opencv2/opencv.hpp>
#include <opencv2/tracking.hpp>
#include "autonomous_driver.hpp"
#include "image_data.hpp"
#include "image_filter.hpp"
#include "camera_calibration.hpp"
#include "lane.hpp"

void *laneDetection (void *arg);
void *laneDetection2 (void *arg);
void *laneDetection3 (void *arg);

/**
 * Line prediction with Kalman filterLines
 */
void initLinePrediction (cv::KalmanFilter& kf, int valueCnt);
void predictLine (std::vector<cv::Vec4i> lines, cv::KalmanFilter& kf, int valueCnt, std::vector<cv::Vec4i>& predLines);

/**
 * @brief This function calculates the distance rho for the polar line form.
 *  (rho, theta)
 * @param pt point on the line
 * @param rho slope of the line
 * @return r the distance of the line to the origin for the polar form
 */
float getRho (cv::Point pt1, cv::Point pt2);

/**
 * @brief This function calculates the angle theta for the polar line form.
 *  (rho, theta)
 * @param pt1 starting point of the line
 * @param pt2 ending point of the line
 * @return theta the angle for the polar form
 */
float getTheta (cv::Point pt1, cv::Point pt2);

cv::Vec4i getLaneMid (std::vector<cv::Vec4i> lane);

void drawArrowedLine (cv::Mat& image, cv::Vec4i l, cv::Scalar color);

#endif // LANE_DETECTION_HPP
