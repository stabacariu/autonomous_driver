/**
 * @file lane.hpp
 * @author Sergiu-Petru Tabacariu
 * @date 25.8.2017
 */
 
#ifndef LANE_HPP
#define LANE_HPP

#include <iostream>
#include <opencv2/opencv.hpp>

enum LaneMarking {
    LANE_MARKING_NONE,
    LANE_MARKING_DASHED,
    LANE_MARKING_DASHED_SOLID,
    LANE_MARKING_SOLID
};

enum LaneMarkingType {
    LANE_MARKING_TYPE_NONE,
    LANE_MARKING_TYPE_SINGLE,
    LANE_MARKING_TYPE_DOUBLE
};

enum LaneMarkingPosition {
    LANE_MARKING_POSITION_NONE,
    LANE_MARKING_POSITION_GUIDE,
    LANE_MARKING_POSITION_EDGE
};

struct LaneData {
    std::vector<cv::Vec4i> lane;
    cv::Rect roiLeft;
    cv::Rect roiRight;
    pthread_mutex_t lock;
};

struct PositionData {
    cv::Point position;
    pthread_mutex_t lock;
};

void initLaneData (void);
void setActualLane (std::vector<cv::Vec4i> lane);
void getActualLane (std::vector<cv::Vec4i>& lane);
void setActualPosition (cv::Point position);
cv::Point getActualPosition (void);
void setTargetPosition (cv::Point position);
cv::Point getTargetPosition (void);

void setRoiLeft (cv::Rect roi);
cv::Rect getRoiLeft (void);
void setRoiRight (cv::Rect roi);
cv::Rect getRoiRight (void);

#endif // LANE_HPP
