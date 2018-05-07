/**
 * @file configuration.cpp
 * @author Sergiu-Petru Tabacariu
 * @date 18.09.2017
 */

#include "configuration.hpp"

Configurator& Configurator::instance (const std::string file)
{
    static Configurator instance(file);
    return instance;
}

void Configurator::setCameraConfig (CameraConfig c)
{
    std::lock_guard<std::mutex> guard(lock);
    camConfig = c;
}

CameraConfig Configurator::getCameraConfig (void)
{
    std::lock_guard<std::mutex> guard(lock);
    return camConfig;
}

void Configurator::saveCameraConfig (void)
{
    cv::FileStorage fs(fileName, cv::FileStorage::WRITE);
    
    if (!fs.isOpened()) {
        fs.release();
        std::cerr << "ERROR: File " << fileName << " does not exist!" << std::endl;
    }
    else {
        std::lock_guard<std::mutex> guard(lock);
        fs.writeComment("camera config");
        fs << "cameraID" << camConfig.id
        << "cameraImageSize_width" << camConfig.imageSize.width
        << "cameraImageSize_height" << camConfig.imageSize.height
        << "cameraFPS" << camConfig.fps;
    }
    fs.release();
}

void Configurator::loadCameraConfig (void)
{
    cv::FileStorage fs(fileName, cv::FileStorage::READ);
    
    if (!fs.isOpened()) {
        fs.release();
        std::cerr << "ERROR: File " << fileName << " does not exist!" << std::endl;
    }
    else {
        std::lock_guard<std::mutex> guard(lock);
        fs["cameraID"] >> camConfig.id;
        fs["cameraImageSize_width"] >> camConfig.imageSize.width;
        fs["cameraImageSize_height"] >> camConfig.imageSize.height;
        fs["cameraFPS"] >> camConfig.fps;
    }
    fs.release();
}

void Configurator::setCameraCalibrationConfig (CameraCalibrationConfig c)
{
    std::lock_guard<std::mutex> guard(lock);
    camCalibConfig = c;
}

CameraCalibrationConfig Configurator::getCameraCalibrationConfig (void)
{
    std::lock_guard<std::mutex> guard(lock);
    return camCalibConfig;
}

void Configurator::saveCameraCalibrationConfig (void)
{
    cv::FileStorage fs(fileName, cv::FileStorage::WRITE);
    
    if (!fs.isOpened()) {
        fs.release();
        std::cerr << "ERROR: File " << fileName << " does not exist!" << std::endl;
    }
    else {
        std::lock_guard<std::mutex> guard(lock);
        fs.writeComment("camera calibration config");
        fs << "camCalibImageSize_width" << camCalibConfig.imageSize.width
        << "camCalibImageSize_height" << camCalibConfig.imageSize.height
        << "camCalibPattern" << camCalibConfig.pattern
        << "camCalibPatternSize_width" << camCalibConfig.patternSize.width
        << "camCalibPatternSize_height" << camCalibConfig.patternSize.height
        << "camCalibPatternMm" << camCalibConfig.patternMm
        << "camCalibnumSamples" << camCalibConfig.numSamples;
        
        fs.writeComment("Calibration data");
        fs << "camCalibIntrDone" << camCalibConfig.intrCalibDone
        << "cameraMatrix" << camCalibConfig.cameraMatrix
        << "distCoeffs" << camCalibConfig.distCoeffs
        << "camCalibExtrDone" << camCalibConfig.extrCalibDone
        << "homography" << camCalibConfig.homography
        << "transformation" << camCalibConfig.transformation
        << "pixelPerMm" << camCalibConfig.pixelPerMm;
    }
    fs.release();
}

void Configurator::loadCameraCalibrationConfig (void)
{
    cv::FileStorage fs(fileName, cv::FileStorage::READ);
    
    if (!fs.isOpened()) {
        fs.release();
        std::cerr << "ERROR: File " << fileName << " does not exist!" << std::endl;
    }
    else {
        std::lock_guard<std::mutex> guard(lock);
        fs["camCalibImageSize_width"] >> camCalibConfig.imageSize.width;
        fs["camCalibImageSize_height"] >> camCalibConfig.imageSize.height;
        fs["camCalibPattern"] >> camCalibConfig.pattern;
        fs["camCalibPatternSize_width"] >> camCalibConfig.patternSize.width;
        fs["camCalibPatternSize_height"] >> camCalibConfig.patternSize.height;
        fs["camCalibPatternMm"] >> camCalibConfig.patternMm;
        fs["camCalibnumSamples"] >> camCalibConfig.numSamples;
        fs["cameraMatrix"] >> camCalibConfig.cameraMatrix;
        fs["distCoeffs"] >> camCalibConfig.distCoeffs;
        fs["camCalibIntrDone"] >> camCalibConfig.intrCalibDone;
        fs["homography"] >> camCalibConfig.homography;
        fs["camCalibExtrDone"] >> camCalibConfig.extrCalibDone;
        fs["transformation"] >> camCalibConfig.transformation;
        fs["pixelPerMm"] >> camCalibConfig.pixelPerMm;
    }
    fs.release();
}

void Configurator::setUserInterfaceConfig (UserInterfaceConfig c)
{
    std::lock_guard<std::mutex> guard(lock);
    uiConfig = c;
}

UserInterfaceConfig Configurator::getUserInterfaceConfig (void)
{
    std::lock_guard<std::mutex> guard(lock);
    return uiConfig;
}

void Configurator::saveUserInterfaceConfig (void)
{
    cv::FileStorage fs(fileName, cv::FileStorage::WRITE);
    
    if (!fs.isOpened()) {
        fs.release();
        std::cerr << "ERROR: File " << fileName << " does not exist!" << std::endl;
    }
    else {
        std::lock_guard<std::mutex> guard(lock);
        fs.writeComment("user interface config");
        fs << "uiMainWindowName" << uiConfig.mainWindowName
        << "uiImageSize_width" << uiConfig.imageSize.width
        << "uiImageSize_height" << uiConfig.imageSize.height
        << "uiMenuWidth" << uiConfig.menuWidth
        << "uiFPS" << uiConfig.fps;
    }
    fs.release();
}

void Configurator::loadUserInterfaceConfig (void)
{
    cv::FileStorage fs(fileName, cv::FileStorage::READ);
    
    if (!fs.isOpened()) {
        fs.release();
        std::cerr << "ERROR: File " << fileName << " does not exist!" << std::endl;
    }
    else {
        std::lock_guard<std::mutex> guard(lock);
        fs["uiMainWindowName"] >> uiConfig.mainWindowName;
        fs["uiImageSize_width"] >> uiConfig.imageSize.width;
        fs["uiImageSize_height"] >> uiConfig.imageSize.height;
        fs["uiMenuWidth"] >> uiConfig.menuWidth;
        fs["uiFPS"] >> uiConfig.fps;
    }
    fs.release();
}

void Configurator::setObstacleDetectionConfig (ObstacleDetectionConfig c)
{
    std::lock_guard<std::mutex> guard(lock);
    obstacleDetConfig = c;
}

ObstacleDetectionConfig Configurator::getObstacleDetectionConfig (void)
{
    std::lock_guard<std::mutex> guard(lock);
    return obstacleDetConfig;
}

void Configurator::saveObstacleDetectionConfig (void)
{
    cv::FileStorage fs(fileName, cv::FileStorage::WRITE);
    
    if (!fs.isOpened()) {
        fs.release();
        std::cerr << "ERROR: File " << fileName << " does not exist!" << std::endl;
    }
    else {
        std::lock_guard<std::mutex> guard(lock);
        fs.writeComment("obstacle detection config");
        fs << "obstacleDetectionActive" << obstacleDetConfig.active;
    }
    fs.release();
}

void Configurator::loadObstacleDetectionConfig (void)
{
    cv::FileStorage fs(fileName, cv::FileStorage::READ);
    
    if (!fs.isOpened()) {
        fs.release();
        std::cerr << "ERROR: File " << fileName << " does not exist!" << std::endl;
    }
    else {
        std::lock_guard<std::mutex> guard(lock);
        fs["obstacleDetectionActive"] >> obstacleDetConfig.active;
    }
    fs.release();
}
