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
    
    Mat inputImage;
    Mat homography;
    Size boardSize = Size(7, 5); // @todo Load size from config file
    
    while (inputImage.empty()) {
        getInputImageData(inputImage);
    }
    
    calibrateExtrinsics(inputImage, homography, boardSize, 30.0);
    
    if (!homography.empty()) {
        setHomography(homography);
    }
    else {
        cout << "Homography couldn't be aqureid!" << endl;
    }
}

void *showChessBoard (void *arg)
{
    Size boardSize = Size(7, 5);
    
    while ((getModuleState() & MODULE_SHOW_CHESSBOARD) == MODULE_SHOW_CHESSBOARD) {
        Mat inputImage, outputImage;
        getInputImageData(inputImage);
        if (!inputImage.empty()) {
            showChessBoardCorners(inputImage, outputImage, boardSize);
            setOutputImageData(outputImage);
        }
    }
}