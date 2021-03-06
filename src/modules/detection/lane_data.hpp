/**
 * @file lane_data.hpp
 * @author Sergiu-Petru Tabacariu
 * @date 25.8.2017
 */
 
#ifndef LANE_DATA_HPP
#define LANE_DATA_HPP

#include <iostream>
#include <opencv2/opencv.hpp>
#include <mutex>

//! @addtogroup lane_detection
//! @{

/**
 * @brief A enum for road marking type
 */
enum MarkingType {
    MARKING_NONE,           //!< No road marking
    MARKING_SOLID,          //!< Single solid marking
    MARKING_DASHED,         //!< Single dashed marking 
    MARKING_SOLIDDASHED,    //!< Double marking, left solid, right dashed
    MARKING_DASHEDSOLID,    //!< Double marking, left dashed, right solid
    MARKING_DOUBLEDASHED    //!< Double dashed marking
};

/**
 * @brief A struct for road marking
 */
struct RoadMarking {
    std::vector<cv::Point> points; //!< Points describing road marking course in an image
    MarkingType type; //!< Type of road marking
    
    /**
     * @brief Size of road marking point vector
     * 
     * This function returns the size of a road marking point vector
     * 
     * @return Size of point vector
     */
    int size (void) { return points.size(); };
};

/**
 * @brief A lane data class
 * 
 * This class defines the lane data and synchronises the access to it.
 */
class LaneData {
public:
    ~LaneData() = default;
    
    /**
     * @brief Set left road marking line
     * 
     * This function sets a left road marking line to the lane.
     * 
     * @param line Road marking line
     */
    //~ void setLeftLine(RoadMarking line);
    
    void setLeftLine(cv::Vec4i line);
    
    /**
     * @brief Get left road marking line
     * 
     * This function gets the left road marking line.
     * 
     * @return Road marking line
     */
    //~ RoadMarking getLeftLine(void);
    
    cv::Vec4i getLeftLine(void);
    
    /**
     * @brief Set right road marking line
     * 
     * This function sets a right road marking line to the lane.
     * 
     * @param line Road marking line
     */
    //~ void setRightLine(RoadMarking line);
    
    void setRightLine(cv::Vec4i line);
    
    /**
     * @brief Get right road marking line
     * 
     * This function gets the right road marking line.
     * 
     * @return Road marking line
     */
    //~ RoadMarking getRightLine(void);
    
    cv::Vec4i getRightLine(void);
    
    /**
     * @brief Push a left road marking line point
     * 
     * This function pushes a left road marking line point to the lane
     * 
     * @param point The point 2D coordinates
     */
    void pushLeftLinePoint(cv::Point point);
    
    /**
     * @brief Push a right road marking line point
     * 
     * This function pushes a right road marking line point to the lane
     * 
     * @param point The point 2D coordinates
     */
    void pushRightLinePoint(cv::Point point);
    
    /**
     * @brief Set lane
     * 
     * This function sets a lane with left and right road marking lines
     * 
     * @param lane The lane with left and right road marking lines
     */
     void setLane(LaneData lane);
     
     /**
      * @brief Get lane
      * 
      * This function gets a lane with left and right road marking lines
      * 
      * @returns The lane data
      */
      LaneData getLane(void);
      
      /**
       * @brief Set region of interest of left lane marking
       * 
       * This function sets the region of interest of the left lane marking.
       * 
       * @param roi Region of interest of left lane marking 
       */
      void setRoiLeft (cv::Rect roi);
      
      /**
       * @brief Get region of interest of left lane marking
       * 
       * This function gets the region of interest of the left lane marking.
       * 
       * @return Region of interest of left lane marking
       */
      cv::Rect getRoiLeft (void);
      
      /**
       * @brief Set region of interest of right lane marking
       * 
       * This function sets the region of interest of the right lane marking.
       * 
       * @param roi Region of interest of right lane marking
       */
      void setRoiRight (cv::Rect roi);
      
      /**
       * @brief Get region of interest of right lane marking
       * 
       * This function gets the region of interest of the right lane marking.
       * 
       * @return Region of interest of right lane marking
       */
      cv::Rect getRoiRight (void);
    
private:
    RoadMarking leftLine; //!< Left lane marking
    RoadMarking rightLine; //!< Right lane marking
    cv::Vec4i leftLineVec4i; //!< @note Only for compatibility!
    cv::Vec4i rightLineVec4i;  //!< @note Only for compatibility!
    cv::Rect roiLeft; //!< Region of interest of left lane marking
    cv::Rect roiRight; //!< Region of interest of right lane marking
    std::mutex lock; //!< Mutex lock for synchronised access
};

/**
 * @brief A struct for the detected road data
 * @note Only for future implementation. Not implemented in this version!
 */
struct RoadData {
    std::vector<LaneData> lane;
};

/**
 * @brief Convert road marking data to cv::Vec4i
 * 
 * This function converts road marking data to 4 elements integer vector.
 * @note Road marking data must contain only zwo points with zwo
 *       two coordinates. If road marking data vector is longer only first
 *       and last point will be converted.
 * 
 * @param line Road marking line
 * @return 4 element integer vector Vec4i
 */
cv::Vec4i cvtRoadMarkingToVec4i (RoadMarking line);

/**
 * @brief Convert cv::Vec4i to road marking data
 * 
 * This function converts 4 elements integer vector to road marking data.
 * 
 * @param line 4 element integer vector Vec4i
 * @return Road marking line
 */
RoadMarking cvtVec4iToRoadMarking (cv::Vec4i line);

//! @} lane_detection

#endif // LANE_DATA_HPP
