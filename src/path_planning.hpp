/**
 * @file path_planning.hpp
 * @author Sergiu-Petru Tabacariu
 * @date 25.8.2017
 */

/**
 * @defgroup path_planning Path planning
 * @{
 * @}
 */

#ifndef PATH_PLANNING_HPP
#define PATH_PLANNING_HPP

#include <iostream>
#include <atomic>
#include <opencv2/opencv.hpp>
#include "lane_data.hpp"
#include "lane_detection.hpp"
#include "obstacle_data.hpp"
#include "vehicle_control.hpp"
#include "vehicle_data.hpp"

//! @addtogroup path_planning Path planning
//! @{

class PathPlanner {
public:
    ~PathPlanner() = default;
    
    /**
     * @brief Start path planning
     * 
     * This function starts the path planning thread. This thread plans
     * a path according to a detected lane makring. It then sets a
     * certain acceleration and steering angle.
     * 
     * @param inputImage
     * @param laneData
     * @param obstacleData
     * @param vehicle
     */
    void start(ImageData& inputImage, LaneData& laneData, ObstacleData& obstacleData, VehicleData& vehicle);
    
    /**
     * @brief Stop path planning
     * 
     * This function stops the path planning thread.
     */
    void stop(void);
    
    /**
     * @brief Check if path planning is running
     * 
     * This function checks if the path planning is running…
     * 
     * @return True if path planning is running, else false.
     */
    bool isRunning(void);
    
private:
    std::atomic_bool running{false}; //!< Path planning running flag
};

/**
 * @brief A thread to plan and drive a long a path
 * 
 * @note This thread is for experimental use only!
 * 
 * This thread plans a path according to a detected lane makring. It then
 * sets a certain acceleration and steering angle.
 * 
 * @param arg Input argument
 */
//~ void *pathPlanning2 (void *arg);

/**
 * @brief Calculate trajectory
 * 
 * This function calculates a trajectory to be driven by the autonomous car
 * 
 * @param actualLane Actual lane composed of left and right road marking line
 * @param kfT Kalman filter for the Trajectory
 * @param imageSize Size of captured image
 */
void calcTrajectory (VehicleData& vehicle, std::vector<cv::Vec4i> actualLane, cv::KalmanFilter kfT, cv::Size imageSize);

//! @} path_planning

#endif // PATH_PLANNING_HPP
