/**
 * @file ui_configuration_mode.hpp
 * @author Sergiu-Petru Tabacariu
 * @date 1.5.2018
 */

#ifndef UI_CONFIGURATION_MODE_HPP
#define UI_CONFIGURATION_MODE_HPP

#include <opencv2/opencv.hpp>
#include "user_interface_mode.hpp"

//! @addtogroup user_interface
//! @{

class UIConfigurationMode : public UserInterfaceMode {
public:
    UIConfigurationMode() {};
    ~UIConfigurationMode() = default;
    
    void draw (cv::Mat& image) override;
    
private:
    void getConfigMenuList (std::vector<std::string>& menuList);
    void getConfigModeList (std::vector<std::string>& menuList);
};

//! @} user_interface

#endif // UI_CONFIGURATION_MODE_HPP
