/**
 * @file ui_error_mode.hpp
 * @author Sergiu-Petru Tabacariu
 * @date 1.5.2018
 */

#ifndef UI_ERROR_MODE_HPP
#define UI_ERROR_MODE_HPP

#include <opencv2/opencv.hpp>
#include "user_interface_mode.hpp"

//! @addtogroup user_interface
//! @{

class UIErrorMode : public UserInterfaceMode {
public:
    UIErrorMode() {};
    ~UIErrorMode() = default;
    
    /**
     * @brief Draw error user interface mode
     * 
     * This function draws the error user interface mode.
     * 
     * @brief image Image matrix
     * @param selected Selected button
     */
    void draw (cv::Mat& image, char& selected) override;
private:
    std::string message {"Error found. Closing system safely."};
};

//! @} user_interface

#endif // UI_ERROR_MODE_HPP
