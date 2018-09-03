/**
 * @file trajectory_data.cpp
 * @author Sergiu-Petru Tabacariu
 * @date 30.3.2018
 */
#include "trajectory_data.hpp"

void TrajectoryData::set (std::vector<cv::Point> pv)
{
    std::lock_guard<std::mutex> guard(lock);
    points = pv;
}

std::vector<cv::Point> TrajectoryData::get (void)
{
    std::lock_guard<std::mutex> guard(lock);
    return points;
}

int TrajectoryData::size (void)
{
    std::lock_guard<std::mutex> guard(lock);
    return points.size();
}

void TrajectoryData::clear (void)
{
    std::lock_guard<std::mutex> guard(lock);
    points.clear();
}

void TrajectoryData::setLine (cv::Vec4i l)
{
    std::lock_guard<std::mutex> guard(lock);
    line = l;
}
    
cv::Vec4i TrajectoryData::getLine (void)
{
    std::lock_guard<std::mutex> guard(lock);
    return line;
}
