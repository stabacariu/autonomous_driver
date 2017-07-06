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

enum SystemMode {
    SYS_MODE_STANDBY,
    SYS_MODE_AUTO,
    SYS_MODE_RC,
    SYS_MODE_DEV,
    SYS_MODE_CONFIG,
    SYS_MODE_CLOSING,
    SYS_MODE_ERROR
};

struct SystemState {
    SystemMode mode;
    pthread_mutex_t lock;
};

void systemStateInit (void);

void setSystemState (SystemMode status);
SystemMode getSystemState (void);

#endif // AUTONOMOUS_DRIVER_HPP
