/**
 * @file lane_data.cpp
 * @author Sergiu-Petru Tabacariu
 * @date 25.8.2017
 */
 
#include "lane_data.hpp"

//~ void LaneData::setLeftLine(RoadMarking line)
//~ {
    //~ std::lock_guard<std::mutex> guard(lock);
    //~ leftLine = line;
//~ }

void LaneData::setLeftLine(cv::Vec4i line)
{
    std::lock_guard<std::mutex> guard(lock);
    leftLineVec4i = line;
}

//~ RoadMarking LaneData::getLeftLine(void)
//~ {
    //~ std::lock_guard<std::mutex> guard(lock);
    //~ return leftLine;
//~ }

cv::Vec4i LaneData::getLeftLine(void)
{
    std::lock_guard<std::mutex> guard(lock);
    return leftLineVec4i;
}

//~ void LaneData::setRightLine(RoadMarking line)
//~ {
    //~ std::lock_guard<std::mutex> guard(lock);
    //~ rightLine = line;
//~ }

void LaneData::setRightLine(cv::Vec4i line)
{
    std::lock_guard<std::mutex> guard(lock);
    rightLineVec4i = line;
}

//~ RoadMarking LaneData::getRightLine(void)
//~ {
    //~ std::lock_guard<std::mutex> guard(lock);
    //~ return rightLine;
//~ }

cv::Vec4i LaneData::getRightLine(void)
{
    std::lock_guard<std::mutex> guard(lock);
    return rightLineVec4i;
}

void LaneData::pushLeftLinePoint(cv::Point point)
{
    std::lock_guard<std::mutex> guard(lock);
    leftLine.points.push_back(point);
}

void LaneData::pushRightLinePoint(cv::Point point)
{
    std::lock_guard<std::mutex> guard(lock);
    rightLine.points.push_back(point);
}

void LaneData::setRoiLeft (cv::Rect roi)
{
    std::lock_guard<std::mutex> guard(lock);
    roiLeft = roi;
}

cv::Rect LaneData::getRoiLeft (void)
{
    std::lock_guard<std::mutex> guard(lock);
    return roiLeft;
}

void LaneData::setRoiRight (cv::Rect roi)
{
    std::lock_guard<std::mutex> guard(lock);
    roiRight = roi;
}

cv::Rect LaneData::getRoiRight (void)
{
    std::lock_guard<std::mutex> guard(lock);
    return roiRight;
}

cv::Vec4i cvtRoadMarkingToVec4i (RoadMarking line)
{
    cv::Vec4i convertedLine;
    convertedLine[0] = line.points.at(0).x;
    convertedLine[1] = line.points.at(0).y;
    convertedLine[2] = line.points.at(1).x;
    convertedLine[3] = line.points.at(1).y;
    return convertedLine;
}

RoadMarking cvtVec4iToRoadMarking (cv::Vec4i line)
{
    RoadMarking convertedLine;
    convertedLine.points.push_back(cv::Point(line[0], line[1]));
    convertedLine.points.push_back(cv::Point(line[2], line[3]));
    return convertedLine;
}
