/**
 * @file image_filter.hpp
 * @author Sergiu-Petru Tabacariu
 * @date 30.6.2017
 */

#ifndef IMAGE_FILTER_HPP
#define IMAGE_FILTER_HPP

#include <iostream>
#include <opencv2/opencv.hpp>

/**
 * @brief A function to auto adjust image brightness
 * 
 * This function adjusts the image brightness by spreding intensity levels.
 * 
 * @param image
 */
void autoAdjustBrightness (cv::Mat& image);

/**
 * @brief A funtion to filter white "color"
 * 
 * This function filters white "color" out of an RGB image.
 * 
 * @param image
 * @param filteredImage
 */
void whiteColorFilter (cv::Mat image, cv::Mat& filteredImage);

/**
 * @brief A function to filter yellow color
 * 
 * This function filters yellow color. It converts a RGB image to HSV
 * color space.
 * 
 * @param image
 * @param filteredImage
 */
void yellowColorFilter (cv::Mat image, cv::Mat& filteredImage);

#endif // IMAGE_FILTER_HPP
