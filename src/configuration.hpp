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
    cv::Size imageSize; //!< Image size
    cv::Size boardSize; //!< Number of chessboard squares
    double squareSize; //! Size of a chessboard square in mm
    
    int sampleCnt; //! Number of samples to use for calibration
    double aspectRatio; //! Aspect ratio of input image
    bool calibZeroTangentDist; //!< Assume zero tangential distortion
    bool calibFixPrincipalPoint; //!< Fix principal point at the center
    int calibFlags; //!< Calibration flags
    
    std::string outputFileName; //!< File name of config file
    
    bool showUndistorted; //!< Show undistorted image after calibration
    bool flipVertical; //1< Flip input image around the horizonal axis
    
    cv::VideoCapture inputCapture; //!<
    int cameraID; //!< Camera identification
    std::string input; //!< Input file
    std::vector<std::string> imageList; //!< Image list for calibration
    size_t imageListCnt; //!< Image list counter
    int inputDelay; //!< Video input delay
    bool validData; //!< Valid input flag
    
    bool fixK1; //!< Fix K1 distortion coefficient
    bool fixK2; //!< Fix K2 distortion coefficient
    bool fixK3; //!< Fix K3 distortion coefficient
    bool fixK4; //!< Fix K4 distortion coefficient
    bool fixK5; //!< Fix K5 distortion coefficient
    
    cv::Mat homography; //!< Homography for perspective transform
    cv::Mat transformation; //!< Transformation matrix for image position
    cv::Mat cameraMatrix; //!< Intrinsic camera matrix
    cv::Mat diffCoeffs; //!< Differential coeffitiens for undistortion

    float pixelPerMm; //!< Average mm per pixel
    
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
void setExtrinsics (cv::Mat homography);
void getExtrinsics (cv::Mat& homography);
void setIntrinsics (cv::Mat cameraMatrix, cv::Mat diffCoeffs);
void getIntrinsics (cv::Mat& cameraMatrix, cv::Mat& diffCoeffs);

void saveConfig(cv::FileStorage& fs, ConfigData c);
void loadConfig(cv::FileStorage fs, ConfigData& c);

void *configCalibIntrinsics(void *arg);
void *configCalibExtrinsics (void *arg);
void *configImagePosition (void *arg);
void *showChessBoard (void *arg);

#endif
