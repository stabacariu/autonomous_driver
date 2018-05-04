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
 * @brief A class for the configuration manager
 *
 * This class holds all configuration data. It synchronises access via
 * a mutex lock to be thread safe.
 */
class Configurator {
public:
    Configurator (const std::string file = "config/default.xml");
    ~Configurator () = default;
    
    /**
     * @brief Configurator instance as global singleton
     * 
     * This static function describes a singleton for global accessibility.
     * 
     * @param file Path to configuration file
     */
    static Configurator &instance (const std::string file = "config/default.xml");
    
    int getInt (const std::string key);
    int getDouble (const std::string key);
    std::string getString (const std::string key);
    cv::Mat getMat (const std::string key);
    
    /**
     * @brief A function to set configuration data
     * 
     * This function sets the configuration data.
     * It synchronises access via a mutex lock to be thread safe.
     * 
     * @param c configuration data
     */
    void setConfigData (Configurator c);
    
    /**
     * @brief A function to save a calibration configuration to a XML file
     * 
     * This function saves a calibration configuration to a XML file.
     * 
     * @param fs File storage
     * @param c Configuration data
     */
    void saveCalibConfig (cv::FileStorage& fs, Configurator c);
    
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
    void load (cv::FileStorage fs, Configurator& c);
    
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
    Configurator getConfigData (void);
    
    
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
    void loadDefault (cv::FileStorage fs, Configurator& c);
    
    /**
     * @brief A function to validate a configuration
     * 
     * This function validates a configuration.
     * 
     * @param c Configuration data
     * @return Valid data 
     */
    bool validateConfig (Configurator& c);
    
private:
    std::string defaultConfigFileName {"default.xml"}; //! Default config file name
    std::mutex lock; //!< Mutex lock for synchronized access
};

//! @} configuration

#endif
