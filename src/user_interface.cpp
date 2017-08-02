
/**
 * @file user_intefrace.cpp
 * @author Sergiu-Petru Tabacariu
 * @date 3.7.2017
 */

#include "user_interface.hpp"

UIState uiState;

using namespace std;
using namespace cv;

void uiStateInit (void)
{
    pthread_mutex_init(&uiState.lock, NULL);
    setUiStatus(UI_MODE_STANDBY);
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

void processUiInput (Mat& image, char key)
{
    UIMode state = getUiStatus();
    SystemMode sysState = getSystemState();
    
    if (state == UI_MODE_STANDBY) {
        drawMainMenu(image);
        if (key == 'A') {
            state = UI_MODE_AUTO;
            sysState = SYS_MODE_AUTO;
            //drawAutoMode(image);
        }
        else if (key == 'R') {
            state = UI_MODE_RC;
            sysState = SYS_MODE_RC;
            //drawRcMode(image);
        }
        else if (key == 'D') {
            state = UI_MODE_DEV;
            sysState = SYS_MODE_DEV;
            //drawDevMode(image);
        }
        else if (key == 'C') {
            state = UI_MODE_CONFIG;
            sysState = SYS_MODE_CONFIG;
            //drawConfigMode(image);
        }
        else if (key == 'S') {
            state = UI_MODE_ABOUT;
            sysState = SYS_MODE_STANDBY;
        }
        else if ((key == 'Q') || (key == 'q')) {
            sysState = SYS_MODE_CLOSING;
        }
    }
    else if (state == UI_MODE_AUTO) {
        drawAutoMode(image);
        if (key == 'B') {
            state = UI_MODE_STANDBY;
            sysState = SYS_MODE_STANDBY;
            //drawMainMenu(image);
        }
        else if ((key == 'Q') || (key == 'q')) {
            sysState = SYS_MODE_CLOSING;
        }
    }
    else if (state == UI_MODE_RC) {
        drawRcMode(image);
        if (key == 'B') {
            state = UI_MODE_STANDBY;
            sysState = SYS_MODE_STANDBY;
            //drawMainMenu(image);
        }
        else if (key == 'A') {
            state = UI_MODE_AUTO;
            sysState = SYS_MODE_AUTO;
            //drawAutoMode(image);
        }
        else if ((key == 'Q') || (key == 'q')) {
            sysState = SYS_MODE_CLOSING;
        }
    }
    else if (state == UI_MODE_DEV) {
        drawDevMode(image);
        if (key == 'B') {
            state = UI_MODE_STANDBY;
            sysState = SYS_MODE_STANDBY;
            //drawMainMenu(image);
        }
        else if (key == 'A') {
            state = UI_MODE_AUTO;
            sysState = SYS_MODE_AUTO;
            //(image);
        }
        else if (key == 'S') {
            cout << "Screenshot..." << endl;
        }
        else if (key == 'C') {
            cout << "Calibrating..." << endl;
        }
        else if ((key == 'Q') || (key == 'q')) {
            sysState = SYS_MODE_CLOSING;
        }
    }
    else if (state == UI_MODE_CONFIG) {
        drawConfigMode(image);
        if (key == 'B') {
            state = UI_MODE_STANDBY;
            sysState = SYS_MODE_STANDBY;
            //drawMainMenu(image);
        }
        else if (key == 'S') {
            cout << "Saving config..." << endl;
        }
        else if ((key == 'Q') || (key == 'q')) {
            sysState = SYS_MODE_CLOSING;
        }
    }
    else if (state == UI_MODE_ABOUT) {
        drawAboutMode(image);
        if (key == 'B') {
            state = UI_MODE_STANDBY;
            sysState = SYS_MODE_STANDBY;
            //drawMainMenu(image);
        }
        else if ((key == 'Q') || (key == 'q')) {
            sysState = SYS_MODE_CLOSING;
        }
    }
    
    setUiStatus(state);
    setSystemState(sysState);
}
