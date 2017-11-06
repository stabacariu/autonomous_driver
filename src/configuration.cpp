/**
 * @file configuration.cpp
 * @author Sergiu-Petru Tabacariu
 * @date 18.09.2017
 */

#include "configuration.hpp"

ConfigData config;
ConfigState configState;

void initConfig (void)
{
    //! @todo Load config from file 
    pthread_mutex_init(&config.lock, NULL);
    configState.mode = CONFIG_MODE_NONE;
    pthread_mutex_init(&configState.lock, NULL);
    
    ConfigData c;
    cv::FileStorage fs("../config/config.xml", cv::FileStorage::READ);
    if (!fs.isOpened()) {
        std::cerr << "Couldn't open config file. Generate default config file..." << std::endl;
        
        //! @todo load default config
        c.imageSize = cv::Size(640, 480);
        c.boardSize = cv::Size(7, 5);
        c.squareSize = 30.;
        c.cameraID = 0;
        c.homography = cv::Mat::eye(3, 3, CV_64F);
        c.cameraMatrix = cv::Mat::eye(3, 3, CV_64F);
        c.diffCoeffs = cv::Mat::zeros(8, 1, CV_64F);
        c.pixelPerMm = 0;
        setConfigData(c);
    }
    else {
        loadConfig(fs, c);
        //! @todo Validate data
        setConfigData(c);
    }
    fs.release();
}

void setIntrinsics (cv::Mat cameraMatrix, cv::Mat diffCoeffs)
{
    if (pthread_mutex_lock(&config.lock)) {
        std::cerr << "ERROR: Couldn't lock config mutex!" << std::endl;
    }
    
    config.cameraMatrix = cameraMatrix;
    config.diffCoeffs = diffCoeffs;
    
    if (pthread_mutex_unlock(&config.lock)) {
        std::cerr << "ERROR: Couldn't unlock config mutex!" << std::endl;
    }
}

void getIntrinsics (cv::Mat& cameraMatrix, cv::Mat& diffCoeffs)
{
    if (pthread_mutex_lock(&config.lock)) {
        std::cerr << "ERROR: Couldn't lock config mutex!" << std::endl;
    }
    
    cameraMatrix = config.cameraMatrix;
    diffCoeffs = config.diffCoeffs;
    
    if (pthread_mutex_unlock(&config.lock)) {
        std::cerr << "ERROR: Couldn't unlock config mutex!" << std::endl;
    }
}

void setExtrinsics (cv::Mat homography)
{
    if (pthread_mutex_lock(&config.lock)) {
        std::cerr << "ERROR: Couldn't lock config mutex!" << std::endl;
    }
    
    config.homography = homography;
    
    if (pthread_mutex_unlock(&config.lock)) {
        std::cerr << "ERROR: Couldn't unlock config mutex!" << std::endl;
    }
}

void getExtrinsics (cv::Mat& homography)
{
    if (pthread_mutex_lock(&config.lock)) {
        std::cerr << "ERROR: Couldn't lock config mutex!" << std::endl;
    }
    
    homography = config.homography;
    
    if (pthread_mutex_unlock(&config.lock)) {
        std::cerr << "ERROR: Couldn't unlock config mutex!" << std::endl;
    }
}

ConfigData getConfigData (void)
{
    ConfigData c;
    
    if (pthread_mutex_lock(&config.lock)) {
        std::cerr << "ERROR: Couldn't lock config mutex!" << std::endl;
    }
    
    c.imageSize = config.imageSize;
    c.boardSize = config.boardSize;
    c.squareSize = config.squareSize;
    c.cameraID = config.cameraID;
    c.homography = config.homography;
    c.cameraMatrix = config.cameraMatrix;
    c.diffCoeffs = config.diffCoeffs;
    c.pixelPerMm = config.pixelPerMm;
    
    if (pthread_mutex_unlock(&config.lock)) {
        std::cerr << "ERROR: Couldn't unlock config mutex!" << std::endl;
    }
    
    return c;
}

void setConfigData (ConfigData c)
{
    if (pthread_mutex_lock(&config.lock)) {
        std::cerr << "ERROR: Couldn't lock config mutex!" << std::endl;
    }
    
    config.imageSize = c.imageSize;
    config.boardSize = c.boardSize;
    config.squareSize = c.squareSize;
    config.cameraID = c.cameraID;
    config.homography = c.homography;
    config.cameraMatrix = c.cameraMatrix;
    config.diffCoeffs = c.diffCoeffs;
    config.pixelPerMm = c.pixelPerMm;
    
    if (pthread_mutex_unlock(&config.lock)) {
        std::cerr << "ERROR: Couldn't unlock config mutex!" << std::endl;
    }
}

void setConfigState (ConfigMode mode)
{
    if (pthread_mutex_lock(&configState.lock)) {
        std::cerr << "ERROR: Couldn't lock config mutex!" << std::endl;
    }
    
    configState.mode = mode;
    
    if (pthread_mutex_unlock(&configState.lock)) {
        std::cerr << "ERROR: Couldn't unlock config mutex!" << std::endl;
    }
}

ConfigMode getConfigState (void)
{
    ConfigMode mode;
    
    if (pthread_mutex_lock(&configState.lock)) {
        std::cerr << "ERROR: Couldn't lock config mutex!" << std::endl;
    }
    
    mode = configState.mode;
    
    if (pthread_mutex_unlock(&configState.lock)) {
        std::cerr << "ERROR: Couldn't unlock config mutex!" << std::endl;
    }
    
    return mode;
}

void saveConfig (cv::FileStorage& fs, ConfigData c)
{
    fs << "imageSize_width" << c.imageSize.width
    << "imageSize_height" << c.imageSize.height
    << "boardSize_width" << c.boardSize.width
    << "boardSize_height" << c.boardSize.height
    << "squareSize" << c.squareSize
    << "cameraID" << c.cameraID
    << "homography" << c.homography
    << "cameraMatrix" << c.cameraMatrix
    << "diffCoeffs" << c.diffCoeffs
    << "pixelPerMm" << c.pixelPerMm;
}

void loadConfig (cv::FileStorage fs, ConfigData& c)
{
    fs["imageSize_width"] >> c.imageSize.width;
    fs["imageSize_height"] >> c.imageSize.height;
    fs["boardSize_width"] >> c.boardSize.width;
    fs["boardSize_height"] >> c.boardSize.height;
    fs["squareSize"] >> c.squareSize;
    fs["cameraID"] >> c.cameraID;
    fs["homography"] >> c.homography;
    fs["cameraMatrix"] >> c.cameraMatrix;
    fs["diffCoeffs"] >> c.diffCoeffs;
    fs["pixelPerMm"] >> c.pixelPerMm;
}

void *configCalibIntrinsics(void *arg)
{
    std::cout << "THREAD: cameraMatrix calibarion started." << std::endl;
    
    cv::Mat inputImage, undistorted;
    cv::Mat cameraMatrix, diffCoeffs;
    cv::Size boardSize = cv::Size(7, 5); //!< @todo Load cv::Size from config file
    
    while ((getModuleState() & MODULE_CONFIG_CALIB_INTRINSICS) == MODULE_CONFIG_CALIB_INTRINSICS) {
        getInputImageData(inputImage);
        if (!inputImage.empty()) {
            calibrateIntrinsics(inputImage, cameraMatrix, diffCoeffs, boardSize, 30.0, 50);
            if (!cameraMatrix.empty() && !diffCoeffs.empty()) {
                setIntrinsics(cameraMatrix, diffCoeffs);
            } 
            else {
                std::cout << "Camera not calibrated!" << std::endl;
            }
        }
        if (!cameraMatrix.empty() && !diffCoeffs.empty()) {
            undistort(inputImage, undistorted, cameraMatrix, diffCoeffs);
            cv::line(undistorted, cv::Point(undistorted.cols/2, 0), cv::Point(undistorted.cols/2, undistorted.rows), cv::Scalar(0, 0, 255), 1);
            cv::line(undistorted, cv::Point(0, undistorted.rows/2), cv::Point(undistorted.cols, undistorted.rows/2), cv::Scalar(0, 0, 255), 1);
            setOutputImageData(undistorted);
        }
    }
    
    setConfigState(CONFIG_MODE_NONE);
    
    std::cout << "THREAD: cameraMatrix calibarion ended." << std::endl;
}

void *configCalibExtrinsics (void *arg)
{
    std::cout << "THREAD: Extrinsics calibarion started." << std::endl;
    
    cv::Mat inputImage, warpedImage;
    cv::Mat homography;
    cv::Size boardSize = cv::Size(7, 5); //!< @todo Load cv::Size from config file
    
    while ((getModuleState() & MODULE_CONFIG_CALIB_EXTRINSICS) == MODULE_CONFIG_CALIB_EXTRINSICS) {
        getInputImageData(inputImage);
        if (!inputImage.empty()) {
            calibrateExtrinsics(inputImage, homography, boardSize, 30.0);
        }
        if (!homography.empty()) {
            inversePerspectiveTransform(inputImage, warpedImage, homography);
            cv::line(warpedImage, cv::Point(warpedImage.cols/2, 0), cv::Point(warpedImage.cols/2, warpedImage.rows), cv::Scalar(0, 0, 255), 1);
            cv::line(warpedImage, cv::Point(0, warpedImage.rows/2), cv::Point(warpedImage.cols, warpedImage.rows/2), cv::Scalar(0, 0, 255), 1);
            setOutputImageData(warpedImage);
        }
        else {
            cv::line(inputImage, cv::Point(inputImage.cols/2, 0), cv::Point(inputImage.cols/2, inputImage.rows), cv::Scalar(0, 0, 255), 1);
            cv::line(inputImage, cv::Point(0, inputImage.rows/2), cv::Point(inputImage.cols, inputImage.rows/2), cv::Scalar(0, 0, 255), 1);
            setOutputImageData(inputImage);
        }
    }
    
    if (!homography.empty()) {
        setExtrinsics(homography);
        float pixelPerMm = calcPixelPerMm(warpedImage, boardSize, 30.0);
    }
    else {
        std::cout << "Homography couldn't be aquired!" << std::endl;
    }
    
    setConfigState(CONFIG_MODE_NONE);
    
    std::cout << "THREAD: Extrinsics calibarion ended." << std::endl;
}

void *configImagePosition (void *arg)
{
    std::cout << "THREAD: Image position configuration started." << std::endl;
    
    cv::Mat inputImage, adjustedImage;
    cv::Mat homography;
    
    getInputImageData(inputImage);
    
    while ((getModuleState() & MODULE_CONFIG_IMAGE_POSITION) == MODULE_CONFIG_IMAGE_POSITION) {
        getInputImageData(inputImage);
        getExtrinsics(homography);
        
        if (!inputImage.empty()) {
            char key = getUiInputKey();
            adjustImagePosition(inputImage, adjustedImage, key, homography);
            setExtrinsics(homography);
            setOutputImageData(adjustedImage);
        }
    }
    
    setConfigState(CONFIG_MODE_NONE);
    
    std::cout << "THREAD: Image position configuration ended." << std::endl;
}

void *showChessBoard (void *arg)
{
    std::cout << "THREAD: Show chessboard started." << std::endl;
    
    cv::Size boardSize = cv::Size(7, 5);
    
    while ((getModuleState() & MODULE_SHOW_CHESSBOARD) == MODULE_SHOW_CHESSBOARD) {
        cv::Mat image;
        getInputImageData(image);
        if (!image.empty()) {
            showChessBoardCorners(image, boardSize);
            setOutputImageData(image);
        }
    }
    
    std::cout << "THREAD: Show chessboard ended." << std::endl;
}
