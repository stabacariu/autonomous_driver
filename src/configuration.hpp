/**
 * @file configuration.hpp
 * @author Sergiu-Petru Tabacariu
 * @date 18.09.2017
 */

#ifndef CONFIGURATION_HPP
#define CONFIGURATION_HPP

#include <iostream>
#include <opencv2/opencv.hpp>
#include <pthread.h>
#include "autonomous_driver.hpp"
#include "image_data.hpp"
#include "camera_calibration.hpp"

enum ConfigMode {
    CONFIG_MODE_NONE,
    CONFIG_MODE_MENU,
    CONFIG_MODE_CALIB_INTRINSICS,
    CONFIG_MODE_CALIB_EXTRINSICS,
    CONFIG_MODE_IMAGE_POSITION,
    CONFIG_MODE_VEHICLE_DATA
};

struct ConfigState {
     ConfigMode mode;
     pthread_mutex_t lock;
};

/**
 * @brief Configuration data structure
 * 
 * This structure holds all configuration data with a mutex lock.
 */
struct ConfigData {
    // Camera config
    int cameraID; //!< Camera identification
    cv::Size cameraImageSize; //!< Camera image size
    int cameraFPS; //!< Camera frames per second
    // Calibration config
    std::string calibrationTime; //!< Calibration time stamp
    cv::Size calibrationImageSize; //!< Calibration image size
    std::string calibrationPattern; //!< Calibration pattern
    cv::Size calibrationPatternDimension; //!< Calibration Pattern dimension
    double calibrationPatternSize; //! Size of a pattern element in mm
    int calibrationSampleCount; //! Number of samples to use for calibration
    // Calibration data
    bool calibIntrinsicDone; //! Calibration done flag
    cv::Mat cameraMatrix; //!< Intrinsic camera matrix
    cv::Mat diffCoeffs; //!< Differential coeffitiens for undistortion
    bool calibExtrinsicDone; //! Calibration done flag
    cv::Mat homography; //!< Homography for extrinsic calibration
    cv::Mat transformation; //!< Transformation matrix for image position
    float pixelPerMm; //!< Average mm per pixel
    
    bool validData; //!< Valid input flag
    
    std::string defaultConfigFileName; //! Default config file name
    
    pthread_mutex_t lock; //!< Lock exlusiv access
};

/**
 * @brief Function to initialize configuration.
 * 
 * This function initializes the configuration of the autonomous driver platform.
 * 
 * @param void
 * @return void
 */
void initConfig (void);

void setConfigState (ConfigMode mode);
ConfigMode getConfigState (void);

ConfigData getConfigData (void);
void setConfigData (ConfigData c);

int getCameraID (void);
cv::Size getImageSize (void);
int getFPS (void);
cv::Size getBoardSize (void);
double getSquareSize (void);
void setExtr (cv::Mat homography);
void getExtr (cv::Mat& homography);
void setIntr (cv::Mat cameraMatrix, cv::Mat diffCoeffs);
void getIntr (cv::Mat& cameraMatrix, cv::Mat& diffCoeffs);

void saveCalibConfig (cv::FileStorage& fs, ConfigData c);
void saveCalibConfig (void);
void loadConfig (cv::FileStorage fs, ConfigData& c);
void loadConfig (void);
void generateDefaultConfig (void);
void loadDefaultConfig (cv::FileStorage fs, ConfigData& c);
bool validateConfig (ConfigData& c);

void *configCalibIntr (void *arg);
void *configCalibExtr (void *arg);
void *configImagePos (void *arg);
void *showChessBoard (void *arg);

#endif
