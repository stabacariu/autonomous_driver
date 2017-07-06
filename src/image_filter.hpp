/**
 * @file image_filter.hpp
 * @author Sergiu-Petru Tabacariu
 * @date 30.6.2017
 */

#ifndef IMAGE_FILTER_HPP
#define IMAGE_FILTER_HPP

#include <iostream>
#include <opencv2/opencv.hpp>

void autoAdjustImage (cv::Mat& image);
void whiteColorFilter (cv::Mat image, cv::Mat& filteredImage);
void yellowColorFilter (cv::Mat image, cv::Mat& filteredImage);

#endif // IMAGE_FILTER_HPP
