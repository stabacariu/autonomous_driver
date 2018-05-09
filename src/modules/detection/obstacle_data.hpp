/**
 * @file obstacle_data.hpp
 * @author Sergiu-Petru Tabacariu
 * @date 29.3.2018
 */

#ifndef OBSTACLE_DATA_HPP
#define OBSTACLE_DATA_HPP

#include <iostream>
#include <mutex>
#include <opencv2/opencv.hpp>

//! @addtogroup obstacle_detection
//! @{

/**
 * @brief An obstacle data class
 */
class ObstacleData {
public:
    ~ObstacleData() = default;
    /**
     * @brief Set distance to obstacle
     * 
     * This function sets the distance between the capturing sensor and
     * a detected obstacle.
     * 
     * @param distance in mm
     */
    void setDistance(double distance);
    
    /**
     * @brief Get distance to obstacle
     * 
     * This function gets the distance between the capturing sensor and 
     * a detected obstacle.
     * 
     * @return Distance in mm
     */
    double getDistance(void);
    
    /**
     * @brief Set velocity of obstacle
     * 
     * This function sets the velocity of a detected obstacle relative
     * to the capturing sensor.
     * 
     * @param velocity in m/s
     */
    void setVelocity(double velocity);
    
    /**
     * @brief Get velocity of obstacle
     * 
     * This function gets the velocity of a detected obstacle relative
     * to the capturing sensor.
     * 
     * @return Velocity in m/s
     */
    double getVelocity(void);
    
    /**
     * @brief Set ROI of obstacle
     * 
     * This function sets the region of interest in an image where a
     * detected obstacle is.
     * 
     * @param roi Rectangle in pixel
     */
    void setRoi(cv::Rect roi);
    
    /**
     * @brief Get ROI of obstacle
     * 
     * This function gets the region of interest in an image where a
     * detected obstacle is.
     * 
     * @return ROI rectangle in pixel
     */
    cv::Rect getRoi(void);
    
private:
    double distance {(-1)}; //!< Distance from sensor to the object
    double velocity {(-1)}; //!< Objekt velocity relative to the sensor
    cv::Rect roi; //!< Region of interest where objekt is in a given image
    std::mutex lock; //!< Mutex lock for synchronized access
};


//! @} obstacle_detection

#endif // OBSTACLE_DATA_HPP
