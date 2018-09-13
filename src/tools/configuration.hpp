/**
 * @file configuration.hpp
 * @author Sergiu-Petru Tabacariu
 * @date 18.09.2017
 */

#ifndef CONFIGURATION_HPP
#define CONFIGURATION_HPP

#include <iostream>
#include <opencv2/opencv.hpp>
#include <mutex>
#include "camera_image_acquisitor.hpp"
#include "user_interface.hpp"
#include "traffic_sign_detection.hpp"
#include "obstacle_detection.hpp"

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
    Configurator (const std::string file = "config/default.xml") : fileName(file) {};
    ~Configurator () = default;
    
    /**
     * @brief Configurator instance as global singleton
     * 
     * This static function describes a singleton for global accessibility.
     * 
     * @param file Path to configuration file
     */
    static Configurator& instance (const std::string file = "config/default.xml");
    
    /**
     * @brief Save configuration
     * 
     * This function saves all configuration data.
     */
    void save (void);
    
    /**
     * @brief Load configuration
     * 
     * This function loads all configuration data.
     */
    void load (void);
    
    /**
     * @brief Set camera configuration
     * 
     * This function sets the camera configuration.
     * 
     * @param c Camera configuration data
     */
    void setCameraConfig (CameraConfig c);
    
    /**
     * @brief Get camera configuration
     * 
     * This function gets the camera configuration.
     * 
     * @return Camera configuration data
     */
    CameraConfig getCameraConfig (void);
    
    /**
     * @brief Save camera configuration to XML-file
     * 
     * This function saves the camera configuration data to a XML-file.
     */
    void saveCameraConfig (void);
    
    /**
     * @brief Load camera configuration from XML-file
     * 
     * This function loads the camera conrfiguration data from a XML-file.
     */
    void loadCameraConfig (void);
    
    void setCameraCalibrationConfig (CameraCalibrationConfig c);
    CameraCalibrationConfig getCameraCalibrationConfig (void);
    
    void setUserInterfaceConfig (UserInterfaceConfig c);
    UserInterfaceConfig getUserInterfaceConfig (void);
    
    void setTrafficSignDetectionConfig (TrafficSignDetectionConfig c);
    TrafficSignDetectionConfig getTrafficSignDetectionConfig (void);
    
    void setObstacleDetectionConfig (ObstacleDetectionConfig c);
    ObstacleDetectionConfig getObstacleDetectionConfig (void);
    
private:
    std::string fileName {"config/default.xml"}; //!< Default config file name
    CameraConfig camConfig; //!< Camera configuration data
    CameraCalibrationConfig camCalibConfig; //!< Camera calibration configuration data
    UserInterfaceConfig uiConfig; //!< User interface configuration data
    TrafficSignDetectionConfig trafficSignDetConfig; //!< Traffic sign detection configuration data
    ObstacleDetectionConfig obstacleDetConfig; //!< Obstacle detection configuration data
    std::mutex lock; //!< Mutex lock for synchronized access
};

//! @} configuration

#endif
