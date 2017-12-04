/**
 * @file obstacle_detection.hpp
 * @author Sergiu-Petru Tabacariu
 * @date 4.12.2017
 */

#ifndef OBSTACLE_DETECTION_HPP
#define OBSTACLE_DETECTION_HPP

#include <iostream>
#include <pthread.h>
#include <wiringPi.h>
#include "../lib/libSonar.h"

struct ObstacleData {
    double distance;
    pthread_mutex_t lock;
};

void initObstacleData (void);
double getDistance (void);
void setDistance (double distance);
void *obstacleDetection (void *arg);

#endif // OBSTACLE_DETECTION_HPP
