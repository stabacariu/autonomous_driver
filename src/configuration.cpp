/**
 * @file configuration.cpp
 * @author Sergiu-Petru Tabacariu
 * @date 18.09.2017
 */

#include "configuration.hpp"

ConfigData config;

using namespace std;
using namespace cv;

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

void configDataInit (void)
{
    pthread_mutex_init(&config.lock, NULL);
}

void *configuration (void *arg)
{
    configDataInit();
    
    Mat inputImage, warpedImage;
    Mat homography;
    Size boardSize = Size(7, 5); // @todo Load size from config file
    
    
    while ((getModuleState() & MODULE_CONFIG_CALIB_EXTRINSICS) == MODULE_CONFIG_CALIB_EXTRINSICS) {
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
            setOutputImageData(warpedImage);
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
