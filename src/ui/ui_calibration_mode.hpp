/**
 * @file ui_calibration_mode.hpp
 * @author Sergiu-Petru Tabacariu
 * @date 1.5.2018
 */

#ifndef UI_CALIBRATION_MODE_HPP
#define UI_CALIBRATION_MODE_HPP

#include <opencv2/opencv.hpp>
#include "user_interface_mode.hpp"

//! @addtogroup user_interface
//! @{

class UIIntrinsicsCalibrationMode : public UserInterfaceMode {
public:
    UIIntrinsicsCalibrationMode() {};
    ~UIIntrinsicsCalibrationMode() = default;
    
    /**
     * @brief Draw intrinsics calibration user interface mode
     * 
     * This function draws the intrinsics calibration user interface mode.
     * 
     * @brief image Image matrix
     * @param selected Selected button
     */
    void draw (cv::Mat& image, char& selected) override;
};

class UIExtrinsicsCalibrationMode : public UserInterfaceMode {
public:
    UIExtrinsicsCalibrationMode() {};
    ~UIExtrinsicsCalibrationMode() = default;
    
    /**
     * @brief Draw extrinsics calibration user interface mode
     * 
     * This function draws the extrinsics calibration user interface mode.
     * 
     * @brief image Image matrix
     */
    void draw (cv::Mat& image, char& selected) override;
};

class UIImageAdjustmentMode : public UserInterfaceMode {
public:
    UIImageAdjustmentMode() {};
    ~UIImageAdjustmentMode() = default;
    
    /**
     * @brief Draw image position adjustment user interface mode
     * 
     * This function draws the image position adjustment user interface mode.
     * 
     * @brief image Image matrix
     */
    void draw (cv::Mat& image, char& selected) override;
};

//! @} user_interface

#endif // UI_CALIBRATION_MODE_HPP
