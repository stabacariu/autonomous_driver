/**
 * @file calibration_mode.hpp
 * @author Sergiu-Petru Tabacariu
 * @date 25.4.2018
 */

/**
 * @ingroup configuration_mode
 * @defgroup calibration_mode Calibration Mode
 * @brief A mode to calibrate the camera
 */

#ifndef CALIBRATION_MODE_HPP
#define CALIBRATION_MODE_HPP

#include <iostream>
#include <thread>
#include "system_mode.hpp"
#include "system_state.hpp"
#include "user_interface_state.hpp"
#include "image_data.hpp"
#include "user_interface.hpp"
#include "camera_image_acquisitor.hpp"

//! @addtogroup calibration_mode
//! @{

class IntrinsicsCalibrationMode : public SystemMode {
public:
    ~IntrinsicsCalibrationMode() = default;
    
    /**
     * @brief Start intrinsics calibration system mode
     * 
     * This function starts the intrinsic camera calibration mode.
     * 
     * @param s System state pointer
     */
    void run (SystemState* s) override;
    
    /**
     * @brief Stop intrinsics calibration system mode
     * 
     * This function stops the intrinsic camera calibration mode.
     */
    void quit (void) override;
    
    /**
     * @brief Stop mode modules
     * 
     * This function stops all mode modules.
     */
    void stopModules (void);

private:
    ImageData inputImage; //!< Input image captured by an image acquisitor
    ImageData outputImage; //!< Output image captured by an image acquisitor
    UserInterfaceState uiState; //!< User inderface user input data
    UserInterface ui; //!< User interface
    CameraImageAcquisitor camera; //!< Camera image acquisitor
};

class ExtrinsicsCalibrationMode : public SystemMode {
public:
    virtual ~ExtrinsicsCalibrationMode() = default;
    
    /**
     * @brief Start extrinsics calibration system mode
     * 
     * This function starts the extrinsic camera calibration mode.
     * 
     * @param s System state pointer
     */
    void run (SystemState* s) override;
    
    /**
     * @brief Stop extrinsics calibration system mode
     * 
     * This function stops the extrinsic camera calibration mode.
     */
    void quit (void) override;
    
    /**
     * @brief Stop mode modules
     * 
     * This function stops all mode modules.
     */
    void stopModules (void);

private:
    ImageData inputImage; //!< Input image captured by an image acquisitor
    ImageData outputImage; //!< Output image captured by an image acquisitor
    UserInterfaceState uiState; //!< User inderface user input data
    UserInterface ui; //!< User interface
    CameraImageAcquisitor camera; //!< Camera image acquisitor
};

class ImageAdjustmentMode : public SystemMode {
public:
    virtual ~ImageAdjustmentMode() = default;
    
    /**
     * @brief Start extrinsics calibration system mode
     * 
     * This function starts the extrinsic camera calibration mode.
     * 
     * @param s System state pointer
     */
    void run (SystemState* s) override;
    
    /**
     * @brief Stop extrinsics calibration system mode
     * 
     * This function stops the extrinsic camera calibration mode.
     */
    void quit (void) override;
    
    /**
     * @brief Stop mode modules
     * 
     * This function stops all mode modules.
     */
    void stopModules (void);

private:
    ImageData inputImage; //!< Input image captured by an image acquisitor
    ImageData outputImage; //!< Output image captured by an image acquisitor
    UserInterfaceState uiState; //!< User inderface user input data
    UserInterface ui; //!< User interface
    CameraImageAcquisitor camera; //!< Camera image acquisitor
};

//! @} calibration_mode

#endif // CALIBRATION_MODE_HPP

