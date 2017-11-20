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

void calibIntr (cv::Mat image, cv::Mat& cameraMatrix, cv::Mat& distCoeffs, cv::Size calibPatternDim, double calibPatternSize, int sampleCnt);
void calibExtr (cv::Mat image, cv::Mat& homography, cv::Size calibPatternDim, double calibPatternSize);
void showChessBoardCorners (cv::Mat& image, cv::Size calibPatternDim);
void adjustImagePosition (cv::Mat image, cv::Mat& adjustedImage, char key, cv::Mat& homography);
float calcPixelPerMm (cv::Mat image, cv::Size calibPatternDim, float calibPatternSize);

#endif // CAMERA_CALIBRATION_HPP
