/**
 * @file lane.cpp
 * @author Sergiu-Petru Tabacariu
 * @date 25.8.2017
 */
 
#include "lane.hpp"

LaneData actualLane;
PositionData actualPosition;
PositionData targetPosition;

void initLaneData (void)
{
    pthread_mutex_init(&actualLane.lock, NULL);
    pthread_mutex_init(&actualPosition.lock, NULL);
    pthread_mutex_init(&targetPosition.lock, NULL);
    
    cv::Size imageSize = getImageSize();
    setRoiLeft(cv::Rect(cv::Point(0, 0), cv::Point(imageSize.width-1, imageSize.height-1)));
    setRoiRight(cv::Rect(cv::Point(0, 0), cv::Point(imageSize.width-1, imageSize.height-1)));
}


void setActualLane (std::vector<cv::Vec4i> lane)
{
    if (pthread_mutex_lock(&actualLane.lock)) {
        std::cerr << "ERROR: Couldn't lock actual lane mutex!" << std::endl;
    }
    
    actualLane.lane = lane;
    
    if (pthread_mutex_unlock(&actualLane.lock)) {
        std::cerr << "ERROR: Couldn't unlock actual lane mutex!" << std::endl;
    }
}

void getActualLane (std::vector<cv::Vec4i>& lane)
{
    if (pthread_mutex_lock(&actualLane.lock)) {
        std::cerr << "ERROR: Couldn't lock actual lane mutex!" << std::endl;
    }
    
    lane = actualLane.lane;
    
    if (pthread_mutex_unlock(&actualLane.lock)) {
        std::cerr << "ERROR: Couldn't unlock actual lane mutex!" << std::endl;
    }
}

void setActualPosition (cv::Point position)
{
    if (pthread_mutex_lock(&actualPosition.lock)) {
        std::cerr << "ERROR: Couldn't lock actual position mutex!" << std::endl;
    }
    
    actualPosition.position = position;
    
    if (pthread_mutex_unlock(&actualPosition.lock)) {
        std::cerr << "ERROR: Couldn't unlock actual position mutex!" << std::endl;
    }
}

cv::Point getActualPosition (void)
{
    cv::Point position;
    
    if (pthread_mutex_lock(&actualPosition.lock)) {
        std::cerr << "ERROR: Couldn't lock actual position mutex!" << std::endl;
    }
    
    position = actualPosition.position;
    
    if (pthread_mutex_unlock(&actualPosition.lock)) {
        std::cerr << "ERROR: Couldn't unlock actual position mutex!" << std::endl;
    }
    
    return position;
}

void setTargetPosition (cv::Point position)
{
    if (pthread_mutex_lock(&targetPosition.lock)) {
        std::cerr << "ERROR: Couldn't lock target position mutex!" << std::endl;
    }
    
    targetPosition.position = position;
    
    if (pthread_mutex_unlock(&targetPosition.lock)) {
        std::cerr << "ERROR: Couldn't unlock target position mutex!" << std::endl;
    }
}

cv::Point getTargetPosition (void)
{
    cv::Point position;
    
    if (pthread_mutex_lock(&targetPosition.lock)) {
        std::cerr << "ERROR: Couldn't lock target position mutex!" << std::endl;
    }
    
    position = targetPosition.position;
    
    if (pthread_mutex_unlock(&targetPosition.lock)) {
        std::cerr << "ERROR: Couldn't unlock target position mutex!" << std::endl;
    }
    
    return position;
}

void setRoiLeft (cv::Rect roi)
{
    if (pthread_mutex_lock(&actualLane.lock)) {
        std::cerr << "ERROR: Couldn't lock actual lane mutex!" << std::endl;
    }
    
    actualLane.roiLeft = roi;
    
    if (pthread_mutex_unlock(&actualLane.lock)) {
        std::cerr << "ERROR: Couldn't unlock actual lane mutex!" << std::endl;
    }
}

cv::Rect getRoiLeft (void)
{
    cv::Rect roi;
    
    if (pthread_mutex_lock(&actualLane.lock)) {
        std::cerr << "ERROR: Couldn't lock actual lane mutex!" << std::endl;
    }
    
    roi = actualLane.roiLeft;
    
    if (pthread_mutex_unlock(&actualLane.lock)) {
        std::cerr << "ERROR: Couldn't unlock actual lane mutex!" << std::endl;
    }
    
    return roi;
}

void setRoiRight (cv::Rect roi)
{
    if (pthread_mutex_lock(&actualLane.lock)) {
        std::cerr << "ERROR: Couldn't lock actual lane mutex!" << std::endl;
    }
    
    actualLane.roiRight = roi;
    
    if (pthread_mutex_unlock(&actualLane.lock)) {
        std::cerr << "ERROR: Couldn't unlock actual lane mutex!" << std::endl;
    }
}

cv::Rect getRoiRight (void)
{
    cv::Rect roi;
    
    if (pthread_mutex_lock(&actualLane.lock)) {
        std::cerr << "ERROR: Couldn't lock actual lane mutex!" << std::endl;
    }
    
    roi = actualLane.roiRight;
    
    if (pthread_mutex_unlock(&actualLane.lock)) {
        std::cerr << "ERROR: Couldn't unlock actual lane mutex!" << std::endl;
    }
    
    return roi;
}
