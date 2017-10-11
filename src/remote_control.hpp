/**
 * @file remote_control.hpp
 * @author Sergiu-Petru Tabacariu
 * @date 11.10.2017
 */

#ifndef REMOTE_CONTROL_HPP
#define REMOTE_CONTROL_HPP

#include <iostream>
#include <opencv2/opencv.hpp>
#include <pthread.h>
#include "autonomous_driver.hpp"
#include "vehicle_control.hpp"

void *remoteControl (void *arg);

#endif // REMOTE_CONTROL_HPP
