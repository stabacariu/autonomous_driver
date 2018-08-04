/**
 * @file trajectory_data.cpp
 * @author Sergiu-Petru Tabacariu
 * @date 30.3.2018
 */
#include "trajectory_data.hpp"

void TrajectoryData::push_back (cv::Point point)
{
    std::lock_guard<std::mutex> guard(lock);
    points.push_back(point);
}

cv::Point TrajectoryData::at (int i)
{
    std::lock_guard<std::mutex> guard(lock);
    return points.at(i);
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
