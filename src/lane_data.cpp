/**
 * @file lane_data.cpp
 * @author Sergiu-Petru Tabacariu
 * @date 25.8.2017
 */
 
#include "lane_data.hpp"

void LaneData::setLeftLine(RoadMarking line)
{
    std::lock_guard<std::mutex> guard(lock);
    leftLine = line;
}

RoadMarking LaneData::getLeftLine(void)
{
    std::lock_guard<std::mutex> guard(lock);
    return leftLine;
}

void LaneData::setRightLine(RoadMarking line)
{
    std::lock_guard<std::mutex> guard(lock);
    rightLine = line;
}

RoadMarking LaneData::getRightLine(void)
{
    std::lock_guard<std::mutex> guard(lock);
    return rightLine;
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
    convertedLine[0] = line.points.front().x;
    convertedLine[1] = line.points.front().y;
    convertedLine[2] = line.points.back().x;
    convertedLine[3] = line.points.back().y;
    return convertedLine;
}

RoadMarking cvtVec4iToRoadMarking (cv::Vec4i line)
{
    RoadMarking convertedLine;
    convertedLine.points.push_back(cv::Point(line[0], line[1]));
    convertedLine.points.push_back(cv::Point(line[2], line[3]));
    return convertedLine;
}
