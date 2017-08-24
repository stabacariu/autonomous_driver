/**
 * @file user_interface.hpp
 * @author Sergiu-Petru Tabacariu
 * @date 27.6.2017
 */

#ifndef USER_INTERFACE_HPP
#define USER_INTERFACE_HPP

#include <iostream>
#include <pthread.h>
#include "autonomous_driver.hpp"
#include "user_interface_menus.hpp"

enum UIMode {
    UI_MODE_STANDBY,
    UI_MODE_AUTO,
    UI_MODE_RC,
    UI_MODE_DEV,
    UI_MODE_CONFIG,
    UI_MODE_ABOUT,
    UI_MODE_CLOSING
};

struct UIState {
    UIMode mode;
    char key;
    pthread_mutex_t lock;
};


void uiStateInit (void);
void setUiStatus (UIMode state);
UIMode getUiStatus (void);
void setUiInputKey (char key);
char getUiInputKey (void);
void processUiInput (cv::Mat& image, char key);

#endif // USER_INTERFACE_HPP
