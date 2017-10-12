/**
 * @file lane.cpp
 * @author Sergiu-Petru Tabacariu
 * @date 25.8.2017
 */
 
#include "lane.hpp"

LaneData actualLane;
PositionData actualPosition;
PositionData targetPosition;

using namespace std;
using namespace cv;

void initLaneData (void)
{
    pthread_mutex_init(&actualLane.lock, NULL);
    pthread_mutex_init(&actualPosition.lock, NULL);
    pthread_mutex_init(&targetPosition.lock, NULL);
}


void setActualLane (vector<Vec4i> lane)
{
    if (pthread_mutex_lock(&actualLane.lock)) {
        cerr << "ERROR: Couldn't lock actual lane mutex!" << endl;
    }
    
    actualLane.lane = lane;
    
    if (pthread_mutex_unlock(&actualLane.lock)) {
        cerr << "ERROR: Couldn't unlock actual lane mutex!" << endl;
    }
}

void getActualLane (vector<Vec4i>& lane)
{
    if (pthread_mutex_lock(&actualLane.lock)) {
        cerr << "ERROR: Couldn't lock actual lane mutex!" << endl;
    }
    
    lane = actualLane.lane;
    
    if (pthread_mutex_unlock(&actualLane.lock)) {
        cerr << "ERROR: Couldn't unlock actual lane mutex!" << endl;
    }
}

void setActualPosition (Point position)
{
    if (pthread_mutex_lock(&actualPosition.lock)) {
        cerr << "ERROR: Couldn't lock actual position mutex!" << endl;
    }
    
    actualPosition.position = position;
    
    if (pthread_mutex_unlock(&actualPosition.lock)) {
        cerr << "ERROR: Couldn't unlock actual position mutex!" << endl;
    }
}

Point getActualPosition (void)
{
    Point position;
    
    if (pthread_mutex_lock(&actualPosition.lock)) {
        cerr << "ERROR: Couldn't lock actual position mutex!" << endl;
    }
    
    position = actualPosition.position;
    
    if (pthread_mutex_unlock(&actualPosition.lock)) {
        cerr << "ERROR: Couldn't unlock actual position mutex!" << endl;
    }
    
    return position;
}

void setTargetPosition (Point position)
{
    if (pthread_mutex_lock(&targetPosition.lock)) {
        cerr << "ERROR: Couldn't lock target position mutex!" << endl;
    }
    
    targetPosition.position = position;
    
    if (pthread_mutex_unlock(&targetPosition.lock)) {
        cerr << "ERROR: Couldn't unlock target position mutex!" << endl;
    }
}

Point getTargetPosition (void)
{
    Point position;
    
    if (pthread_mutex_lock(&targetPosition.lock)) {
        cerr << "ERROR: Couldn't lock target position mutex!" << endl;
    }
    
    position = targetPosition.position;
    
    if (pthread_mutex_unlock(&targetPosition.lock)) {
        cerr << "ERROR: Couldn't unlock target position mutex!" << endl;
    }
    
    return position;
}

void setRoiLeft (Rect roi)
{
    if (pthread_mutex_lock(&actualLane.lock)) {
        cerr << "ERROR: Couldn't lock actual lane mutex!" << endl;
    }
    
    actualLane.roiLeft = roi;
    
    if (pthread_mutex_unlock(&actualLane.lock)) {
        cerr << "ERROR: Couldn't unlock actual lane mutex!" << endl;
    }
}

Rect getRoiLeft (void)
{
    Rect roi;
    
    if (pthread_mutex_lock(&actualLane.lock)) {
        cerr << "ERROR: Couldn't lock actual lane mutex!" << endl;
    }
    
    roi = actualLane.roiLeft;
    
    if (pthread_mutex_unlock(&actualLane.lock)) {
        cerr << "ERROR: Couldn't unlock actual lane mutex!" << endl;
    }
    
    return roi;
}

void setRoiRight (Rect roi)
{
    if (pthread_mutex_lock(&actualLane.lock)) {
        cerr << "ERROR: Couldn't lock actual lane mutex!" << endl;
    }
    
    actualLane.roiRight = roi;
    
    if (pthread_mutex_unlock(&actualLane.lock)) {
        cerr << "ERROR: Couldn't unlock actual lane mutex!" << endl;
    }
}

Rect getRoiRight (void)
{
    Rect roi;
    
    if (pthread_mutex_lock(&actualLane.lock)) {
        cerr << "ERROR: Couldn't lock actual lane mutex!" << endl;
    }
    
    roi = actualLane.roiRight;
    
    if (pthread_mutex_unlock(&actualLane.lock)) {
        cerr << "ERROR: Couldn't unlock actual lane mutex!" << endl;
    }
    
    return roi;
}
