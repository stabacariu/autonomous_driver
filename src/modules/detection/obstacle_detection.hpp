/**
 * @file obstacle_detection.hpp
 * @author Sergiu-Petru Tabacariu
 * @date 4.12.2017
 */

/**
 * @ingroup module
 * @defgroup obstacle_detection Obstacle Detectiom
 * @brief A obstacle detection module
 */

#ifndef OBSTACLE_DETECTION_HPP
#define OBSTACLE_DETECTION_HPP

#include <iostream>
#include <atomic>
#include <thread>
#include <wiringPi.h>
#include <opencv2/opencv.hpp>
#include "module.hpp"
#include "libSonar.h"
#include "obstacle_data.hpp"

//! @addtogroup obstacle_detection
//! @{

class ObstacleDetectionConfig {
public:
    ~ObstacleDetectionConfig() = default;
    
    bool load (cv::FileStorage fs);
    void save (cv::FileStorage fs);
    
public:
    bool active {false};
};

/**
 * @brief A obstacle detector class
 */
class ObstacleDetector : public Module {
public:
    ~ObstacleDetector() = default;
    
    /**
     * @brief Run obstacle detection
     * 
     * This function runs the obstacle detection thread.
     * 
     * @param obstacleData Detected obstacle data
     */
    void run (ObstacleData& obstacleData);
    
private:
    ObstacleDetectionConfig obstacleDetConfig;
};

//! @} obstacle_detection

#endif // OBSTACLE_DETECTION_HPP
