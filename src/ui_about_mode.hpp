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

class UIAboutMode : UserInterfaceMode {
public:
    UIAboutMode () {};
    ~UIAboutMode () = default;
    
    void draw (cv::Mat& image) override;
    
private:
    void drawAboutText (cv::Mat& image);
    void getAboutMenuList (std::vector<std::string>& menuList);
    void getAboutTextList (std::vector<std::string>& textList);
};

//! @} user_interface

#endif // UI_ABOUT_MODE_HPP
