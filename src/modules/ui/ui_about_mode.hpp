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
     */
    void draw (cv::Mat& image) override;
    
    /**
     * @brief Draw about user interface mode text
     * 
     * This function draws the about user interface mode text.
     * 
     * @param image Image matrix
     */
    void drawText (cv::Mat& image);
    
private:
    void getMenuList (std::vector<std::string>& menuList);
    void getTextList (std::vector<std::string>& textList);
};

//! @} user_interface

#endif // UI_ABOUT_MODE_HPP
