/**
 * @file user_interface.hpp
 * @author Sergiu-Petru Tabacariu
 * @date 27.6.2017
 */

/**
 * @defgroup user_interface User Interface
 * @{
 * @}
 */

#ifndef USER_INTERFACE_HPP
#define USER_INTERFACE_HPP

#include <iostream>
#include <pthread.h>
#include "autonomous_driver.hpp"
#include "configuration.hpp"
#include "user_interface_menus.hpp"

//! @addtogroup user_interface
//! @{

/**
 * @brief A enum to describe all user interface modes
 */
enum UIMode {
    UI_MODE_STANDBY,
    UI_MODE_AUTO,
    UI_MODE_RC,
    UI_MODE_DEV,
    UI_MODE_CONFIG,
    UI_MODE_ABOUT,
    UI_MODE_CLOSING
};

/**
 * @brief A struct to describe the user interface state
 */
struct UIState {
    UIMode mode;
    char key;
    pthread_mutex_t lock;
};

/**
 * @brief A function to initialize the user interface state
 * 
 * This function initializes the user interface state by setting the
 * a default starting state and initializing the mutex for synchronized
 * access.
 */
void initUiState (void);

/**
 * @brief A function to set the user interface status
 * 
 * This function sets the user interface status by locking the user interface state.
 * 
 * @param state User interface mode
 */
void setUiStatus (UIMode state);

/**
 * @brief A function to get the user interface status
 * 
 * This function gets the user interface status by locking the user interface state.
 * 
 * @return User interface mode
 */
UIMode getUiStatus (void);

/**
 * @brief A function to set the user interface input key
 * 
 * This function sets an input key pressed by the user throw the 
 * user interface.
 * 
 * @note If no key is pressed OpenCVs HighGUI returns -1.
 * 
 * @param key User interface input key
 */
void setUiInputKey (char key);

/**
 * @brief A function to get the user interface input key
 * 
 * This function gets an input key pressed by the user throw the 
 * user interface.
 * 
 * @note If no key is pressed OpenCVs HighGUI returns -1.
 * 
 * @return Input character key
 */
char getUiInputKey (void);

/**
 * @brief A function to process the user interface input
 * 
 * This function processes the user interface input and drawing a
 * user interface.
 * 
 * @param image Image matrix for output image
 * @param key User input key
 */
void processUiInput (cv::Mat& image, char key);

/**
 * @brief A thread to process the user input from terminal
 * 
 * @note This function is stil in development!
 * 
 * This thread process the user input from a console.
 * 
 * @param arg Input argument
 */
void *userInput (void *arg);

//! @} user_interface

#endif // USER_INTERFACE_HPP
