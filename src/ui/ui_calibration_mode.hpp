/**
 * @file ui_calibration_mode.hpp
 * @author Sergiu-Petru Tabacariu
 * @date 1.5.2018
 */

#ifndef UI_CALIBRATION_MODE_HPP
#define UI_CALIBRATION_MODE_HPP

#include <opencv2/opencv.hpp>
#include "user_interface_mode.hpp"

//! @addtogroup user_interface_mode
//! @{

/**
 * @brief A user interface for the Intrinsics Calibration Mode
 * 
 * This user interface shows intrinsics calibration.
 */
class UIIntrinsicsCalibrationMode : public UserInterfaceMode {
public:
    UIIntrinsicsCalibrationMode() {};
    ~UIIntrinsicsCalibrationMode() = default;
    
    /**
     * @brief Draw intrinsics calibration user interface mode
     * 
     * This function draws the intrinsics calibration user interface mode.
     * 
     * @param image Image matrix
     * @param selected Selected button
     */
    void draw (cv::Mat& image, char& selected) override;
};

/**
 * @brief A user interface for the Extrinsics Calibration Mode
 * 
 * This user interface shows extrinsics calibration.
 */
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

/**
 * @brief A user interface for the Image Adjustment Mode
 * 
 * This user interface shows image adjustment mode.
 */
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

//! @} user_interface_mode

#endif // UI_CALIBRATION_MODE_HPP
