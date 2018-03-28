/**
 * @file autonomous_driver.hpp
 * @author Sergiu-Petru Tabacariu
 * @date 6.12.2017
 * 
 * @brief This header describes the enums, structs 
 *        and function prototypes for the system state,
 */

#ifndef AUTONOMOUS_DRIVER_HPP
#define AUTONOMOUS_DRIVER_HPP

#include <iostream>
#include <pthread.h>
#include <thread>
#include <mutex>
#include "image_show.hpp"
#include "lane_detection.hpp"
#include "traffic_sign_detection.hpp"
#include "obstacle_detection.hpp"
#include "user_interface.hpp"
#include "planning.hpp"
#include "vehicle_control.hpp"
#include "remote_control.hpp"
#include "configuration.hpp"

/**
 * @brief An enum for system modes
 * 
 * This enumerator describes the system state by defining system modes.
 */
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

/**
 * @brief A struct for the system state
 * 
 * This structure describes the system state by its mode.
 * It synchronises access via a mutex lock to be thread safe.
 */
struct SystemState {
    SystemMode mode; //!< System mode
    pthread_mutex_t lock; //!< Mutex lock for synchronized access
};

/**
 * @brief An enum for active module types
 * 
 * This enum describes all available modules.
 */
enum ModuleFlag {
    MODULE_NONE = 0x0,
    
    MODULE_CAP_CAM_IMAGE = 0x1,
    MODULE_CAP_VIDEO_IMAGE = 0x2,
    
    MODULE_SHOW_OUT_IMAGE = 0x10,
    MODULE_SHOW_IN_IMAGE = 0x20,
    
    MODULE_DETECT_LANES = 0x100,
    MODULE_DETECT_TRAFFIC_SIGNS = 0x200,
    MODULE_DETECT_OBSTACLE = 0x400,
    
    MODULE_PLAN_PATH = 0x1000,
    
    MODULE_CONTROL_VEHICLE = 0x10000,
    MODULE_CONTROL_STEERING = 0x20000,
    MODULE_CONTROL_SPEED = 0x40000,
    MODULE_CONTROL_REMOTE = 0x80000,
    
    MODULE_CONFIG_CALIB_INTR = 0x100000,
    MODULE_CONFIG_CALIB_EXTR = 0x200000,
    MODULE_CONFIG_IMAGE_POSITION = 0x400000,
    MODULE_SHOW_CHESSBOARD = 0x800000
};

/**
 * @brief A module state stucture
 * 
 * This structure holds the module state flags and a mutex lock.
 */
struct ModuleState {
    int state; //!< Module state vector with active module flags
    pthread_mutex_t lock; //!< Mutex lock for synchronized access
};

/**
 * @brief A system state class
 * 
 * This class describes the system state of the autonomous driver.
 */
class SystemStateClass {
public:
    SystemStateClass(); //!< Default constructor
    virtual ~SystemStateClass(); //!< Default destructor
    
    /**
     * @brief Set the system state
     * 
     * This function sets the system state. First it locks the state
     * information resource.
     * 
     * @param state New system state to be set
     */
    void setState(SystemMode state);
    
    /**
     * @brief Get the system state
     * 
     * This function gets the actual system state. First it locks the
     * state information resource.
     * 
     * @return The system state
     */
    SystemMode getState() const;
    
    /**
     * @brief Get all active modules
     * 
     * This function gets all active modules. They are activated by the
     * system state with also is the actual mode.
     * 
     * @return Active modules
     */
    ModuleFlag getActiveModules() const;
    
private:
    SystemMode state;
    ModuleFlag activeModules;
    std::mutex lock;
};

/**
 * @brief A function for system state initialization
 * 
 * This function initializes the system state by initializing the mutex
 * and setting the system state to standby.
 */
void initSystemState (void);

/**
 * @brief A function for setting the system state
 * 
 * This function sets the system state by locking the state first and
 * then changing it.
 * 
 * @param state A system state mode
 */
void setSystemState (SystemMode state);

/**
 * @brief A function for getting the system state
 * 
 * This function gets the actual system state by locking the state first
 * and then returning it.
 * 
 * @return system mode
 */
SystemMode getSystemState (void);

/**
 * @brief A function for module state initialization
 * 
 * This function initializes the module state by initializing the mutex
 * and setting the module state to none.
 */
void initModuleState (void);

/**
 * @brief A function for setting the module state
 * 
 * This function sets a module state vector to start or stop corresponding
 * modules. First it locks the access and then it changes the state.
 * 
 * @param modules Modules to activate or deactivate
 */
void setModuleState (int modules);

/**
 * @brief A function for getting the module state
 * 
 * This function gets the module state vector by locking it first and
 * returning the state.
 * 
 * @return module flags
 */
int getModuleState (void);

/**
 * @brief A function to execute the autonomous driving platform system states
 * 
 * This function executes the actual system state by reading the actual
 * state and starting of the corresponding modules and execution threads.
 */
void autonomousDriver (void);

#endif // AUTONOMOUS_DRIVER_HPP
