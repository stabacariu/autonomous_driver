/**
 * @file traffic_sign_data.cpp
 * @author Sergiu-Petru Tabacariu
 * @date 29.3.2018
 */

#include "traffic_sign_data.hpp"

void TrafficSignData::setDistance (double distance)
{
    std::lock_guard<std::mutex> guard(lock);
    distance = distance;
}

double TrafficSignData::getDistance (void)
{
    std::lock_guard<std::mutex> guard(lock);
    return distance;
}

void TrafficSignData::setVelocity (double velocity)
{
    std::lock_guard<std::mutex> guard(lock);
    velocity = velocity;
}

double TrafficSignData::getVelocity (void)
{
    std::lock_guard<std::mutex> guard(lock);
    return velocity;
}

void TrafficSignData::setRoi (cv::Rect roi)
{
    std::lock_guard<std::mutex> guard(lock);
    roi = roi;
}

cv::Rect TrafficSignData::getRoi (void)
{
    std::lock_guard<std::mutex> guard(lock);
    return roi;
}