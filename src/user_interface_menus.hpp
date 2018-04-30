/**
 * @file user_interface_menus.hpp
 * @author Sergiu-Petru Tabacariu
 * @date 4.7.2017
 */

#ifndef USER_INTERFACE_MENUS_HPP
#define USER_INTERFACE_MENUS_HPP

#include <iostream>
//~ #incldue <sstream>
#include <opencv2/opencv.hpp>
#include "vehicle_data.hpp"
#include "lane_data.hpp"
#include "obstacle_data.hpp"

//! @addtogroup user_interface
//! @{

/**
 * @brief A function to draw a main menu to an image
 * 
 * This function draws a 200 px wide main menu on the left side of an image.
 * 
 * @param image Image matrix
 */
void drawMainMenu (cv::Mat& image);

/**
 * @brief A function to draw the autonomous mode menu to an image
 * 
 * This function draws a 200 px wide autonomous mode menu on the left side of an image.
 * 
 * @param image Image matrix
 */
void drawAutoMode (cv::Mat& image, VehicleData& vehicle, LaneData& lane, ObstacleData& obstacle);

/**
 * @brief A function to draw the remote control mode menu to an image
 * 
 * This function draws a 200 px wide remote control mode menu on the left side of an image.
 * 
 * @param image Image matrix
 * @param position
 */
void drawRcCom (cv::Mat& image, cv::Point position);

/**
 * @brief A function to draw the autonomous mode menu to an image
 * 
 * This function draws a 200 px wide autonomous mode menu on the left side of an image.
 * 
 * @param image Image matrix
 */
void drawRcMode (cv::Mat& image, VehicleData& vehicle);

/**
 * @brief A function to draw the configuration mode menu to an image
 * 
 * This function draws a 200 px wide configuration mode menu on the left side of an image.
 * 
 * @param image Image matrix
 */
void drawConfigMode (cv::Mat& image);

/**
 * @brief A function to draw the intrinsics calibration mode menu to an image
 * 
 * This function draws a 200 px wide intrinsics calibration mode menu on the left side of an image.
 * 
 * @param image Image matrix
 */
void drawCalibIntrinsics (cv::Mat& image);

/**
 * @brief A function to draw the extrinsics mode menu to an image
 * 
 * This function draws a 200 px wide extrinsics mode menu on the left side of an image.
 * 
 * @param image Image matrix
 */
void drawCalibExtrinsics (cv::Mat& image);

/**
 * @brief A function to draw the image positioning mode menu to an image
 * 
 * This function draws a 200 px wide image positioning mode menu on the left side of an image.
 * 
 * @param image Image matrix
 */
void drawPositionImage (cv::Mat& image);

/**
 * @brief A function to draw the about mode menu to an image
 * 
 * This function draws a 200 px wide about mode menu on the left side of an image.
 * 
 * @param image Image matrix
 */
void drawAboutMode (cv::Mat& image);

/**
 * @brief A function to draw the error mode menu to an image
 * 
 * This function draws a 200 px wide error mode menu on the left side of an image.
 * 
 * @param image Image matrix
 */
void drawErrorMode (cv::Mat& image);

//! @} user_interface

#endif // USER_INTERFACE_MENUS_HPP
