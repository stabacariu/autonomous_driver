/**
 * @file ui_about_mode.hpp
 * @author Sergiu-Petru Tabacariu
 * @date 1.5.2018
 */

#ifndef UI_ABOUT_MODE_HPP
#define UI_ABOUT_MODE_HPP

#include <opencv2/opencv.hpp>
#include "user_interface_mode.hpp"

//! @addtogroup user_interface
//! @{

class UIAboutMode : public UserInterfaceMode {
public:
    UIAboutMode () {};
    ~UIAboutMode () = default;
    
    /**
     * @brief Draw about user interface mode
     * 
     * This function draws the about user interface mode.
     * 
     * @param image Image matrix
     * @param selected Selected button
     */
    void draw (cv::Mat& image, char& selected) override;
};

//! @} user_interface

#endif // UI_ABOUT_MODE_HPP
