/**
 * @file configuration.cpp
 * @author Sergiu-Petru Tabacariu
 * @date 18.09.2017
 */

#include "configuration.hpp"

ConfigData config;
ConfigState configState;

using namespace std;
using namespace cv;

void initConfig (void)
{
    // TODO: Load config from file 
    pthread_mutex_init(&config.lock, NULL);
    configState.mode = CONFIG_MODE_NONE;
    pthread_mutex_init(&configState.lock, NULL);
}

void setIntrinsics (Mat intrinsics, Mat diffCoeffs)
{
    if (pthread_mutex_lock(&config.lock)) {
        cerr << "ERROR: Couldn't lock config mutex!" << endl;
    }
    
    config.intrinsics = intrinsics;
    config.diffCoeffs = diffCoeffs;
    
    if (pthread_mutex_unlock(&config.lock)) {
        cerr << "ERROR: Couldn't unlock config mutex!" << endl;
    }
}

void getIntrinsics (Mat& intrinsics, Mat& diffCoeffs)
{
    if (pthread_mutex_lock(&config.lock)) {
        cerr << "ERROR: Couldn't lock config mutex!" << endl;
    }
    
    intrinsics = config.intrinsics;
    diffCoeffs = config.diffCoeffs;
    
    if (pthread_mutex_unlock(&config.lock)) {
        cerr << "ERROR: Couldn't unlock config mutex!" << endl;
    }
}

void setHomography (Mat homography)
{
    if (pthread_mutex_lock(&config.lock)) {
        cerr << "ERROR: Couldn't lock config mutex!" << endl;
    }
    
    config.homography = homography;
    
    if (pthread_mutex_unlock(&config.lock)) {
        cerr << "ERROR: Couldn't unlock config mutex!" << endl;
    }
}

void getHomography (Mat& homography)
{
    if (pthread_mutex_lock(&config.lock)) {
        cerr << "ERROR: Couldn't lock config mutex!" << endl;
    }
    
    homography = config.homography;
    
    if (pthread_mutex_unlock(&config.lock)) {
        cerr << "ERROR: Couldn't unlock config mutex!" << endl;
    }
}

void setConfigState (ConfigMode mode)
{
    if (pthread_mutex_lock(&configState.lock)) {
        cerr << "ERROR: Couldn't lock config mutex!" << endl;
    }
    
    configState.mode = mode;
    
    if (pthread_mutex_unlock(&configState.lock)) {
        cerr << "ERROR: Couldn't unlock config mutex!" << endl;
    }
}

ConfigMode getConfigState (void)
{
    ConfigMode mode;
    
    if (pthread_mutex_lock(&configState.lock)) {
        cerr << "ERROR: Couldn't lock config mutex!" << endl;
    }
    
    mode = configState.mode;
    
    if (pthread_mutex_unlock(&configState.lock)) {
        cerr << "ERROR: Couldn't unlock config mutex!" << endl;
    }
    
    return mode;
}

void *configCalibExtrinsics (void *arg)
{
    Mat inputImage, warpedImage;
    Mat homography;
    Size boardSize = Size(7, 5); /// @todo Load size from config file
    
    
    while (getConfigState() == CONFIG_MODE_CALIB_EXTRINSICS) {
        getInputImageData(inputImage);
        if (!inputImage.empty()) {
            calibrateExtrinsics(inputImage, homography, boardSize, 30.0);
            if (!homography.empty()) {
                setHomography(homography);
            }
            else {
                cout << "Homography couldn't be aqureid!" << endl;
            }
        }
        if (!homography.empty()) {
            inversePerspectiveTransform(inputImage, warpedImage, homography);
            line(warpedImage, Point(warpedImage.cols/2, 0), Point(warpedImage.cols/2, warpedImage.rows), Scalar(0, 0, 255), 1);
            line(warpedImage, Point(0, warpedImage.rows/2), Point(warpedImage.cols, warpedImage.rows/2), Scalar(0, 0, 255), 1);
            setOutputImageData(warpedImage);
        }
    }
}

void *configCalibIntrinsics(void *arg)
{
    Mat inputImage, undistorted;
    Mat intrinsics, diffCoeffs;
    Size boardSize = Size(7, 5); // @todo Load size from config file
    
    
    while (getConfigState() == CONFIG_MODE_CALIB_INTRINSICS) {
        getInputImageData(inputImage);
        if (!inputImage.empty()) {
            calibrateIntrinsics(inputImage, intrinsics, diffCoeffs, boardSize, 30.0, 50);
            if (!intrinsics.empty() && !diffCoeffs.empty()) {
                setIntrinsics(intrinsics, diffCoeffs);
            }
            else {
                cout << "Camera not calibrated!" << endl;
            }
        }
        if (!intrinsics.empty() && !diffCoeffs.empty()) {
            undistort(inputImage, undistorted, intrinsics, diffCoeffs);
            line(undistorted, Point(undistorted.cols/2, 0), Point(undistorted.cols/2, undistorted.rows), Scalar(0, 0, 255), 1);
            line(undistorted, Point(0, undistorted.rows/2), Point(undistorted.cols, undistorted.rows/2), Scalar(0, 0, 255), 1);
            setOutputImageData(undistorted);
        }
    }
}

void *configImagePosition (void *arg)
{
    Mat inputImage;
    while (getConfigState() == CONFIG_MODE_IMAGE_POSITION) {
        getInputImageData(inputImage);
        if (!inputImage.empty()) {
            setOutputImageData(inputImage);
        }
    }
}

void *showChessBoard (void *arg)
{
    Size boardSize = Size(7, 5);
    
    while ((getModuleState() & MODULE_SHOW_CHESSBOARD) == MODULE_SHOW_CHESSBOARD) {
        Mat image;
        getInputImageData(image);
        if (!image.empty()) {
            showChessBoardCorners(image, boardSize);
            setOutputImageData(image);
        }
    }
}
