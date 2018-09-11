/**
 * @file user_interface_mode.hpp
 * @author Sergiu-Petru Tabacariu
 * @date 1.5.2018
 */

/**
 * @ingroup user_interface_state
 * @defgroup user_interface_mode User Interface Mode
 * @brief User Interface Modes to control the system states
 */

#ifndef USER_INTERFACE_MODE_HPP
#define USER_INTERFACE_MODE_HPP

#include <opencv2/opencv.hpp>

//! @addtogroup user_interface_mode
//! @{

class UserInterfaceMode {
public:
    virtual ~UserInterfaceMode () = default;
    
    /**
     * @brief Draw user interface mode
     * 
     * This function draws the user interface mode.
     * 
     * @param image Image matrix
     * @param selected Pressed button
     */
    virtual void draw (cv::Mat& image, char& selected) = 0;
};

//! @} user_interface_mode

#endif // USER_INTERFACE_MODE_HPP
