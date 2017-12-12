/**
 * @file obstacle_detection.hpp
 * @author Sergiu-Petru Tabacariu
 * @date 4.12.2017
 */

/**
 * @defgroup obstacle_detection Obstacle Detectiom
 * @{
 * @}
 */

#ifndef OBSTACLE_DETECTION_HPP
#define OBSTACLE_DETECTION_HPP

#include <iostream>
#include <pthread.h>
#include <wiringPi.h>
#include <opencv2/opencv.hpp>
#include "../lib/libSonar.h"

//! @addtogroup obstacle_detection
//! @{

/**
 * @brief A struct to describe a detected obstacle
 * 
 * This structure describes the detected obstacle data.
 */
struct ObstacleData {
    double distance; //!< Distance from camera to the object
    double velocity; //!< Velocity of the object
    cv::Rect roi; //!< Region of interest where object is detected in an input frame.
    pthread_mutex_t lock; //!< Mutex lock for synchronized access
};

/**
 * @brief A function to initialize obstacle data
 * 
 * This function initializes the obstacle data.
 */
void initObstacleData (void);

/**
 * @brief A function to get the distance to an obstacle
 * 
 * This function gets the distance to an obstacle.
 * 
 * @return Distance in cm
 */
double getDistance (void);

/**
 * @brief A function to set the distance to an obstacle
 * 
 * This function sets the distance to an obstacle.
 * 
 * @param distance Distance to an obstacle
 */
void setDistance (double distance);

/**
 * @brief A thread to detect an obstacle with an ultrasonic sensor
 * 
 * This thread detects an obstacle with an ultrasonic sensor.
 * 
 * @param arg Input argument
 */
void *obstacleDetection (void *arg);

//! @} obstacle_detection

#endif // OBSTACLE_DETECTION_HPP
