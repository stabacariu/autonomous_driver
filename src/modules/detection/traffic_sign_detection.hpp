/**
 * @file traffic_sign_detection.hpp
 * @author Sergiu-Petru Tabacariu
 * @date 30.6.2017
 */
 
/**
 * @ingroup module
 * @defgroup traffic_sign_detection Traffic Sign Detectiom
 * @brief A traffic sign detection module
 */

#ifndef TRAFFIC_SIGN_DETECTION_HPP
#define TRAFFIC_SIGN_DETECTION_HPP

#include <iostream>
#include <atomic>
#include <thread>
#include <opencv2/opencv.hpp>
#include "module.hpp"
#include "traffic_sign_data.hpp"
#include "image_data.hpp"
#include "camera_image_acquisitor.hpp"

//! @addtogroup traffic_sign_detection
//! @{

#define STOP_SIGN_SIZE cv::Size(30,30)
#define STOP_SIGN_SAFETY_DISTANCE 20.

class TrafficSignDetectionConfig {
public:
    ~TrafficSignDetectionConfig() = default;
    
    bool load (cv::FileStorage fs);
    void save (cv::FileStorage fs);
    
public:
    bool active {false};
};


/**
 * @brief A traffic sign detector class
 */
class TrafficSignDetector : public Module {
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
     * @param trafficSignData
     */
    void run (ImageData& inputImageData, ImageData& outputImageData, TrafficSignData& trafficSignData);
    
private:
    CameraCalibrationConfig camCalibConfig;
    TrafficSignDetectionConfig trafficSignDetConfig;
};

//! @} traffic_sign_detection

#endif // TRAFFIC_SIGN_DETECTION_HPP
