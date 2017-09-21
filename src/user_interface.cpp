
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
    setUiInputKey('n');
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
    
    if (state == UI_MODE_STANDBY) {
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
            sysState = SYS_MODE_STANDBY;
        }
        else if ((key == 'Q') || (key == 'q')) {
            state = UI_MODE_CLOSING;
            sysState = SYS_MODE_CLOSING;
        }
    }
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
        }
        else if ((key == 'Q') || (key == 'q')) {
            state = UI_MODE_CLOSING;
            sysState = SYS_MODE_CLOSING;
        }
    }
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
            cout << "Calibrating..." << endl;
        }
        else if ((key == 'Q') || (key == 'q')) {
            state = UI_MODE_CLOSING;
            sysState = SYS_MODE_CLOSING;
        }
    }
    else if (state == UI_MODE_CONFIG) {
        drawConfigMode(image);
        if (key == 'B') {
            state = UI_MODE_STANDBY;
            sysState = SYS_MODE_STANDBY;
        }
        else if (key == 'S') {
            cout << "Saving config..." << endl;
            setUiInputKey('S');
        }
        else if ((key == 'Q') || (key == 'q')) {
            state = UI_MODE_CLOSING;
            sysState = SYS_MODE_CLOSING;
        }
    }
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
        setUiInputKey('Q');
        setModuleState(MODULE_NONE);
        setSystemState(SYS_MODE_CLOSING);
    }
    
    if (prevState != state) {
        setUiStatus(state);
        cout << "Changing UI state to " << (int) state << endl;
    }
    if (prevSysState != sysState) {
        setModuleState(MODULE_NONE);
        setSystemState(sysState);
        cout << "Changing system state to " << (int) sysState << endl;
    }
}
