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

//! @addtogroup configuration
//! @{

/**
 * @brief A struct for the configuration data
 *
 * This struct holds all configuration data. It synchronises access via
 * a mutex lock to be thread safe.
 */
struct ConfigData {
public:
    
    /**
     * @brief A function to set configuration data
     * 
     * This function sets the configuration data.
     * It synchronises access via a mutex lock to be thread safe.
     * 
     * @param c configuration data
     */
    void setConfigData (ConfigData c);
    
    /**
     * @brief A function to save a calibration configuration to a XML file
     * 
     * This function saves a calibration configuration to a XML file.
     * 
     * @param fs File storage
     * @param c Configuration data
     */
    void saveCalibConfig (cv::FileStorage& fs, ConfigData c);
    
    /**
     * @brief A function to save a calibration configuration to a XML file
     * 
     * This function saves a calibration configuration to a XML file.
     * This is a overloading function to save file to default location
     * "../config/config.xml"
     */
    void saveCalibConfig (void);
    
    /**
     * @brief A function to load a configuration from a XML file
     * 
     * This function loads a calibration configuration from a XML file.
     * 
     * @param fs File storage
     * @param c Config data
     */
    void load (cv::FileStorage fs, ConfigData& c);
    
    /**
     * @brief A function to load a configuration from a XML file
     * 
     * This function loads a configuration from a XML file.
     * This is a overloading function to load file from default location
     * "../config/config.xml"
     */
    void load (void);
    
    /**
     * @brief A function to get configuration data
     * 
     * This function gets the configuration data.
     * It synchronises access via a mutex lock to be thread safe.
     * 
     * @return Configuration data
     */
    ConfigData getConfigData (void);
    
    
    /**
     * @brief A function to generate a default configuration
     * 
     * This function generates a default configuration.
     */
    void generateDefault (void);
    
    /**
     * @brief A function to load a default configuration from a XML file
     * 
     * This function loads a default configuration from a XML file.
     * 
     * @param fs File storage
     * @param c Configuration data
     */
    void loadDefault (cv::FileStorage fs, ConfigData& c);
    
    /**
     * @brief A function to validate a configuration
     * 
     * This function validates a configuration.
     * 
     * @param c Configuration data
     * @return Valid data 
     */
    bool validateConfig (ConfigData& c);
    
private:
    std::string defaultConfigFileName {"default.xml"}; //! Default config file name
    std::mutex lock; //!< Mutex lock for synchronized access
};

//! @} configuration

#endif
