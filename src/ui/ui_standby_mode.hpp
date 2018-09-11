/**
 * @file ui_standby_mode.hpp
 * @author Sergiu-Petru Tabacariu
 * @date 1.5.2018
 */

#ifndef UI_STANDBY_MODE_HPP
#define UI_STANDBY_MODE_HPP

#include <opencv2/opencv.hpp>
#include "user_interface_mode.hpp"

//! @addtogroup user_interface_mode
//! @{

/**
 * @brief A user interface for the Standby Mode
 * 
 * This user interface shows standby mode. It shows the actual captured
 * camera image and a system navigation menu.
 */
class UIStandbyMode : public UserInterfaceMode {
public:
    UIStandbyMode () {};
    ~UIStandbyMode () = default;
    /**
     * @brief Draw standby user interface mode
     * 
     * This function draws the standby user interface mode.
     * 
     * @param image Image matrix
     * @param selected Selected button
     */
    void draw (cv::Mat& image, char& selected) override;
};

//! @} user_interface_mode

#endif // UI_STANDBY_MODE_HPP
