/**
 * @file path_planning.hpp
 * @author Sergiu-Petru Tabacariu
 * @date 25.8.2017
 */

/**
 * @ingroup module
 * @defgroup planning Planning
 * @brief A behavior planning module
 */
 
/**
 * @ingroup planning
 * @defgroup path_planning Path planning
 * @brief A module to plan a path autonomously
 */


#ifndef PATH_PLANNING_HPP
#define PATH_PLANNING_HPP

#include <iostream>
#include <atomic>
#include <opencv2/opencv.hpp>
#include "module.hpp"
#include "camera_image_acquisitor.hpp"
#include "lane_data.hpp"
#include "lane_detection.hpp"
#include "obstacle_data.hpp"
#include "obstacle_detection.hpp"
#include "traffic_sign_data.hpp"
#include "vehicle_control.hpp"
#include "vehicle_data.hpp"
#include "trajectory_data.hpp"

//! @addtogroup path_planning Path planning
//! @{

class PathPlanner : public Module {
public:
    ~PathPlanner() = default;
    
    /**
     * @brief Start path planning
     * 
     * This function runs the path planning thread. This thread plans
     * a path according to a detected lane makring. It then sets a
     * certain acceleration and steering angle.
     * 
     * @param inputImage Input image data
     * @param outputImage Output image data
     * @param lane Actual lane data
     * @param trafficSigns Traffic sign data
     * @param obstacle Obstacle data
     * @param vehicle Vehicle data
     * @param trajectory Trajectory data
     */
    void run (ImageData& inputImage, ImageData& outputImage, LaneData& lane, TrafficSignData& trafficSigns, ObstacleData& obstacle, VehicleModel& vehicle, TrajectoryData& trajectory);
    
private:
    CameraConfig camConfig;
    ObstacleDetectionConfig obstacleDetConfig;
};

/**
 * @brief Calculate trajectory
 * 
 * This function calculates a trajectory to be driven by the autonomous car
 * 
 * @param actualLane Actual lane composed of left and right road marking line
 * @param trajectory Trajectory data
 * @param kfT Kalman filter for the Trajectory
 * @param imageSize Size of captured image
 */
void calcTrajectory (std::vector<cv::Vec4i> actualLane, TrajectoryData& trajectory, cv::KalmanFilter kfT, cv::Size imageSize);

/**
 * @brief Draw trajectory data point vector
 * 
 * This function draws the trajectory by drawing a line between
 * the first and the last point from the point vector.
 * 
 * @param image
 * @param trajectory
 */
void drawTrajectory (cv::Mat& image, TrajectoryData& trajectory);

/**
 * @brief Draw trajectory line
 * 
 * This function draws the trajectory by drawing the line describ
 * 
 * @param image
 * @param trajectory
 */
void drawTrajectoryLine (cv::Mat& image, TrajectoryData& trajectory);

//! @} path_planning

#endif // PATH_PLANNING_HPP
