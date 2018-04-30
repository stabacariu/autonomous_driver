/**
 * @file obstacle_data.cpp
 * @author Sergiu-Petru Tabacariu
 * @date 29.3.2018
 */

#include "obstacle_data.hpp"

void ObstacleData::setDistance (double distance)
{
    std::lock_guard<std::mutex> guard(lock);
    distance = distance;
}

double ObstacleData::getDistance (void)
{
    std::lock_guard<std::mutex> guard(lock);
    return distance;
}

void ObstacleData::setVelocity (double velocity)
{
    std::lock_guard<std::mutex> guard(lock);
    velocity = velocity;
}

double ObstacleData::getVelocity (void)
{
    std::lock_guard<std::mutex> guard(lock);
    return velocity;
}

void ObstacleData::setRoi (cv::Rect roi)
{
    std::lock_guard<std::mutex> guard(lock);
    roi = roi;
}

cv::Rect ObstacleData::getRoi (void)
{
    std::lock_guard<std::mutex> guard(lock);
    return roi;
}
