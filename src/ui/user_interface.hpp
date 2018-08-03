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
#include <atomic>
#include <mutex>
#include "module.hpp"
#include "camera_image_acquisitor.hpp"
#include "image_data.hpp"
#include "user_interface_state.hpp"

//! @addtogroup user_interface
//! @{

/**
 * @brief User interface configuration class
 */
class UserInterfaceConfig {
public:
    ~UserInterfaceConfig() = default;
    
    bool load (cv::FileStorage fs);
    void save (cv::FileStorage fs);
    
public:
    std::string mainWindowName {"Autonomous Driver"}; //!< Main user interface window title
    cv::Size imageSize {640, 360}; //!< Image size of output image
    int menuWidth {160}; //!< Menu width
    double fps {30.}; //!< User interface frames per second
};

/**
 * @brief A user interface class
 */
class UserInterface : public Module {
public:
    ~UserInterface() = default;
    
    /**
     * @brief Run user interface thread
     * 
     * This function runs the user interface thread.
     * 
     * @param imageData Image data to show on user interface
     * @param uiState User interface input data
     */
    void run (ImageData& imageData, UserInterfaceState& uiState);
    
private:
    cv::Mat image;
    std::atomic_char inputKey {(char)(-1)};
    UserInterfaceConfig uiConfig;
    CameraConfig camConfig;
    std::mutex lock;
};

/**
 * @brief Get user input from console
 * 
 * This function gets the user input from the console with out blocking
 * wait
 * 
 * @return User input key
 */
char getConsoleInput (void);

/**
 * @brief Draw a message on the center of an image
 * 
 * This function draws a message on the center of an image.
 * 
 * @param image Image matrix
 * @param text Text string
 */
void drawMessage (cv::Mat& image, std::string text);

//! @} user_interface

#endif // USER_INTERFACE_HPP
