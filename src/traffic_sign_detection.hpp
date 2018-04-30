/**
 * @file traffic_sign_detection.hpp
 * @author Sergiu-Petru Tabacariu
 * @date 30.6.2017
 */

#ifndef TRAFFIC_SIGN_DETECTION_HPP
#define TRAFFIC_SIGN_DETECTION_HPP

#include <iostream>
#include <mutex>
#include <thread>
#include <opencv2/opencv.hpp>
#include "image_data.hpp"

//! @addtogroup traffic_sign_detection
//! @{

/**
 * @brief A traffic sign detector class
 */
class TrafficSignDetector {
public:
    ~TrafficSignDetector() = default;
    
    /**
     * @brief Start traffic sign detection
     * 
     * This function starts the traffic sign detection thread. This thread
     * detects traffic signs with Haar cascade classification.
     * It uses a pretrained model with is stored in "input/*.xml".
     * 
     * @param inputImageData
     * @param outputImageData
     */
    void start(ImageData& inputImageData, ImageData& outputImageData);
    
    /**
     * @brief Stop traffic sign detection
     * 
     * This function stops the traffic sign detection thread.
     */
    void stop(void);
    
    /**
     * @brief Check if traffic sign detection is running
     * 
     * This function checks if the traffic sign detection is running…
     * 
     * @return True if traffic sign detection is running, else false.
     */
    bool isRunning(void);
    
private:
    bool running{false};
};

/**
 * @brief Get center point of detected traffic sign
 * 
 * This function gets the mid point of a detected traffic sign.
 * 
 * @param tl Top left corner point of traffic sign
 * @param br Bottom right corner point of traffic sign
 * @return Center point of traffic sign
 */
cv::Point getSignCenter (cv::Point tl, cv::Point br);

//! @} traffic_sign_detection

#endif // TRAFFIC_SIGN_DETECTION_HPP
