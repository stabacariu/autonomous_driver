/**
 * @file autonomous_driver.hpp
 * @author Sergiu-Petru Tabacariu
 * @date 27.6.2017
 * 
 * @brief This header contains the class descrition
 */

#ifndef AUTONOMOUS_DRIVER_HPP
#define AUTONOMOUS_DRIVER_HPP

#include <iostream>
#include <pthread.h>
#include "image_processing.hpp"
#include "lane_detection.hpp"
#include "traffic_sign_detection.hpp"
#include "user_interface.hpp"
#include "planning.hpp"
#include "vehicle_control.hpp"

enum SystemMode {
    SYS_MODE_STANDBY,
    SYS_MODE_AUTO,
    SYS_MODE_RC,
    SYS_MODE_DEV,
    SYS_MODE_CONFIG,
    SYS_MODE_ABOUT,
    SYS_MODE_CLOSING,
    SYS_MODE_ERROR
};

struct SystemState {
    SystemMode mode;
    pthread_mutex_t lock;
};

enum ModuleType {
    MODULE_NONE = 0x0,
    
    MODULE_CAP_CAM_IMAGE = 0x1,
    MODULE_CAP_VIDEO_IMAGE = 0x2,
    
    MODULE_SHOW_OUT_IMAGE = 0x10,
    MODULE_SHOW_IN_IMAGE = 0x20,
    
    MODULE_DETECT_LANES = 0x100,
    MODULE_DETECT_TRAFFIC_SIGNS = 0x200,
    MODULE_DETECT_OBSTACLE = 0x400,
    
    MODULE_PLAN_PATH = 0x1000,
    MODULE_CONTROL_STEERING = 0x10000,
    MODULE_CONTROL_SPEED = 0x20000,
    MODULE_CONTROL_VEHICLE = 0x40000
};

struct ModuleState {
    int state; //< Active modules state vector
    pthread_mutex_t lock; //< Mutex lock for concurrent access
};

void systemStateInit (void);
void setSystemState (SystemMode state);
SystemMode getSystemState (void);

void initModuleState (void);
void setModuleState (int modules);
int getModuleState (void);

void autonomousDriver (void);

#endif // AUTONOMOUS_DRIVER_HPP
