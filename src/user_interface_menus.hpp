/**
 * @file user_interface_menus.hpp
 * @author Sergiu-Petru Tabacariu
 * @date 4.7.2017
 */

#ifndef USER_INTERFACE_MENUS_HPP
#define USER_INTERFACE_MENUS_HPP

#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>

void drawMainMenu (cv::Mat& image);
void drawAutoMode (cv::Mat& image);
void drawRcCom (cv::Mat& image, cv::Point position);
void drawRcMode (cv::Mat& image);
void drawDevMode (cv::Mat& image);
void drawConfigMode (cv::Mat& image);

#endif // USER_INTERFACE_MENUS_HPP
