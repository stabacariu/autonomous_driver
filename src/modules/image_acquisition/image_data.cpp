/**
 * @file image_data.cpp
 * @author Sergiu-Petru Tabacariu
 * @date 30.6.2017
 */

#include "image_data.hpp"

void ImageData::write (cv::Mat image)
{
    std::lock_guard<std::mutex> guard(lock);
    data = image;
    //~ timeStamp = std::chrono::high_resolution_clock::now();
}

cv::Mat ImageData::read ()
{
    std::lock_guard<std::mutex> guard(lock);
    return data;
}

void ImageData::setTime(std::chrono::high_resolution_clock::time_point time)
{
    std::lock_guard<std::mutex> guard(lock);
    timeStamp = time;
}

std::chrono::high_resolution_clock::time_point ImageData::getTime()
{
    std::lock_guard<std::mutex> guard(lock);
    return timeStamp;
}
