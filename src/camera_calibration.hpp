/**
 * @file camera_calibration.hpp
 * @author Sergiu-Petru Tabacariu
 * @date 5.7.2017
 */

#ifndef CAMERA_CALIBRATION_HPP
#define CAMERA_CALIBRATION_HPP

#include <iostream>
#include <opencv2/opencv.hpp>
#include "configuration.hpp"

//! @addtogroup camera_calibration
//! @brief A module to calibrate a camera
//! @{

/**
 * @brief A function calibrate intrinsic camera parameters
 * 
 * This function calibrates intrinsic camera parameters by searching for chessboard pattern
 * 
 * @param image Image captured by the camera
 * @param cameraMatrix Pointer to camera matrix where result is stored
 * @param distCoeffs Pointer to matrix where distortion coefficents are stored
 * @param calibPatternSize Calibration pattern dimensions
 * @param calibPatternMm Calibration pattern size in mm
 * @param sampleCnt Sample capturing counter
 */
void calibIntr (cv::Mat image, cv::Mat& cameraMatrix, cv::Mat& distCoeffs, cv::Size calibPatternSize, double calibPatternMm, int sampleCnt);

/**
 * @brief A function calibrate extrinsic camera parameters
 * 
 * This function calibrates extrinsic camera parameters by searching for a chessboard pattern
 * 
 * @param image Image captured by the camera
 * @param homography Perspective transform homography matrix
 * @param calibPatternSize Calibration pattern dimensions
 * @param calibPatternMm Calibration pattern size in mm
 */
void calibExtr (cv::Mat image, cv::Mat& homography, cv::Size calibPatternSize, double calibPatternMm);

/**
 * @brief A function to draw chessboard on an image.
 * 
 * This function draws a chessboard on an image.
 * 
 * @param image Input and output image
 * @param calibPatternSize Calibration pattern dimensions
 */
void showChessBoardCorners (cv::Mat& image, cv::Size calibPatternSize);

/**
 * @brief A function to adjust image position in frame.
 * 
 * This function adjusts an image position inside an image frame.
 * 
 * @param image Input image
 * @param adjustedImage Adjusted output image
 * @param key User input key
 * @param homography Perspective transform homography matrix
 */
void adjustImagePosition (cv::Mat image, cv::Mat& adjustedImage, char key, cv::Mat& homography);

/**
 * @brief A function to calculate how many pixels are in 1 mm.
 * 
 * This function calculates how many pixels are in 1 millimeter.
 * It finds the corners of a captured chessboard image and calculates the
 * average distance between each chessboard field.
 * 
 * @param image Input and output image
 * @param calibPatternSize Calibration pattern dimensions
 * @param calibPatternMm Calibration pattern size in mm
 */
float calcPixelPerMm (cv::Mat image, cv::Size calibPatternSize, float calibPatternMm);

//! @} camera_calibration

#endif // CAMERA_CALIBRATION_HPP
