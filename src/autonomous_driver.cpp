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

using namespace std;
using namespace cv;

void initSystemState (void)
{
    pthread_mutex_init(&systemState.lock, NULL);
    setSystemState(SYS_MODE_STANDBY);

    initModuleState();
}

void setSystemState (SystemMode state)
{
    if (pthread_mutex_lock(&systemState.lock)) {
        cerr << "ERROR: Couldn't lock status mutex!" << endl;
    }

    systemState.mode = state;

    if (pthread_mutex_unlock(&systemState.lock)) {
        cerr << "ERROR: Couldn't unlock status mutex!" << endl;
    }
}

SystemMode getSystemState (void)
{
    SystemMode mode;

    if (pthread_mutex_lock(&systemState.lock)) {
        cerr << "ERROR: Couldn't lock status mutex!" << endl;
    }

    mode = systemState.mode;

    if (pthread_mutex_unlock(&systemState.lock)) {
        cerr << "ERROR: Couldn't unlock status mutex!" << endl;
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
        cerr << "ERROR: Couldn't lock status mutex!" << endl;
    }

    moduleState.state = modules;

    if (pthread_mutex_unlock(&moduleState.lock)) {
        cerr << "ERROR: Couldn't unlock status mutex!" << endl;
    }
}

int getModuleState (void)
{
    int modules;

    if (pthread_mutex_lock(&moduleState.lock)) {
        cerr << "ERROR: Couldn't lock status mutex!" << endl;
    }

    modules = moduleState.state;

    if (pthread_mutex_unlock(&moduleState.lock)) {
        cerr << "ERROR: Couldn't unlock status mutex!" << endl;
    }

    return modules;
}

void systemStandbyMode (void)
{
    cout << "---------------------------------" << endl;
    cout << "SYSTEM: Standby Mode" << endl;

    // Start modules for standby mode
    setModuleState(MODULE_CAP_CAM_IMAGE + MODULE_SHOW_IN_IMAGE + MODULE_SHOW_OUT_IMAGE);

    pthread_t cameraCaptureThread;
    pthread_t showInputImageThread;
    pthread_t showOutputImageThread;

    // Create threads
    if (pthread_create(&cameraCaptureThread, NULL, cameraCapture, NULL)) {
        cerr << "ERROR: Couldn't create camera capture thread!" << endl;
    }
    if (pthread_create(&showInputImageThread, NULL, showInputImage, NULL)) {
        cerr << "ERROR: Couldn't create show input image thread!" << endl;
    }
    if (pthread_create(&showOutputImageThread, NULL, showOutputImage, NULL)) {
        cerr << "ERROR: Couldn't create show output image thread!" << endl;
    }

    // Join threads in the same sequence as they where created
    if (pthread_join(cameraCaptureThread, NULL)) {
        cerr << "ERROR: Couldn't join thread!" << endl;
    }
    if (pthread_join(showInputImageThread, NULL)) {
        cerr << "ERROR: Couldn't join thread!" << endl;
    }
    if (pthread_join(showOutputImageThread, NULL)) {
        cerr << "ERROR: Couldn't join thread!" << endl;
    }
}

void systemAutoMode (void)
{
    cout << "---------------------------------" << endl;
    cout << "SYSTEM: Autonomous Driving Mode" << endl;

    setModuleState(MODULE_CAP_CAM_IMAGE + MODULE_SHOW_OUT_IMAGE + MODULE_DETECT_LANES + MODULE_DETECT_OBSTACLE + MODULE_DETECT_TRAFFIC_SIGNS + MODULE_PLAN_PATH + MODULE_CONTROL_VEHICLE);

    pthread_t cameraCaptureThread;
    pthread_t detectLaneThread;
    pthread_t detectTrafficSignThread;
    //~ pthread_t detectObstacleThread;
    pthread_t detectObstacleThread;
    pthread_t showOutputImageThread;
    pthread_t pathPlanningThread;
    pthread_t vehicleControlThread;

    // Create threads
    if (pthread_create(&cameraCaptureThread, NULL, cameraCapture, NULL)) {
        cerr << "ERROR: Couldn't create camera capture thread!" << endl;
    }
    if (pthread_create(&detectLaneThread, NULL, laneDetection, NULL)) {
        cerr << "ERROR: Couldn't create lane detection thread!" << endl;
    }
    //~ if (pthread_create(&detectTrafficSignThread, NULL, trafficSignDetection, NULL)) {
        //~ cerr << "ERROR: Couldn't create traffic sign detection thread!" << endl;
    //~ }
    if (pthread_create(&detectObstacleThread, NULL, obstacleDetection, NULL)) {
        cerr << "ERROR: Couldn't create obstacle detection thread!" << endl;
    }
    if (pthread_create(&showOutputImageThread, NULL, showOutputImage, NULL)) {
        cerr << "ERROR: Couldn't create show output image thread!" << endl;
    }
    if (pthread_create(&pathPlanningThread, NULL, pathPlanning, NULL)) {
        cerr << "ERROR: Couldn't create path planning thread!" << endl;
    }
    if (pthread_create(&vehicleControlThread, NULL, vehicleControl, NULL)) {
        cerr << "ERROR: Couldn't create vehicle control thread!" << endl;
    }

    // Join threads
    if (pthread_join(cameraCaptureThread, NULL)) {
        cerr << "ERROR: Couldn't join thread!" << endl;
    }
    if (pthread_join(detectLaneThread, NULL)) {
        cerr << "ERROR: Couldn't join thread!" << endl;
    }
    //~ if (pthread_join(detectTrafficSignThread, NULL)) {
        //~ cerr << "ERROR: Couldn't join thread!" << endl;
    //~ }
    if (pthread_join(detectObstacleThread, NULL)) {
        cerr << "ERROR: Couldn't join thread!" << endl;
    }
    if (pthread_join(showOutputImageThread, NULL)) {
        cerr << "ERROR: Couldn't join thread!" << endl;
    }
    if (pthread_join(pathPlanningThread, NULL)) {
        cerr << "ERROR: Couldn't join thread!" << endl;
    }
    if (pthread_join(vehicleControlThread, NULL)) {
        cerr << "ERROR: Couldn't join thread" << endl;
    }
}

void systemRCMode (void)
{
    cout << "---------------------------------" << endl;
    cout << "SYSTEM: Remote Control Mode" << endl;

    setModuleState(MODULE_CAP_CAM_IMAGE + MODULE_SHOW_IN_IMAGE + MODULE_SHOW_OUT_IMAGE + MODULE_CONTROL_VEHICLE + MODULE_CONTROL_REMOTE);

    pthread_t cameraCaptureThread;
    pthread_t showInputImageThread;
    pthread_t showOutputImageThread;
    pthread_t remoteControlThread;
    pthread_t vehicleControlThread;

    // Create threads
    if (pthread_create(&cameraCaptureThread, NULL, cameraCapture, NULL)) {
        cerr << "ERROR: Couldn't create camera capture thread!" << endl;
    }
    if (pthread_create(&showInputImageThread, NULL, showInputImage, NULL)) {
        cerr << "ERROR: Couldn't create show input image thread!" << endl;
    }
    if (pthread_create(&showOutputImageThread, NULL, showOutputImage, NULL)) {
        cerr << "ERROR: Couldn't create show output image thread!" << endl;
    }
    if (pthread_create(&remoteControlThread, NULL, remoteControl, NULL)) {
        cerr << "ERROR: Couldn't create remote control thread!" << endl;
    }
    if (pthread_create(&vehicleControlThread, NULL, vehicleControl, NULL)) {
        cerr << "ERROR: Couldn't create vehicle control thread!" << endl;
    }

    // Join thread
    if (pthread_join(cameraCaptureThread, NULL)) {
        cerr << "ERROR: Couldn't join thread!" << endl;
    }
    if (pthread_join(showInputImageThread, NULL)) {
        cerr << "ERROR: Couldn't join thread!" << endl;
    }
    if (pthread_join(showOutputImageThread, NULL)) {
        cerr << "ERROR: Couldn't join thread!" << endl;
    }
    if (pthread_join(remoteControlThread, NULL)) {
        cerr << "ERROR: Couldn't join thread!" << endl;
    }
    if (pthread_join(vehicleControlThread, NULL)) {
        cerr << "ERROR: Couldn't join thread!" << endl;
    }
}

void systemDevMode (void)
{
    cout << "---------------------------------" << endl;
    cout << "SYSTEM: Development Mode" << endl;

    //! @todo Dev mode
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
        cerr << "ERROR: Couldn't create camera capture thread!" << endl;
    }
    if (pthread_create(&detectLaneThread, NULL, laneDetection, NULL)) {
        cerr << "ERROR: Couldn't create lane detection thread!" << endl;
    }
    if (pthread_create(&detectTrafficSignThread, NULL, trafficSignDetection, NULL)) {
        cerr << "ERROR: Couldn't create traffic sign detection thread!" << endl;
    }
    if (pthread_create(&detectObstacleThread, NULL, obstacleDetection, NULL)) {
        cerr << "ERROR: Couldn't create obstacle detection thread!" << endl;
    }
    if (pthread_create(&showOutputImageThread, NULL, showOutputImage, NULL)) {
        cerr << "ERROR: Couldn't create show output image thread!" << endl;
    }
    if (pthread_create(&pathPlanningThread, NULL, pathPlanning, NULL)) {
        cerr << "ERROR: Couldn't create path planning thread!" << endl;
    }
    if (pthread_create(&vehicleControlThread, NULL, vehicleControl, NULL)) {
        cerr << "ERROR: Couldn't create vehicle control thread!" << endl;
    }

    // Join threads
    if (pthread_join(cameraCaptureThread, NULL)) {
        cerr << "ERROR: Couldn't join thread!" << endl;
    }
    if (pthread_join(detectLaneThread, NULL)) {
        cerr << "ERROR: Couldn't join thread!" << endl;
    }
    if (pthread_join(detectTrafficSignThread, NULL)) {
        cerr << "ERROR: Couldn't join thread!" << endl;
    }
    if (pthread_join(detectObstacleThread, NULL)) {
        cerr << "ERROR: Couldn't join thread!" << endl;
    }
    if (pthread_join(showOutputImageThread, NULL)) {
        cerr << "ERROR: Couldn't join thread!" << endl;
    }
    if (pthread_join(pathPlanningThread, NULL)) {
        cerr << "ERROR: Couldn't join thread!" << endl;
    }
    if (pthread_join(vehicleControlThread, NULL)) {
        cerr << "ERROR: Couldn't join thread" << endl;
    }
}

void systemConfigMode (void)
{
    cout << "---------------------------------" << endl;
    cout << "SYSTEM: Config Mode" << endl;
    //! @todo Config mode

    ConfigMode mode = getConfigState();
    setModuleState(MODULE_CAP_CAM_IMAGE + MODULE_SHOW_OUT_IMAGE);

    pthread_t cameraCaptureThread;
    pthread_t configThread;
    //~ pthread_t showChessBoardThread;
    pthread_t showOutputImageThread;

    while (getSystemState() == SYS_MODE_CONFIG) {
        mode = getConfigState();

        if (pthread_create(&cameraCaptureThread, NULL, cameraCapture, NULL)) {
            cerr << "ERROR: Couldn't create camera capture thread!" << endl;
        }
        // Start modules and threads for configuration
        if (mode == CONFIG_MODE_NONE) {
            setModuleState(MODULE_CAP_CAM_IMAGE + MODULE_SHOW_OUT_IMAGE + MODULE_SHOW_IN_IMAGE);
            if (pthread_create(&configThread, NULL, showInputImage, NULL)) {
                cerr << "ERROR: Couldn't create config thread!" << endl;
            }
        }
        else if (mode == CONFIG_MODE_CALIB_INTRINSICS) {
            setModuleState(MODULE_CAP_CAM_IMAGE + MODULE_SHOW_OUT_IMAGE + MODULE_CONFIG_CALIB_INTR);
            if (pthread_create(&configThread, NULL, configCalibIntr, NULL)) {
                cerr << "ERROR: Couldn't create config thread!" << endl;
            }
        }
        else if (mode == CONFIG_MODE_CALIB_EXTRINSICS) {
            setModuleState(MODULE_CAP_CAM_IMAGE + MODULE_SHOW_OUT_IMAGE + MODULE_CONFIG_CALIB_EXTR);
            if (pthread_create(&configThread, NULL, configCalibExtr, NULL)) {
                cerr << "ERROR: Couldn't create config thread!" << endl;
            }
        }
        else if (mode == CONFIG_MODE_IMAGE_POSITION) {
            setModuleState(MODULE_CAP_CAM_IMAGE + MODULE_SHOW_OUT_IMAGE + MODULE_CONFIG_IMAGE_POSITION);
            if (pthread_create(&configThread, NULL, configImagePos, NULL)) {
                cerr << "ERROR: Couldn't create config thread!" << endl;
            }
        }
        if (pthread_create(&showOutputImageThread, NULL, showOutputImage, NULL)) {
            cerr << "ERROR: Couldn't create show output image thread!" << endl;
        }

        // Join threads
        if (pthread_join(cameraCaptureThread, NULL)) {
            cerr << "ERROR: Couldn't join thread!" << endl;
        }
        if (pthread_join(configThread, NULL)) {
            cerr << "ERROR: Couldn't join thread!" << endl;
        }
        if (pthread_join(showOutputImageThread, NULL)) {
            cerr << "ERROR: Couldn't join thread!" << endl;
        }
    }
}

void systemAboutMode (void)
{
    cout << "---------------------------------" << endl;
    cout << "SYSTEM: About Mode" << endl;

    setModuleState(MODULE_SHOW_OUT_IMAGE);

    pthread_t showOutputImageThread;

    if (pthread_create(&showOutputImageThread, NULL, showOutputImage, NULL)) {
        cerr << "ERROR: Couldn't create show output image thread!" << endl;
    }

    if (pthread_join(showOutputImageThread, NULL)) {
        cerr << "ERROR: Couldn't join thread!" << endl;
    }
}

void systemErrorMode (void)
{
    cout << "---------------------------------" << endl;
    cout << "SYSTEM: Error Mode" << endl;

    //! @todo ERROR mode
    setModuleState(MODULE_NONE);

    while (getSystemState() == SYS_MODE_ERROR) {
    }
}

void systemClosing (void)
{
    cout << "---------------------------------" << endl;
    cout << "SYSTEM: Closing Mode" << endl;

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
