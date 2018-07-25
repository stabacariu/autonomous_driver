/**
 * @file user_interface_mode.hpp
 * @author Sergiu-Petru Tabacariu
 * @date 1.5.2018
 */

#ifndef USER_INTERFACE_MODE_HPP
#define USER_INTERFACE_MODE_HPP

#include <opencv2/opencv.hpp>

//! @addtogroup user_interface
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

//! @} user_interface

#endif // USER_INTERFACE_MODE_HPP
