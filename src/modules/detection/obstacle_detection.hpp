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
#include <atomic>
#include <thread>
#include <wiringPi.h>
#include <opencv2/opencv.hpp>
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
class ObstacleDetector {
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
    
    /**
     * @brief Quit obstacle detection
     * 
     * This function quits the obstacle detection thread.
     */
    void quit (void);
    
    /**
     * @brief Check if obstacle detection is running
     * 
     * This function checks if the obstacle detection is running…
     * 
     * @return True if obstacle detection is running, else false.
     */
    bool isRunning(void);
    
private:
    std::atomic_bool running {false};
    ObstacleDetectionConfig obstacleDetConfig;
};

//! @} obstacle_detection

#endif // OBSTACLE_DETECTION_HPP
