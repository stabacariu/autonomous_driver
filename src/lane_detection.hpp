/**
 * @file lane_detection.hpp
 * @author Sergiu-Petru Tabacariu
 * @date 30.6.2017
 */
 
/**
 * @defgroup lane_detection Lane Detection
 * @{
 * 
 * @}
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

//! @addtogroup lane_detection Lane Detection
//! @{

/**
 * @brief A function to initialize a Kalman filter for line prediction
 * 
 * This function initializes a Kalman filter to predict lines found in
 * an input image.
 * 
 * @param kf Kalman filter
 * @param valueCnt Values to predict
 */
void initLinePrediction (cv::KalmanFilter& kf, int valueCnt);

/**
 * @brief A function to predict position of lines
 * 
 * This function predicts the line positions found in an input image.
 * It corrects the prediction by considering vector of found/measured
 * lines.
 * 
 * @param lines Vector of lines describet by starting and and ending point
 * @param kf Kalman filter
 * @param valueCnt Values to predict
 * @param predLines Vector of predicted lines
 */
void predictLine (std::vector<cv::Vec4i> lines, cv::KalmanFilter& kf, int valueCnt, std::vector<cv::Vec4i>& predLines);

/**
 * @brief A function to calculate the distance &rho; of a line to the origin
 * 
 * This function calculates the distance &rho; of a line to the origin in
 * polar form (&rho;, &theta;).
 * 
 * @param pt1 Starting point of line
 * @param pt2 Ending point of line
 * @return The distance &rho; of the line to the origin in polar form
 */
float getRho (cv::Point pt1, cv::Point pt2);

/**
 * @brief A function to calculate the orthogonal angle &theta; of the
 * slope of a line in relation to the origin 
 * 
 * This function calculates the orthogonal angle &theta; of the slope 
 * of a line in in relation to the origin for the polar form
 * (&rho;, &theta;).
 * 
 * @param pt1 Starting point of the line
 * @param pt2 Ending point of the line
 * @return The orthogonal angle &theta; of the line to the origin for the polar form
 */
float getTheta (cv::Point pt1, cv::Point pt2);

/**
 * @brief A function to get the middle line of a lane
 * 
 * This function gets the middle line of a lane as starting and ending
 * point.
 * 
 * @param lane Lane as vector of zwo lines with starting and ending point
 * @return Middle line as starting and ending point
 */
cv::Vec4i getLaneMid (std::vector<cv::Vec4i> lane);

/**
 * @brief A function to draw an arrowed line
 * 
 * This function draws an arrowed line on an input image with a color.
 * 
 * @param image Image matrix
 * @param l Line vector with starting and ending point
 * @param color Line color as RGB scalar value
 */
void drawArrowedLine (cv::Mat& image, cv::Vec4i l, cv::Scalar color);

/**
 * @brief A thread to detect a lane
 * 
 * This thread detects a lane in an input image.
 * 
 * @param arg Input argument
 */
void *laneDetection (void *arg);

/**
 * @brief A thread to detect a lane
 * 
 * @note This function is experimental
 * 
 * @param arg Input argument
 */
void *laneDetection2 (void *arg);

/**
 * @brief A thread to detect a lane
 * 
 * @note This function is experimental
 * 
 * @param arg Input argument
 */
void *laneDetection3 (void *arg);

//! @} lane_detection

#endif // LANE_DETECTION_HPP
