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

void Configurator::save (void)
{
    cv::FileStorage fs(fileName, cv::FileStorage::WRITE);
    
    camConfig.save(fs);
    camCalibConfig.save(fs);
    uiConfig.save(fs);
    trafficSignDetConfig.save(fs);
    obstacleDetConfig.save(fs);
}

void Configurator::load (void)
{
    cv::FileStorage fs(fileName, cv::FileStorage::READ);
    if (!fs.isOpened()) {
        std::cerr << "ERROR: No file " << fileName << " found!" << std::endl;
        fs.release();
        
        // Try open default.xml
        fs.open("../config/default.xml", cv::FileStorage::READ);
        if (!fs.isOpened()) {
            std::cerr << "Error: No file ../config/default.xml found!" << std::endl;
        }
        else {
            fileName = "../config/default.xml";
            camConfig.load(fs);
            camCalibConfig.load(fs);
            uiConfig.load(fs);
            trafficSignDetConfig.load(fs);
            obstacleDetConfig.load(fs);
            fs.release();
        }
    }
    else {
        camConfig.load(fs);
        camCalibConfig.load(fs);
        uiConfig.load(fs);
        trafficSignDetConfig.load(fs);
        obstacleDetConfig.load(fs);
        fs.release();
    }
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

void Configurator::setTrafficSignDetectionConfig (TrafficSignDetectionConfig c)
{
    std::lock_guard<std::mutex> guard(lock);
    trafficSignDetConfig = c;
}

TrafficSignDetectionConfig Configurator::getTrafficSignDetectionConfig (void)
{
    std::lock_guard<std::mutex> guard(lock);
    return trafficSignDetConfig;
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
