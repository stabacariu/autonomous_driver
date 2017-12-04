/**
 * @file planning.hpp
 * @author Sergiu-Petru Tabacariu
 * @date 25.8.2017
 */

#ifndef PLANNING_HPP
#define PLANNING_HPP

#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/tracking.hpp>
#include <pthread.h>
#include "autonomous_driver.hpp"
#include "lane_detection.hpp"
#include "vehicle_control.hpp"

void *pathPlanning (void *arg);
void *pathPlanning2 (void *arg);

#endif // PLANNING_HPP
