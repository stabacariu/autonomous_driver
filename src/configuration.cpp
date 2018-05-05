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
    cameraData = c;
}

CameraConfig Configurator::getCameraConfig (void)
{
    return cameraData;
}

void Configurator::saveCameraConfig (void)
{
    cv::FileStorage fs(fileName, cv::FileStorage::WRITE);
    
    if (!fs.isOpened()) {
        fs.release();
        std::cerr << "ERROR: File " << fileName << " does not exist!" << std::endl;
    }
    else {
        fs.writeComment("Camera config");
        fs << "cameraID" << cameraData.id
        << "cameraImageSize_width" << cameraData.imageSize.width
        << "cameraImageSize_height" << cameraData.imageSize.height
        << "cameraFPS" << cameraData.fps;
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
        fs["cameraID"] >> cameraData.id;
        fs["cameraImageSize_width"] >> cameraData.imageSize.width;
        fs["cameraImageSize_height"] >> cameraData.imageSize.height;
        fs["cameraFPS"] >> cameraData.fps;
    }
    fs.release();
}

void Configurator::setCameraCalibrationConfig (CameraCalibrationConfig c)
{
    camCalibConfig = c;
}

CameraCalibrationConfig Configurator::getCameraCalibrationConfig (void)
{
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
        fs.writeComment("Calibration config");
        fs << "calibImageSize_width" << camCalibConfig.imageSize.width
        << "calibImageSize_height" << camCalibConfig.imageSize.height
        << "calibPattern" << camCalibConfig.pattern
        << "calibPatternSize_width" << camCalibConfig.patternSize.width
        << "calibPatternSize_height" << camCalibConfig.patternSize.height
        << "calibPatternMm" << camCalibConfig.patternMm
        << "calibnumSamples" << camCalibConfig.numSamples;
        
        fs.writeComment("Calibration data");
        fs << "calibrateIntrinsicsDone" << camCalibConfig.intrCalibDone
        << "cameraMatrix" << camCalibConfig.cameraMatrix
        << "distCoeffs" << camCalibConfig.distCoeffs
        << "calibrateExtrinsicsDone" << camCalibConfig.extrCalibDone
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
        fs["calibImageSize_width"] >> camCalibConfig.imageSize.width;
        fs["calibImageSize_height"] >> camCalibConfig.imageSize.height;
        fs["calibPattern"] >> camCalibConfig.pattern;
        fs["calibPatternSize_width"] >> camCalibConfig.patternSize.width;
        fs["calibPatternSize_height"] >> camCalibConfig.patternSize.height;
        fs["calibPatternMm"] >> camCalibConfig.patternMm;
        fs["calibnumSamples"] >> camCalibConfig.numSamples;
        fs["cameraMatrix"] >> camCalibConfig.cameraMatrix;
        fs["distCoeffs"] >> camCalibConfig.distCoeffs;
        fs["calibrateIntrinsicsDone"] >> camCalibConfig.intrCalibDone;
        fs["homography"] >> camCalibConfig.homography;
        fs["calibrateExtrinsicsDone"] >> camCalibConfig.extrCalibDone;
        fs["transformation"] >> camCalibConfig.transformation;
        fs["pixelPerMm"] >> camCalibConfig.pixelPerMm;
    }
    fs.release();
}
