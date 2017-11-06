
/**
 * @file user_intefrace.cpp
 * @author Sergiu-Petru Tabacariu
 * @date 3.7.2017
 */

#include "user_interface.hpp"

UIState uiState;

using namespace std;
using namespace cv;

void initUiState (void)
{
    pthread_mutex_init(&uiState.lock, NULL);
    setUiStatus(UI_MODE_STANDBY);
    setUiInputKey(-1); // No key was pushed
}

void setUiStatus (UIMode state)
{
    if (pthread_mutex_lock(&uiState.lock)) {
        cerr << "ERROR: Couldn't lock status mutex!" << endl;
    }
    
    uiState.mode = state;
    
    if (pthread_mutex_unlock(&uiState.lock)) {
        cerr << "ERROR: Couldn't unlock status mutex!" << endl;
    }
}

UIMode getUiStatus (void)
{
    UIMode state;
    if (pthread_mutex_lock(&uiState.lock)) {
        cerr << "ERROR: Couldn't lock status mutex!" << endl;
    }
    
    state = uiState.mode;
    
    if (pthread_mutex_unlock(&uiState.lock)) {
        cerr << "ERROR: Couldn't unlock status mutex!" << endl;
    }
    
    return state;
}

void setUiInputKey (char key)
{
    if (pthread_mutex_lock(&uiState.lock)) {
        cerr << "ERROR: Couldn't lock status mutex!" << endl;
    }
    
    uiState.key = key;
    
    if (pthread_mutex_unlock(&uiState.lock)) {
        cerr << "ERROR: Couldn't unlock status mutex!" << endl;
    }
}

char getUiInputKey (void)
{
    char key;
    if (pthread_mutex_lock(&uiState.lock)) {
        cerr << "ERROR: Couldn't lock status mutex!" << endl;
    }
    
    key = uiState.key;
    // Reset key to -1
    //~ uiState.key = -1;
    
    if (pthread_mutex_unlock(&uiState.lock)) {
        cerr << "ERROR: Couldn't unlock status mutex!" << endl;
    }
    
    return key;
}

void processUiInput (Mat& image, char key)
{
    UIMode state = getUiStatus();
    UIMode prevState = state;
    SystemMode sysState = getSystemState();
    SystemMode prevSysState = sysState;
    ConfigMode configState = getConfigState();
    ConfigMode preConfigState = configState;
    
    // Close program if ESC key was pressed.
    if (key == 27) {
        state = UI_MODE_CLOSING;
        sysState = SYS_MODE_CLOSING;
    }
    // Key handling for standby mode
    else if (state == UI_MODE_STANDBY) {
        drawMainMenu(image);
        if (key == 'A') {
            state = UI_MODE_AUTO;
            sysState = SYS_MODE_AUTO;
        }
        else if (key == 'R') {
            state = UI_MODE_RC;
            sysState = SYS_MODE_RC;
        }
        else if (key == 'D') {
            state = UI_MODE_DEV;
            sysState = SYS_MODE_DEV;
        }
        else if (key == 'C') {
            state = UI_MODE_CONFIG;
            sysState = SYS_MODE_CONFIG;
        }
        else if (key == 'S') {
            state = UI_MODE_ABOUT;
            sysState = SYS_MODE_ABOUT;
        }
        else if ((key == 'Q') || (key == 'q')) {
            state = UI_MODE_CLOSING;
            sysState = SYS_MODE_CLOSING;
        }
    }
    // Key handling for autonomous mode
    else if (state == UI_MODE_AUTO) {
        drawAutoMode(image);
        if (key == 'B') {
            state = UI_MODE_STANDBY;
            sysState = SYS_MODE_STANDBY;
        }
        else if ((key == 'Q') || (key == 'q')) {
            state = UI_MODE_CLOSING;
            sysState = SYS_MODE_CLOSING;
        }
    }
    // Key handling for remote control mode
    else if (state == UI_MODE_RC) {
        drawRcMode(image);
        if (key == 'B') {
            state = UI_MODE_STANDBY;
            sysState = SYS_MODE_STANDBY;
        }
        else if (key == 'A') {
            state = UI_MODE_AUTO;
            sysState = SYS_MODE_AUTO;
        }
        else if ((key == 'Q') || (key == 'q')) {
            state = UI_MODE_CLOSING;
            sysState = SYS_MODE_CLOSING;
        }
    }
    // Key handling for development mode
    else if (state == UI_MODE_DEV) {
        drawDevMode(image);
        if (key == 'B') {
            state = UI_MODE_STANDBY;
            sysState = SYS_MODE_STANDBY;
        }
        else if (key == 'A') {
            state = UI_MODE_AUTO;
            sysState = SYS_MODE_AUTO;
        }
        else if (key == 'S') {
            cout << "Screenshot..." << endl;
        }
        else if (key == 'C') {
            state = UI_MODE_CONFIG;
            sysState = SYS_MODE_CONFIG;
        }
        else if ((key == 'Q') || (key == 'q')) {
            state = UI_MODE_CLOSING;
            sysState = SYS_MODE_CLOSING;
        }
    }
    // Key handling for configuration mode
    else if (state == UI_MODE_CONFIG) {
        FileStorage fs("../config/config.xml", FileStorage::WRITE);
        ConfigData c;
        
        if ((key == 'Q') || (key == 'q')) {
            configState = CONFIG_MODE_NONE;
            state = UI_MODE_CLOSING;
            sysState = SYS_MODE_CLOSING;
            configState = CONFIG_MODE_NONE;
        }
        // Config mode sub menu
        if (configState == CONFIG_MODE_NONE) {
            drawConfigMode(image);
            if (key == 'B') {
                state = UI_MODE_STANDBY;
                sysState = SYS_MODE_STANDBY;
            }
            else if (key == 'R') {
                //! @todo reset configuration
                cout << "Resetting config..." << endl;
                Mat homography;
                setExtrinsics(homography);
            }
            else if (key == 'I') {
                configState = CONFIG_MODE_CALIB_INTRINSICS;
            }
            else if (key == 'E') {
                configState = CONFIG_MODE_CALIB_EXTRINSICS;
            }
            else if (key == 'P') {
                configState =CONFIG_MODE_IMAGE_POSITION;
            }
        }
        else if (configState == CONFIG_MODE_CALIB_INTRINSICS) {
            drawCalibIntrinsics(image);
            if (key == 'B') {
                state = UI_MODE_CONFIG;
                sysState = SYS_MODE_CONFIG;
                configState = CONFIG_MODE_NONE;
            }
            else if (key == 'R') {
                cout << "Resetting config..." << endl;
                Mat homography;
                setExtrinsics(homography);
                //! @todo reset configuration
            }
            else if (key == 'S') {
                cout << "Saving config..." << endl;
                c = getConfigData();
                saveConfig(fs, c);
                //! @todo Save configuration
            }
        }
        else if (configState == CONFIG_MODE_CALIB_EXTRINSICS) {
            drawCalibExtrinsics(image);
            if (key == 'B') {
                state = UI_MODE_CONFIG;
                sysState = SYS_MODE_CONFIG;
                configState = CONFIG_MODE_NONE;
            }
            else if (key == 'R') {
                cout << "Resetting config..." << endl;
                Mat homography;
                setExtrinsics(homography);
                //! @todo reset configuration
            }
            else if (key == 'S') {
                cout << "Saving config..." << endl;
                c = getConfigData();
                saveConfig(fs, c);
                //! @todo Save configuration
            }
        }
        else if (configState == CONFIG_MODE_IMAGE_POSITION) {
            drawPositionImage(image);
            if (key == 'B') {
                state = UI_MODE_CONFIG;
                sysState = SYS_MODE_CONFIG;
                configState = CONFIG_MODE_NONE;
            }
            else if (key == 'R') {
                cout << "Resetting config..." << endl;
                //! @todo reset configuration
            }
            else if (key == 'S') {
                cout << "Saving config..." << endl;
                //! @todo Save configuration
            }
        }
        fs.release();
    }
    // Key handling for about mode
    else if (state == UI_MODE_ABOUT) {
        drawAboutMode(image);
        if (key == 'B') {
            state = UI_MODE_STANDBY;
            sysState = SYS_MODE_STANDBY;
        }
        else if ((key == 'Q') || (key == 'q')) {
            state = UI_MODE_CLOSING;
            sysState = SYS_MODE_CLOSING;
        }
    }
    else if (state == UI_MODE_CLOSING) {
        setModuleState(MODULE_NONE);
        setSystemState(SYS_MODE_CLOSING);
    }
    
    // Change states only if not the same as previous states
    if (prevState != state) {
        setUiStatus(state);
    }
    if (prevSysState != sysState) {
        setModuleState(MODULE_NONE);
        setSystemState(sysState);
    }
    if (sysState == SYS_MODE_CONFIG) {
        if (preConfigState != configState) {
            setModuleState(MODULE_NONE);
            setConfigState(configState);
        }
    }
}
