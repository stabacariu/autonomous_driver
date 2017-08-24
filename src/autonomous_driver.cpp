/**
 * @file autonomous_driver.cpp
 * @author Sergiu-Petru Tabacariu
 * @date 27.6.2017
 * 
 * @brief This programm holds all functions to demonstrate an autonmous
 * driving car.
 */
 
#include "autonomous_driver.hpp"
 
SystemState systemState;
ModuleState moduleState;

using namespace std;
using namespace cv;
 
void systemStateInit (void)
{
    // Init system state
    pthread_mutex_init(&systemState.lock, NULL);
    setSystemState(SYS_MODE_STANDBY);
    // Init module state
    pthread_mutex_init(&moduleState.lock, NULL);
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
    SystemMode state;
    
    if (pthread_mutex_lock(&systemState.lock)) {
        cerr << "ERROR: Couldn't lock status mutex!" << endl;
    }
    
    state = systemState.mode;
    
    if (pthread_mutex_unlock(&systemState.lock)) {
        cerr << "ERROR: Couldn't unlock status mutex!" << endl;
    }
    
    return state;
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
    cout << "SYSTEM: Standby Mode" << endl;
    
    setModuleState(MODULE_CAP_CAM_IMAGE + MODULE_SHOW_IN_IMAGE + MODULE_SHOW_OUT_IMAGE);
        
    pthread_t cameraCaptureThread;
    pthread_t showInputImageThread;
    pthread_t showOutputImageThread;
    
    // Create image capturing thread
    if (pthread_create(&cameraCaptureThread, NULL, cameraCapture, NULL)) {
        cerr << "ERROR: Couldn't create camera capture thread!" << endl;
    }
    // Create image standby thread
    if (pthread_create(&showInputImageThread, NULL, showInputImage, NULL)) {
        cerr << "ERROR: Couldn't create show input image thread!" << endl;
    }
    // Create image show tread
    if (pthread_create(&showOutputImageThread, NULL, showOutputImage, NULL)) {
        cerr << "ERROR: Couldn't create show output image thread!" << endl;
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
}

void systemAutoMode (void)
{
    cout << "SYSTEM: Autonomous Driving Mode" << endl;
    
    setModuleState(MODULE_CAP_CAM_IMAGE + MODULE_SHOW_OUT_IMAGE + MODULE_DETECT_LANES);
    
    pthread_t cameraCaptureThread;
    pthread_t detectLaneThread;
    //~ pthread_t detectTrafficSignThread;
    //~ pthread_t detectObstacleThread;
    pthread_t showOutputImageThread;
    
    // Create image capturing thread
    if (pthread_create(&cameraCaptureThread, NULL, cameraCapture, NULL)) {
        cerr << "ERROR: Couldn't create camera capture thread!" << endl;
    }
    // Create detect lane thread
    if (pthread_create(&detectLaneThread, NULL, laneDetection, NULL)) {
        cerr << "ERROR: Couldn't create lane detection thread!" << endl;
    }
    // Create detect traffic signs thread
    //~ if (pthread_create(&detectTrafficSignThread, NULL, trafficSignDetection, NULL)) {
        //~ cerr << "ERROR: Couldn't create traffic sign detection thread!" << endl;
    //~ }
    // Create show output image thread
    if (pthread_create(&showOutputImageThread, NULL, showOutputImage, NULL)) {
        cerr << "ERROR: Couldn't create show output image thread!" << endl;
    }
    
    // Join image capturing thread
    if (pthread_join(cameraCaptureThread, NULL)) {
        cerr << "ERROR: Couldn't join thread!" << endl;
    }
    // Join image processing threads
    if (pthread_join(detectLaneThread, NULL)) {
        cerr << "ERROR: Couldn't join thread!" << endl;
    }
    //~ if (pthread_join(detectTrafficSignThread, NULL)) {
        //~ cerr << "ERROR: Couldn't join thread!" << endl;
    //~ }
    if (pthread_join(showOutputImageThread, NULL)) {
        cerr << "ERROR: Couldn't join thread!" << endl;
    }
}

void systemRCMode (void)
{
    cout << "SYSTEM: Remote Control Mode" << endl;
    
    setModuleState(MODULE_CAP_CAM_IMAGE + MODULE_SHOW_IN_IMAGE + MODULE_SHOW_OUT_IMAGE);
    
    // TODO: RC mode
    pthread_t cameraCaptureThread;
    pthread_t showInputImageThread;
    pthread_t showOutputImageThread;
    //~ pthread_t remoteControlThread;
    //~ pthread_t vehicleControlThread;
    
    // Create image capturing thread
    if (pthread_create(&cameraCaptureThread, NULL, cameraCapture, NULL)) {
        cerr << "ERROR: Couldn't create camera capture thread!" << endl;
    }
    // Create image standby thread
    if (pthread_create(&showInputImageThread, NULL, showInputImage, NULL)) {
        cerr << "ERROR: Couldn't create show input image thread!" << endl;
    }
    // Create image show tread
    if (pthread_create(&showOutputImageThread, NULL, showOutputImage, NULL)) {
        cerr << "ERROR: Couldn't create show output image thread!" << endl;
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
}

void systemDevMode (void)
{
    cout << "SYSTEM: Development Mode" << endl;
    
    // TODO: Dev mode
    setModuleState(MODULE_CAP_CAM_IMAGE + MODULE_SHOW_IN_IMAGE + MODULE_SHOW_OUT_IMAGE);
    
    pthread_t cameraCaptureThread;
    pthread_t showInputImageThread;
    pthread_t showOutputImageThread;
    
    // Create image capturing thread
    if (pthread_create(&cameraCaptureThread, NULL, cameraCapture, NULL)) {
        cerr << "ERROR: Couldn't create camera capture thread!" << endl;
    }
    // Create image standby thread
    if (pthread_create(&showInputImageThread, NULL, showInputImage, NULL)) {
        cerr << "ERROR: Couldn't create show input image thread!" << endl;
    }
    // Create image show tread
    if (pthread_create(&showOutputImageThread, NULL, showOutputImage, NULL)) {
        cerr << "ERROR: Couldn't create show output image thread!" << endl;
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
}

void systemConfigMode (void)
{
    cout << "SYSTEM: Config Mode" << endl;
    // TODO: Config mode
}

void systemAboutMode (void)
{
    cout << "SYSTEM: About Mode" << endl;
    // TODO: About mode
}

void systemErrorMode (void)
{
    cout << "SYSTEM: Error Mode" << endl;
    // TODO: ERROR mode
}

void systemClosing (void)
{
    cout << "SYSTEM: Closing Mode" << endl;
    
    // TODO: Closing mode
    setModuleState(MODULE_NONE);
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
