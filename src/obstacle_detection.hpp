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
#include "obstacle_data.hpp"

//! @addtogroup obstacle_detection
//! @{

/**
 * @brief A obstacle detector class
 */
class ObstacleDetector {
public:
    ~ObstacleDetector() = default;
    
    /**
     * @brief Start obstacle detection
     * 
     * This function starts the obstacle detection thread.
     */
    void start(ObstacleData& obstacleData);
    
    /**
     * @brief Stop obstacle detection
     * 
     * This function stops the obstacle detection thread.
     */
    void stop(void);
    
    /**
     * @brief Check if obstacle detection is running
     * 
     * This function checks if the obstacle detection is running…
     * 
     * @return True if obstacle detection is running, else false.
     */
    bool isRunning(void);
    
private:
    bool running{false};
};

//! @} obstacle_detection

#endif // OBSTACLE_DETECTION_HPP
