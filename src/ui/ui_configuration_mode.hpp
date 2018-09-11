/**
 * @file ui_configuration_mode.hpp
 * @author Sergiu-Petru Tabacariu
 * @date 1.5.2018
 */

#ifndef UI_CONFIGURATION_MODE_HPP
#define UI_CONFIGURATION_MODE_HPP

#include <opencv2/opencv.hpp>
#include "user_interface_mode.hpp"

//! @addtogroup user_interface_mode
//! @{

/**
 * @brief A user interface for the Configuration Mode
 * 
 * This user interface shows configuration mode.
 */
class UIConfigurationMode : public UserInterfaceMode {
public:
    UIConfigurationMode() {};
    ~UIConfigurationMode() = default;
    
    /**
     * @brief Draw configuration user interface mode
     * 
     * This function draws the configuration user interface mode.
     * 
     * @param image Image matrix
     * @param selected Selected button
     */
    void draw (cv::Mat& image, char& selected) override;
};

//! @} user_interface_mode

#endif // UI_CONFIGURATION_MODE_HPP
