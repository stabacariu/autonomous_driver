/**
 * @file obstacle_data.cpp
 * @author Sergiu-Petru Tabacariu
 * @date 29.3.2018
 */

#include "obstacle_data.hpp"

void ObstacleData::setDistance (double d)
{
    std::lock_guard<std::mutex> guard(lock);
    distance = d;
}

double ObstacleData::getDistance (void)
{
    std::lock_guard<std::mutex> guard(lock);
    return distance;
}

void ObstacleData::setVelocity (double v)
{
    std::lock_guard<std::mutex> guard(lock);
    velocity = v;
}

double ObstacleData::getVelocity (void)
{
    std::lock_guard<std::mutex> guard(lock);
    return velocity;
}

void ObstacleData::setRoi (cv::Rect r)
{
    std::lock_guard<std::mutex> guard(lock);
    roi = r;
}

cv::Rect ObstacleData::getRoi (void)
{
    std::lock_guard<std::mutex> guard(lock);
    return roi;
}
