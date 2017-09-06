/**
 * @file vehicle_control.hpp
 * @author Sergiu-Petru Tabacariu
 * @date 3.7.2017
 */

#ifndef VEHICLE_CONTROL_HPP
#define VEHICLE_CONTROL_HPP

#include <iostream>
#include <opencv2/opencv.hpp>
#include "autonomous_driver.hpp"
#include "vehicle.hpp"
#include "motor_driver.hpp"

void *vehicleControl (void* arg);

#endif // VEHICLE_CONTROL_HPP
