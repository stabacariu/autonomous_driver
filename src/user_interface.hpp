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
#include <mutex>
#include "system_state.hpp"
#include "image_data.hpp"
#include "user_interface_data.hpp"
//~ #include "configuration.hpp"
#include "user_interface_menus.hpp"

//! @addtogroup user_interface
//! @{

/**
 * @brief A user interface class
 */
class UserInterface {
public:
    ~UserInterface() = default;
    
    /**
     * @brief Run user interface thread
     * 
     * This function runs the user interface thread.
     * 
     * @param imageData Image data to show on user interface
     * @param uiData User interface input data
     */
    void start (ImageData& imageData, UserInterfaceData& uiData);
    
    /**
     * @brief Quit user interface thread
     * 
     * This function quits the user interface thread. It does that by
     * by setting a flag.
     */
    void stop (void);
    
    /**
     * @brief Check if user interface thread is running
     * 
     * This function checks if the user interface thread is running.
     * 
     * @return True if user interface is running, else false
     */
    bool isRunning (void);
    
    /**
     * @brief Get user input from console thread
     * 
     * This function gets the user input from the console in an detached
     * thread.
     * 
     * @param uiData User interface input data
     */
    void consoleInput (UserInterfaceData& uiData);
    
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
     * @brief Set user keyboard input
     * 
     * This function sets the user keyboard input.
     * 
     * @param c Input key
     */
    void setUserInput(char c);
    
    /**
     * @brief Get user keyboard input
     * 
     * This function gets the user keyboard input.
     * 
     * @return Input key
     */
    char getUserInput(void);
    
private:
    bool running {false};
    cv::Mat image;
    //~ UserInterfaceState state;
    char guiInputKey {(char)(-1)};
    char consoleInputKey {(char)(-1)};
    std::mutex lock;
};

//! @} user_interface

#endif // USER_INTERFACE_HPP
