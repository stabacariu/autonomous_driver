/**
 * @file autonomous_driver.cpp
 * @author Sergiu-Petru Tabacariu
 * @date 6.12.2017
 *
 * @brief This programm holds all functions to demonstrate an autonmous
 * driving car.
 */

#include "autonomous_driver.hpp"

SystemState systemState;
ModuleState moduleState;

void initSystemState (void)
{
    pthread_mutex_init(&systemState.lock, NULL);
    setSystemState(SYS_MODE_STANDBY);

    initModuleState();
}

void setSystemState (SystemMode state)
{
    if (pthread_mutex_lock(&systemState.lock)) {
        std::cerr << "ERROR: Couldn't lock status mutex!" << std::endl;
    }

    systemState.mode = state;

    if (pthread_mutex_unlock(&systemState.lock)) {
        std::cerr << "ERROR: Couldn't unlock status mutex!" << std::endl;
    }
}

SystemMode getSystemState (void)
{
    SystemMode mode;

    if (pthread_mutex_lock(&systemState.lock)) {
        std::cerr << "ERROR: Couldn't lock status mutex!" << std::endl;
    }

    mode = systemState.mode;

    if (pthread_mutex_unlock(&systemState.lock)) {
        std::cerr << "ERROR: Couldn't unlock status mutex!" << std::endl;
    }

    return mode;
}

void initModuleState (void)
{
    pthread_mutex_init(&moduleState.lock, NULL);
    setModuleState(MODULE_NONE);
}

void setModuleState (int modules)
{
    if (pthread_mutex_lock(&moduleState.lock)) {
        std::cerr << "ERROR: Couldn't lock status mutex!" << std::endl;
    }

    moduleState.state = modules;

    if (pthread_mutex_unlock(&moduleState.lock)) {
        std::cerr << "ERROR: Couldn't unlock status mutex!" << std::endl;
    }
}

int getModuleState (void)
{
    int modules;

    if (pthread_mutex_lock(&moduleState.lock)) {
        std::cerr << "ERROR: Couldn't lock status mutex!" << std::endl;
    }

    modules = moduleState.state;

    if (pthread_mutex_unlock(&moduleState.lock)) {
        std::cerr << "ERROR: Couldn't unlock status mutex!" << std::endl;
    }

    return modules;
}

void systemStandbyMode (void)
{
    std::cout << "---------------------------------" << std::endl;
    std::cout << "SYSTEM: Standby Mode" << std::endl;

    // Start modules for standby mode
    setModuleState(MODULE_CAP_CAM_IMAGE + MODULE_SHOW_IN_IMAGE + MODULE_SHOW_OUT_IMAGE);

    pthread_t cameraCaptureThread;
    pthread_t showInputImageThread;
    pthread_t showOutputImageThread;

    // Create threads
    if (pthread_create(&cameraCaptureThread, NULL, cameraCapture, NULL)) {
        std::cerr << "ERROR: Couldn't create camera capture thread!" << std::endl;
    }
    if (pthread_create(&showInputImageThread, NULL, showInputImage, NULL)) {
        std::cerr << "ERROR: Couldn't create show input image thread!" << std::endl;
    }
    if (pthread_create(&showOutputImageThread, NULL, showOutputImage, NULL)) {
        std::cerr << "ERROR: Couldn't create show output image thread!" << std::endl;
    }

    // Join threads in the same sequence as they where created
    if (pthread_join(cameraCaptureThread, NULL)) {
        std::cerr << "ERROR: Couldn't join thread!" << std::endl;
    }
    if (pthread_join(showInputImageThread, NULL)) {
        std::cerr << "ERROR: Couldn't join thread!" << std::endl;
    }
    if (pthread_join(showOutputImageThread, NULL)) {
        std::cerr << "ERROR: Couldn't join thread!" << std::endl;
    }
}

void systemAutoMode (void)
{
    std::cout << "---------------------------------" << std::endl;
    std::cout << "SYSTEM: Autonomous Driving Mode" << std::endl;

    setModuleState(MODULE_CAP_CAM_IMAGE + MODULE_SHOW_OUT_IMAGE + MODULE_DETECT_LANES + MODULE_DETECT_OBSTACLE + MODULE_DETECT_TRAFFIC_SIGNS + MODULE_PLAN_PATH + MODULE_CONTROL_VEHICLE);

    pthread_t cameraCaptureThread;
    pthread_t detectLaneThread;
    pthread_t detectTrafficSignThread;
    pthread_t detectObstacleThread;
    pthread_t showOutputImageThread;
    pthread_t pathPlanningThread;
    pthread_t vehicleControlThread;

    // Create threads
    if (pthread_create(&cameraCaptureThread, NULL, cameraCapture, NULL)) {
        std::cerr << "ERROR: Couldn't create camera capture thread!" << std::endl;
    }
    if (pthread_create(&detectLaneThread, NULL, laneDetection, NULL)) {
        std::cerr << "ERROR: Couldn't create lane detection thread!" << std::endl;
    }
    if (pthread_create(&detectTrafficSignThread, NULL, trafficSignDetection, NULL)) {
        std::cerr << "ERROR: Couldn't create traffic sign detection thread!" << std::endl;
    }
    if (pthread_create(&detectObstacleThread, NULL, obstacleDetection, NULL)) {
        std::cerr << "ERROR: Couldn't create obstacle detection thread!" << std::endl;
    }
    if (pthread_create(&showOutputImageThread, NULL, showOutputImage, NULL)) {
        std::cerr << "ERROR: Couldn't create show output image thread!" << std::endl;
    }
    if (pthread_create(&pathPlanningThread, NULL, pathPlanning, NULL)) {
        std::cerr << "ERROR: Couldn't create path planning thread!" << std::endl;
    }
    if (pthread_create(&vehicleControlThread, NULL, vehicleControl, NULL)) {
        std::cerr << "ERROR: Couldn't create vehicle control thread!" << std::endl;
    }

    // Join threads
    if (pthread_join(cameraCaptureThread, NULL)) {
        std::cerr << "ERROR: Couldn't join thread!" << std::endl;
    }
    if (pthread_join(detectLaneThread, NULL)) {
        std::cerr << "ERROR: Couldn't join thread!" << std::endl;
    }
    if (pthread_join(detectTrafficSignThread, NULL)) {
        std::cerr << "ERROR: Couldn't join thread!" << std::endl;
    }
    if (pthread_join(detectObstacleThread, NULL)) {
        std::cerr << "ERROR: Couldn't join thread!" << std::endl;
    }
    if (pthread_join(showOutputImageThread, NULL)) {
        std::cerr << "ERROR: Couldn't join thread!" << std::endl;
    }
    if (pthread_join(pathPlanningThread, NULL)) {
        std::cerr << "ERROR: Couldn't join thread!" << std::endl;
    }
    if (pthread_join(vehicleControlThread, NULL)) {
        std::cerr << "ERROR: Couldn't join thread" << std::endl;
    }
}

void systemRCMode (void)
{
    std::cout << "---------------------------------" << std::endl;
    std::cout << "SYSTEM: Remote Control Mode" << std::endl;
    
    setModuleState(MODULE_CAP_CAM_IMAGE + MODULE_SHOW_IN_IMAGE + MODULE_SHOW_OUT_IMAGE + MODULE_CONTROL_VEHICLE + MODULE_CONTROL_REMOTE);
    
    pthread_t cameraCaptureThread;
    pthread_t showInputImageThread;
    pthread_t showOutputImageThread;
    pthread_t remoteControlThread;
    pthread_t vehicleControlThread;
    
    // Create threads
    if (pthread_create(&cameraCaptureThread, NULL, cameraCapture, NULL)) {
        std::cerr << "ERROR: Couldn't create camera capture thread!" << std::endl;
    }
    if (pthread_create(&showInputImageThread, NULL, showInputImage, NULL)) {
        std::cerr << "ERROR: Couldn't create show input image thread!" << std::endl;
    }
    if (pthread_create(&showOutputImageThread, NULL, showOutputImage, NULL)) {
        std::cerr << "ERROR: Couldn't create show output image thread!" << std::endl;
    }
    if (pthread_create(&remoteControlThread, NULL, remoteControl, NULL)) {
        std::cerr << "ERROR: Couldn't create remote control thread!" << std::endl;
    }
    if (pthread_create(&vehicleControlThread, NULL, vehicleControl, NULL)) {
        std::cerr << "ERROR: Couldn't create vehicle control thread!" << std::endl;
    }
    
    // Join thread
    if (pthread_join(cameraCaptureThread, NULL)) {
        std::cerr << "ERROR: Couldn't join thread!" << std::endl;
    }
    if (pthread_join(showInputImageThread, NULL)) {
        std::cerr << "ERROR: Couldn't join thread!" << std::endl;
    }
    if (pthread_join(showOutputImageThread, NULL)) {
        std::cerr << "ERROR: Couldn't join thread!" << std::endl;
    }
    if (pthread_join(remoteControlThread, NULL)) {
        std::cerr << "ERROR: Couldn't join thread!" << std::endl;
    }
    if (pthread_join(vehicleControlThread, NULL)) {
        std::cerr << "ERROR: Couldn't join thread!" << std::endl;
    }
}

void systemDevMode (void)
{
    std::cout << "---------------------------------" << std::endl;
    std::cout << "SYSTEM: Development Mode" << std::endl;
    
    setModuleState(MODULE_CAP_CAM_IMAGE + MODULE_SHOW_OUT_IMAGE + MODULE_DETECT_LANES + MODULE_DETECT_TRAFFIC_SIGNS + MODULE_DETECT_OBSTACLE + MODULE_PLAN_PATH + MODULE_CONTROL_VEHICLE);
    
    pthread_t cameraCaptureThread;
    pthread_t detectLaneThread;
    pthread_t detectTrafficSignThread;
    pthread_t detectObstacleThread;
    pthread_t showOutputImageThread;
    pthread_t pathPlanningThread;
    pthread_t vehicleControlThread;
    
    // Create threads
    if (pthread_create(&cameraCaptureThread, NULL, cameraCapture, NULL)) {
        std::cerr << "ERROR: Couldn't create camera capture thread!" << std::endl;
    }
    if (pthread_create(&detectLaneThread, NULL, laneDetection, NULL)) {
        std::cerr << "ERROR: Couldn't create lane detection thread!" << std::endl;
    }
    if (pthread_create(&detectTrafficSignThread, NULL, trafficSignDetection, NULL)) {
        std::cerr << "ERROR: Couldn't create traffic sign detection thread!" << std::endl;
    }
    if (pthread_create(&detectObstacleThread, NULL, obstacleDetection, NULL)) {
        std::cerr << "ERROR: Couldn't create obstacle detection thread!" << std::endl;
    }
    if (pthread_create(&showOutputImageThread, NULL, showOutputImage, NULL)) {
        std::cerr << "ERROR: Couldn't create show output image thread!" << std::endl;
    }
    if (pthread_create(&pathPlanningThread, NULL, pathPlanning, NULL)) {
        std::cerr << "ERROR: Couldn't create path planning thread!" << std::endl;
    }
    if (pthread_create(&vehicleControlThread, NULL, vehicleControl, NULL)) {
        std::cerr << "ERROR: Couldn't create vehicle control thread!" << std::endl;
    }

    // Join threads
    if (pthread_join(cameraCaptureThread, NULL)) {
        std::cerr << "ERROR: Couldn't join thread!" << std::endl;
    }
    if (pthread_join(detectLaneThread, NULL)) {
        std::cerr << "ERROR: Couldn't join thread!" << std::endl;
    }
    if (pthread_join(detectTrafficSignThread, NULL)) {
        std::cerr << "ERROR: Couldn't join thread!" << std::endl;
    }
    if (pthread_join(detectObstacleThread, NULL)) {
        std::cerr << "ERROR: Couldn't join thread!" << std::endl;
    }
    if (pthread_join(showOutputImageThread, NULL)) {
        std::cerr << "ERROR: Couldn't join thread!" << std::endl;
    }
    if (pthread_join(pathPlanningThread, NULL)) {
        std::cerr << "ERROR: Couldn't join thread!" << std::endl;
    }
    if (pthread_join(vehicleControlThread, NULL)) {
        std::cerr << "ERROR: Couldn't join thread" << std::endl;
    }
}

void systemConfigMode (void)
{
    std::cout << "---------------------------------" << std::endl;
    std::cout << "SYSTEM: Config Mode" << std::endl;
    
    ConfigMode mode = getConfigState();
    setModuleState(MODULE_CAP_CAM_IMAGE + MODULE_SHOW_OUT_IMAGE);

    pthread_t cameraCaptureThread;
    pthread_t configThread;
    //~ pthread_t showChessBoardThread;
    pthread_t showOutputImageThread;

    while (getSystemState() == SYS_MODE_CONFIG) {
        mode = getConfigState();

        if (pthread_create(&cameraCaptureThread, NULL, cameraCapture, NULL)) {
            std::cerr << "ERROR: Couldn't create camera capture thread!" << std::endl;
        }
        
        // Start modules and threads for configuration
        if (mode == CONFIG_MODE_NONE) {
            setModuleState(MODULE_CAP_CAM_IMAGE + MODULE_SHOW_OUT_IMAGE + MODULE_SHOW_IN_IMAGE);
            if (pthread_create(&configThread, NULL, showInputImage, NULL)) {
                std::cerr << "ERROR: Couldn't create config thread!" << std::endl;
            }
        }
        else if (mode == CONFIG_MODE_CALIB_INTRINSICS) {
            setModuleState(MODULE_CAP_CAM_IMAGE + MODULE_SHOW_OUT_IMAGE + MODULE_CONFIG_CALIB_INTR);
            if (pthread_create(&configThread, NULL, configCalibIntr, NULL)) {
                std::cerr << "ERROR: Couldn't create config thread!" << std::endl;
            }
        }
        else if (mode == CONFIG_MODE_CALIB_EXTRINSICS) {
            setModuleState(MODULE_CAP_CAM_IMAGE + MODULE_SHOW_OUT_IMAGE + MODULE_CONFIG_CALIB_EXTR);
            if (pthread_create(&configThread, NULL, configCalibExtr, NULL)) {
                std::cerr << "ERROR: Couldn't create config thread!" << std::endl;
            }
        }
        else if (mode == CONFIG_MODE_IMAGE_POSITION) {
            setModuleState(MODULE_CAP_CAM_IMAGE + MODULE_SHOW_OUT_IMAGE + MODULE_CONFIG_IMAGE_POSITION);
            if (pthread_create(&configThread, NULL, configImagePos, NULL)) {
                std::cerr << "ERROR: Couldn't create config thread!" << std::endl;
            }
        }
        if (pthread_create(&showOutputImageThread, NULL, showOutputImage, NULL)) {
            std::cerr << "ERROR: Couldn't create show output image thread!" << std::endl;
        }

        // Join threads
        if (pthread_join(cameraCaptureThread, NULL)) {
            std::cerr << "ERROR: Couldn't join thread!" << std::endl;
        }
        if (pthread_join(configThread, NULL)) {
            std::cerr << "ERROR: Couldn't join thread!" << std::endl;
        }
        if (pthread_join(showOutputImageThread, NULL)) {
            std::cerr << "ERROR: Couldn't join thread!" << std::endl;
        }
    }
}

void systemAboutMode (void)
{
    std::cout << "---------------------------------" << std::endl;
    std::cout << "SYSTEM: About Mode" << std::endl;

    setModuleState(MODULE_SHOW_OUT_IMAGE);

    pthread_t showOutputImageThread;

    if (pthread_create(&showOutputImageThread, NULL, showOutputImage, NULL)) {
        std::cerr << "ERROR: Couldn't create show output image thread!" << std::endl;
    }

    if (pthread_join(showOutputImageThread, NULL)) {
        std::cerr << "ERROR: Couldn't join thread!" << std::endl;
    }
}

void systemErrorMode (void)
{
    std::cout << "---------------------------------" << std::endl;
    std::cout << "SYSTEM: Error Mode" << std::endl;

    //! @todo ERROR mode
    setModuleState(MODULE_NONE);

    while (getSystemState() == SYS_MODE_ERROR) {
    }
}

void systemClosing (void)
{
    std::cout << "---------------------------------" << std::endl;
    std::cout << "SYSTEM: Closing Mode" << std::endl;

    //! @todo Closing mode
    setSystemState(SYS_MODE_CLOSING);
}

void autonomousDriver (void)
{
    SystemMode state = getSystemState();
    while (state != SYS_MODE_CLOSING) {
        switch (state) {
            case SYS_MODE_STANDBY: systemStandbyMode(); break;
            case SYS_MODE_AUTO: systemAutoMode(); break;
            case SYS_MODE_RC: systemRCMode(); break;
            case SYS_MODE_DEV: systemDevMode(); break;
            case SYS_MODE_CONFIG: systemConfigMode(); break;
            case SYS_MODE_ABOUT: systemAboutMode(); break;
            case SYS_MODE_ERROR: systemErrorMode(); break;
            default: systemClosing(); break;
        }
        state = getSystemState();
    }
}
