/**
 * @file user_interface.cpp
 * @author Sergiu-Petru Tabacariu
 * @date 10.4.2018
 */

#include "user_interface.hpp"

void UserInterface::start (ImageData& imageData, UserInterfaceData& uiData)
{
    std::cout << "THREAD: User interface started." << std::endl;
    running = true;
    
    cv::namedWindow("Autonomous Driver 1.0", CV_WINDOW_AUTOSIZE);
    
    while (running) {
        image = imageData.read();
        if (!image.empty()) {
            imshow("Autonomous Driver 1.0", image);
            guiInputKey = cv::waitKey(1000/30);
            
            //~ processUiInput(image, guiInputKey);
        }
        
        //~ if ((guiInputKey == 27) || (guiInputKey =='q')) {
            //~ std::cout << "THREAD: Closing user interface..." << std::endl;
            //~ running = false;
        //~ }
        
        if (uiData.getKey() == (char)(-1)) {
            uiData.setKey(guiInputKey);
        }
        
    }

    std::cout << "THREAD: User interface ended." << std::endl;
}

void UserInterface::stop ()
{
    running = false;
}

bool UserInterface::isRunning ()
{
    return running;
}

void UserInterface::consoleInput (UserInterfaceData& uiData)
{
    std::cout << "THREAD: User input started." << std::endl;
    running = true;
    std::ios_base::sync_with_stdio(false);
    
    while (running) {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        
        //~ if ((consoleInputKey == 27) || (consoleInputKey == 'q')) {
            //~ std::cout << "THREAD: Closing user interface..." << std::endl;
            //~ running = false;
        //~ }
        
        if (std::cin.readsome(&consoleInputKey, 1) < 1) {
            consoleInputKey = (char)(-1);
        }
        
        if (uiData.getKey() == (char)(-1)) {
            uiData.setKey(consoleInputKey);
        }
    }
    
    std::ios_base::sync_with_stdio(true);
    
    std::cout << "THREAD: User input ended." << std::endl;
}

//~ void UserInterface::processUiInput (cv::Mat& image, char key)
//~ {
    //~ UIMode state = getUiStatus();
    //~ UIMode prevState = state;
    //~ SystemMode sysState = getSystemState();
    //~ SystemMode prevSysState = sysState;
    //~ ConfigMode configState = getConfigState();
    //~ ConfigMode preConfigState = configState;
    
    //~ // Close program if ESC key was pressed.
    //~ if (key == 27) {
        //~ state = UI_MODE_CLOSING;
        //~ sysState = SYS_MODE_CLOSING;
    //~ }
    //~ // Key handling for standby mode
    //~ else if (state == UI_MODE_STANDBY) {
        //~ drawMainMenu(image);
        //~ if (key == 'A') {
            //~ state = UI_MODE_AUTO;
            //~ sysState = SYS_MODE_AUTO;
        //~ }
        //~ else if (key == 'R') {
            //~ state = UI_MODE_RC;
            //~ sysState = SYS_MODE_RC;
        //~ }
        //~ else if (key == 'D') {
            //~ state = UI_MODE_DEV;
            //~ sysState = SYS_MODE_DEV;
        //~ }
        //~ else if (key == 'C') {
            //~ state = UI_MODE_CONFIG;
            //~ sysState = SYS_MODE_CONFIG;
        //~ }
        //~ else if (key == 'S') {
            //~ state = UI_MODE_ABOUT;
            //~ sysState = SYS_MODE_ABOUT;
        //~ }
        //~ else if ((key == 'Q') || (key == 'q')) {
            //~ state = UI_MODE_CLOSING;
            //~ sysState = SYS_MODE_CLOSING;
        //~ }
    //~ }
    //~ // Key handling for autonomous mode
    //~ else if (state == UI_MODE_AUTO) {
        //~ drawAutoMode(image);
        //~ if (key == 'B') {
            //~ state = UI_MODE_STANDBY;
            //~ sysState = SYS_MODE_STANDBY;
        //~ }
        //~ else if ((key == 'Q') || (key == 'q')) {
            //~ state = UI_MODE_CLOSING;
            //~ sysState = SYS_MODE_CLOSING;
        //~ }
    //~ }
    //~ // Key handling for remote control mode
    //~ else if (state == UI_MODE_RC) {
        //~ drawRcMode(image);
        //~ if (key == 'B') {
            //~ state = UI_MODE_STANDBY;
            //~ sysState = SYS_MODE_STANDBY;
        //~ }
        //~ else if (key == 'A') {
            //~ state = UI_MODE_AUTO;
            //~ sysState = SYS_MODE_AUTO;
        //~ }
        //~ else if ((key == 'Q') || (key == 'q')) {
            //~ state = UI_MODE_CLOSING;
            //~ sysState = SYS_MODE_CLOSING;
        //~ }
    //~ }
    //~ // Key handling for development mode
    //~ else if (state == UI_MODE_DEV) {
        //~ drawDevMode(image);
        //~ if (key == 'B') {
            //~ state = UI_MODE_STANDBY;
            //~ sysState = SYS_MODE_STANDBY;
        //~ }
        //~ else if (key == 'A') {
            //~ state = UI_MODE_AUTO;
            //~ sysState = SYS_MODE_AUTO;
        //~ }
        //~ else if (key == 'S') {
            //~ std::cout << "Screenshot..." << std::endl;
        //~ }
        //~ else if (key == 'C') {
            //~ state = UI_MODE_CONFIG;
            //~ sysState = SYS_MODE_CONFIG;
        //~ }
        //~ else if ((key == 'Q') || (key == 'q')) {
            //~ state = UI_MODE_CLOSING;
            //~ sysState = SYS_MODE_CLOSING;
        //~ }
    //~ }
    //~ // Key handling for configuration mode
    //~ else if (state == UI_MODE_CONFIG) {
        //~ if ((key == 'Q') || (key == 'q')) {
            //~ configState = CONFIG_MODE_NONE;
            //~ state = UI_MODE_CLOSING;
            //~ sysState = SYS_MODE_CLOSING;
            //~ configState = CONFIG_MODE_NONE;
        //~ }
        //~ // Config mode sub menu
        //~ if (configState == CONFIG_MODE_NONE) {
            //~ drawConfigMode(image);
            //~ if (key == 'B') {
                //~ state = UI_MODE_STANDBY;
                //~ sysState = SYS_MODE_STANDBY;
            //~ }
            //~ else if (key == 'R') {
                //~ //! @todo reset configuration
                //~ std::cout << "Resetting config..." << std::endl;
                //~ cv::Mat homography;
                //~ setExtr(homography);
            //~ }
            //~ else if (key == 'S') {
                //~ std::cout << "Saving config..." << std::endl;
                //~ saveCalibConfig();
            //~ }
            //~ else if (key == 'I') {
                //~ configState = CONFIG_MODE_CALIB_INTRINSICS;
            //~ }
            //~ else if (key == 'E') {
                //~ configState = CONFIG_MODE_CALIB_EXTRINSICS;
            //~ }
            //~ else if (key == 'P') {
                //~ configState =CONFIG_MODE_IMAGE_POSITION;
            //~ }
        //~ }
        //~ else if (configState == CONFIG_MODE_CALIB_INTRINSICS) {
            //~ drawCalibIntrinsics(image);
            //~ if (key == 'B') {
                //~ state = UI_MODE_CONFIG;
                //~ sysState = SYS_MODE_CONFIG;
                //~ configState = CONFIG_MODE_NONE;
            //~ }
            //~ else if (key == 'R') {
                //~ std::cout << "Resetting config..." << std::endl;
                //~ cv::Mat homography;
                //~ setExtr(homography);
                //~ //! @todo reset configuration
            //~ }
            //~ else if (key == 'S') {
                //~ std::cout << "Saving config..." << std::endl;
                //~ saveCalibConfig();
                //~ //! @todo Save configuration
            //~ }
        //~ }
        //~ else if (configState == CONFIG_MODE_CALIB_EXTRINSICS) {
            //~ drawCalibExtrinsics(image);
            //~ if (key == 'B') {
                //~ state = UI_MODE_CONFIG;
                //~ sysState = SYS_MODE_CONFIG;
                //~ configState = CONFIG_MODE_NONE;
            //~ }
            //~ else if (key == 'R') {
                //~ std::cout << "Resetting config..." << std::endl;
                //~ cv::Mat homography;
                //~ setExtr(homography);
                //~ //! @todo reset configuration
            //~ }
            //~ else if (key == 'S') {
                //~ std::cout << "Saving config..." << std::endl;
                //~ saveCalibConfig();
                //~ //! @todo Save configuration
            //~ }
        //~ }
        //~ else if (configState == CONFIG_MODE_IMAGE_POSITION) {
            //~ drawPositionImage(image);
            //~ if (key == 'B') {
                //~ state = UI_MODE_CONFIG;
                //~ sysState = SYS_MODE_CONFIG;
                //~ configState = CONFIG_MODE_NONE;
            //~ }
            //~ else if (key == 'R') {
                //~ std::cout << "Resetting config..." << std::endl;
                //~ //! @todo reset configuration
            //~ }
            //~ else if (key == 'S') {
                //~ std::cout << "Saving config..." << std::endl;
                //~ //! @todo Save configuration
            //~ }
        //~ }
    //~ }
    //~ // Key handling for about mode
    //~ else if (state == UI_MODE_ABOUT) {
        //~ drawAboutMode(image);
        //~ if (key == 'B') {
            //~ state = UI_MODE_STANDBY;
            //~ sysState = SYS_MODE_STANDBY;
        //~ }
        //~ else if ((key == 'Q') || (key == 'q')) {
            //~ state = UI_MODE_CLOSING;
            //~ sysState = SYS_MODE_CLOSING;
        //~ }
    //~ }
    //~ else if (state == UI_MODE_CLOSING) {
        //~ setModuleState(MODULE_NONE);
        //~ setSystemState(SYS_MODE_CLOSING);
    //~ }
    
    //~ // Change states only if not the same as previous states
    //~ if (prevState != state) {
        //~ setUiStatus(state);
    //~ }
    //~ if (prevSysState != sysState) {
        //~ setModuleState(MODULE_NONE);
        //~ setSystemState(sysState);
    //~ }
    //~ if (sysState == SYS_MODE_CONFIG) {
        //~ if (preConfigState != configState) {
            //~ setModuleState(MODULE_NONE);
            //~ setConfigState(configState);
        //~ }
    //~ }
//~ }

void UserInterface::setUserInput (char c)
{
    std::lock_guard<std::mutex> guard(lock);
    guiInputKey = c;
    consoleInputKey = c;
}

char UserInterface::getUserInput ()
{
    std::lock_guard<std::mutex> guard(lock);
    if (guiInputKey == consoleInputKey) {
        return guiInputKey;
    }
    else if ((guiInputKey == (char)(-1)) && (consoleInputKey != (char)(-1))) {
        return consoleInputKey;
    }
    else if ((guiInputKey != (char)(-1)) && (consoleInputKey == (char)(-1))) {
        return guiInputKey;
    }
    else {
        return guiInputKey;
    }
}
