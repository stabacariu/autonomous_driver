/**
 * @file lane.cpp
 * @author Sergiu-Petru Tabacariu
 * @date 25.8.2017
 */
 
#include "lane.hpp"

LaneData actualLane;

using namespace std;
using namespace cv;

void initLaneData (void)
{
    pthread_mutex_init(&actualLane.lock, NULL);
}


void setActualLane (vector<Vec4i> lane)
{
    if (pthread_mutex_lock(&actualLane.lock)) {
        cerr << "ERROR: Couldn't lock lane mutex!" << endl;
    }
    
    actualLane.lane = lane;
    
    if (pthread_mutex_unlock(&actualLane.lock)) {
        cerr << "ERROR: Couldn't unlock lane mutex!" << endl;
    }
}

void getActualLane (vector<Vec4i>& lane)
{
    if (pthread_mutex_lock(&actualLane.lock)) {
        cerr << "ERROR: Couldn't lock lane mutex!" << endl;
    }
    
    lane = actualLane.lane;
    
    if (pthread_mutex_unlock(&actualLane.lock)) {
        cerr << "ERROR: Couldn't unlock lane mutex!" << endl;
    }
}
