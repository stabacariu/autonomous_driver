/**
 * @file traffic_sign_data.cpp
 * @author Sergiu-Petru Tabacariu
 * @date 29.3.2018
 */

#include "traffic_sign_data.hpp"

void TrafficSignData::setDistance (double d)
{
    std::lock_guard<std::mutex> guard(lock);
    distance = d;
}

double TrafficSignData::getDistance (void)
{
    std::lock_guard<std::mutex> guard(lock);
    return distance;
}

void TrafficSignData::setVelocity (double v)
{
    std::lock_guard<std::mutex> guard(lock);
    velocity = v;
}

double TrafficSignData::getVelocity (void)
{
    std::lock_guard<std::mutex> guard(lock);
    return velocity;
}

void TrafficSignData::setRoi (cv::Rect r)
{
    std::lock_guard<std::mutex> guard(lock);
    roi = r;
}

cv::Rect TrafficSignData::getRoi (void)
{
    std::lock_guard<std::mutex> guard(lock);
    return roi;
}

cv::Point getSignCenter (cv::Point tl, cv::Point br)
{
    return cv::Point(tl.x + (br.x - tl.x)/2, tl.y + (br.y - tl.y)/2);
}

cv::Point getSignCenter (cv::Rect roi)
{
    return cv::Point(roi.tl().x + roi.width/2, roi.tl().y + roi.height/2);
}
