/**
 * @file camera_calibration.hpp
 * @author Sergiu-Petru Tabacariu
 * @date 5.7.2017
 */

#ifndef CAMERA_CALIBRATION_HPP
#define CAMERA_CALIBRATION_HPP

#include <iostream>
#include <opencv2/opencv.hpp>

void calibrateIntrinsics (cv::Mat& image, cv::Mat& homography, cv::Size boardSize, double squareSize, int sampleCnt);
void calibrateExtrinsics (cv::Mat& image, cv::Mat& homography, cv::Size boardSize, double squareSize);
void showChessBoardCorners (cv::Mat& image, cv::Size boardSize);
void inversePerspectiveTransform(cv::Mat image, cv::Mat& warpedImage, cv::Mat homography);

#endif // CAMERA_CALIBRATION_HPP
