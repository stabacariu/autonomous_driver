/**
 * @file lane.hpp
 * @author Sergiu-Petru Tabacariu
 * @date 25.8.2017
 */
 
#ifndef LANE_HPP
#define LANE_HPP

#include <iostream>
#include <opencv2/opencv.hpp>
#include "configuration.hpp"

//! @addtogroup lane_detection
//! @{

/**
 * @brief A enum for lane marking types
 */
enum LaneMarking {
    LANE_MARKING_NONE,
    LANE_MARKING_DASHED,
    LANE_MARKING_DASHED_SOLID,
    LANE_MARKING_SOLID
};

/**
 * @brief A enum for lane marking types
 */
enum LaneMarkingType {
    LANE_MARKING_TYPE_NONE,
    LANE_MARKING_TYPE_SINGLE,
    LANE_MARKING_TYPE_DOUBLE
};

/**
 * @brief A enum for lane marking position
 */
enum LaneMarkingPosition {
    LANE_MARKING_POSITION_NONE,
    LANE_MARKING_POSITION_GUIDE,
    LANE_MARKING_POSITION_EDGE
};

/**
 * @brief A struct for lane data
 */
struct LaneData {
    std::vector<cv::Vec4i> lane; //!< Lane data storred as start and end point
    cv::Rect roiLeft; //!< Region of interest around left line of lane
    cv::Rect roiRight; //!< Region of interest around right line of lane
    pthread_mutex_t lock; //!< Mutex lock for synchronized access
};

/**
 * @brief A struct for position data
 */
struct PositionData {
    cv::Point position; //!< Position data
    pthread_mutex_t lock; //!< Mutex lock for synchronized access
};

/**
 * @brief A function to initialize the lane data
 * 
 * This function initializes lane data.
 */
void initLaneData (void);

/**
 * @brief A function to set the actual lane
 * 
 * This function sets the actual found lane.
 * 
 * @param lane Actual found lane
 */
void setActualLane (std::vector<cv::Vec4i> lane);

/**
 * @brief A function to get the actual lane
 * 
 * This function gets the actual lane.
 * 
 * @param lane Actual lane
 */
void getActualLane (std::vector<cv::Vec4i>& lane);

/**
 * @brief A function to set actual position
 * 
 * This function gets the actual position in image frame.
 * 
 * @param position Actual position
 */
void setActualPosition (cv::Point position);

/**
 * @brief A function to get actual position
 * 
 * This function gets the actual position in image frame.
 * 
 * @return Point of actual position
 */
cv::Point getActualPosition (void);

/**
 * @brief A function to set target position
 * 
 * This function sets the target position.
 * 
 * @param position Target position
 */
void setTargetPosition (cv::Point position);

/**
 * @brief A function to get target postion
 * 
 * This function gets the target position.
 * 
 * @return Point of target position
 */
cv::Point getTargetPosition (void);

/**
 * @brief A function to set left ROI
 * 
 * This function sets a left region of interest around a line.
 * 
 * @param roi Region of interest as rectangle
 */
void setRoiLeft (cv::Rect roi);

/**
 * @brief A function to get left ROI
 * 
 * This function gets a left region of interest around a line.
 * 
 * @return Region of interest as rectangle
 */
cv::Rect getRoiLeft (void);

/**
 * @brief A function to set right ROI
 * 
 * This function sets a right region of interest around a line.
 * 
 * @param roi Region of interest as rectangle
 */
void setRoiRight (cv::Rect roi);

/**
 * @brief A function to set right ROI
 * 
 * This function sets a right region of interest around a line.
 * 
 * @return Region of interest as rectangle
 */
cv::Rect getRoiRight (void);

//! @} lane_detection

#endif // LANE_HPP
