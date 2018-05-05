/**
 * @file configuration.hpp
 * @author Sergiu-Petru Tabacariu
 * @date 18.09.2017
 */

/**
 * @defgroup configuration Configuration
 * @{
 * @}
 */

#ifndef CONFIGURATION_HPP
#define CONFIGURATION_HPP

#include <iostream>
#include <opencv2/opencv.hpp>
#include <mutex>
#include "camera_image_acquisitor.hpp"

//! @addtogroup configuration
//! @{

/**
 * @brief A class for the configuration manager
 *
 * This class holds all configuration data. It synchronises access via
 * a mutex lock to be thread safe.
 */
class Configurator {
public:
    Configurator (const std::string file = "../config/default.xml") : fileName(file) {};
    ~Configurator () = default;
    
    /**
     * @brief Configurator instance as global singleton
     * 
     * This static function describes a singleton for global accessibility.
     * 
     * @param file Path to configuration file
     */
    static Configurator& instance (const std::string file = "../config/default.xml");
    
    void setCameraConfig (CameraConfig c);
    CameraConfig getCameraConfig (void);
    void saveCameraConfig (void);
    void loadCameraConfig (void);
    
    void setCameraCalibrationConfig (CameraCalibrationConfig c);
    CameraCalibrationConfig getCameraCalibrationConfig (void);
    void saveCameraCalibrationConfig (void);
    void loadCameraCalibrationConfig (void);
    
public:
    std::string fileName; //! Default config file name
    CameraConfig cameraData;
    CameraCalibrationConfig camCalibConfig;
    
    std::mutex lock; //!< Mutex lock for synchronized access
};

//! @} configuration

#endif
