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
#include <pthread.h>
#include "autonomous_driver.hpp"
#include "image_data.hpp"
#include "camera_calibration.hpp"

//! @addtogroup configuration
//! @{

/**
 * @brief An enum for the configuration mode
 * 
 * This enum defines all configuration modes
 */
enum ConfigMode {
    CONFIG_MODE_NONE,
    CONFIG_MODE_MENU,
    CONFIG_MODE_CALIB_INTRINSICS,
    CONFIG_MODE_CALIB_EXTRINSICS,
    CONFIG_MODE_IMAGE_POSITION,
    CONFIG_MODE_VEHICLE_DATA
};

/**
 * @brief A struct for the configuration state
 * 
 * This struct describes the configuration state by its mode.
 * It synchronises access via a mutex lock to be thread safe.
 */
struct ConfigState {
     ConfigMode mode;
     pthread_mutex_t lock;
};

/**
 * @brief A struct for the configuration data
 *
 * This struct holds all configuration data. It synchronises access via
 * a mutex lock to be thread safe.
 */
struct ConfigData {
    // Camera config
    int cameraID; //!< Camera identification
    cv::Size cameraImageSize; //!< Camera image size
    double cameraFPS; //!< Camera frames per second
    // Calibration config
    std::string calibTime; //!< Calibration time stamp
    cv::Size calibImageSize; //!< Calibration image size
    std::string calibPattern; //!< Calibration pattern
    cv::Size calibPatternSize; //!< Calibration Pattern size
    double calibPatternMm; //! Size of a pattern element in mm
    int calibSampleCount; //! Number of samples to use for calibration
    // Calibration data
    bool calibIntrDone; //! Calibration done flag
    cv::Mat cameraMatrix; //!< Intrinsic camera matrix
    cv::Mat distCoeffs; //!< Differential coeffitiens for undistortion
    bool calibExtrDone; //! Calibration done flag
    cv::Mat homography; //!< Homography for extrinsic calibration
    cv::Mat transformation; //!< Transformation matrix for image position
    float pixelPerMm; //!< Average mm per pixel
    
    bool validData; //!< Valid input flag
    
    std::string defaultConfigFileName; //! Default config file name
    
    pthread_mutex_t lock; //!< Mutex lock for synchronized access
};

/**
 * @brief A function to initialize the configuration
 *
 * This function initializes the configuration of the autonomous driver platform.
 */
void initConfig (void);

/**
 * @brief A function to set the configuration state
 * 
 * This function sets the configuration state.
 * It synchronises access via a mutex lock to be thread safe.
 * 
 * @param mode configuration mode
 */
void setConfigState (ConfigMode mode);

/**
 * @brief A function to get the configuration state
 * 
 * This function gets the configuration state.
 * It synchronises access via a mutex lock to be thread safe.
 * 
 * @return Configuration mode
 */
ConfigMode getConfigState (void);

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
 * @brief A function to set configuration data
 * 
 * This function sets the configuration data.
 * It synchronises access via a mutex lock to be thread safe.
 * 
 * @param c configuration data
 */
void setConfigData (ConfigData c);

/**
 * @brief A function to get the camera ID
 * 
 * This function gets the camera ID of the used camera.
 * 
 * @return Camera ID
 */
int getCameraID (void);

/**
 * @brief A function to get image size
 * 
 * This function gets the configurated capturing image size.
 * 
 * @return Size of image
 */
cv::Size getImageSize (void);

/**
 * @brief A function to get frames per second
 * 
 * This function gets the configurated frames per second.
 * 
 * @return Frames per second
 */
double getFPS (void);

/**
 * @brief A function to get the calibration pattern size
 * 
 * This function gets the configurated calibration pattern size.
 * 
 * @return Size pattern size
 */
cv::Size getPatternSize (void);

/**
 * @brief A function to get the calibration pattern element size in mm
 * 
 * This function gets the configurated calibration pattern element size in mm.
 * 
 * @return Pattern element size in mm
 */
double getPatternMm (void);

/**
 * @brief A function to set the extrinsic camera parameters
 * 
 * This function sets the extrinsic camera parameters.
 * It is used to set a homography matrix for a perspective transformation.
 * 
 * @param homography Homography for perspective transformation
 */
void setExtr (cv::Mat homography);

/**
 * @brief A function to get the extrinsic camera parameters
 * 
 * This function gets the extrinsic camera parameters.
 * It is used to get a homography matrix for a perspective transformation.
 * 
 * @param homography Homography for perspective transformation
 */
void getExtr (cv::Mat& homography);

/**
 * @brief A function to set the intrinsic camera parameters
 * 
 * This function sets the intrinsic camera parameters.
 * It is used to set a camera matrix and distortion coefficients.
 * 
 * @param cameraMatrix Camera matrix
 * @param distCoeffs Distortion coefficients
 */
void setIntr (cv::Mat cameraMatrix, cv::Mat distCoeffs);

/**
 * @brief A function to get the intrinsic camera parameters
 * 
 * This function gets the intrinsic camera parameters.
 * It is used to get a camera matrix and distortion coefficients.
 * 
 * @param cameraMatrix Camera matrix
 * @param distCoeffs Distortion coefficients
 */
void getIntr (cv::Mat& cameraMatrix, cv::Mat& distCoeffs);

/**
 * @brief A function to set pixel per mm
 * 
 * This function sets how many pixel are in a mm
 * 
 * @param pxPerMm Pixel per mm
 */
void setPxPerMm (float pxPerMm);

/**
 * @brief A function to get pixel per mm
 * 
 * This function gets how many pixel are in a mm
 * 
 * @return float pixel per mm
 */
float getPxPerMm (void);

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
void loadConfig (cv::FileStorage fs, ConfigData& c);

/**
 * @brief A function to load a configuration from a XML file
 * 
 * This function loads a configuration from a XML file.
 * This is a overloading function to load file from default location
 * "../config/config.xml"
 */
void loadConfig (void);

/**
 * @brief A function to generate a default configuration
 * 
 * This function generates a default configuration.
 */
void generateDefaultConfig (void);

/**
 * @brief A function to load a default configuration from a XML file
 * 
 * This function loads a default configuration from a XML file.
 * 
 * @param fs File storage
 * @param c Configuration data
 */
void loadDefaultConfig (cv::FileStorage fs, ConfigData& c);

/**
 * @brief A function to validate a configuration
 * 
 * This function validates a configuration.
 * 
 * @param c Configuration data
 * @return Valid data 
 */
bool validateConfig (ConfigData& c);

/**
 * @brief A thread to calibrate intrinsic camera parameters
 * 
 * This thread calibrates intrinsic camera paremeters
 */
void *configCalibIntr (void *arg);

/**
 * @brief A thread to calibrate extrinsic camera parameters
 * 
 * This thread calibrates extrinsic camera paremeters
 * 
 * @param arg Input argument
 */
void *configCalibExtr (void *arg);

/**
 * @brief A thread to change image position
 * 
 * This thread changes the image position in frame
 * 
 * @param arg Input argument
 */
void *configImagePos (void *arg);

/**
 * @brief A thread to show a detected chessboard pattern
 * 
 * This thread searches for a chessboard pattern in a captured image,
 * and draws the detected corners on an output image.
 * 
 * @param arg Input argument
 */
void *showChessBoard (void *arg);

//! @} configuration

#endif
