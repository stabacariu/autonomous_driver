/**
 * @file traffic_sign_detection.cpp
 * @author Sergiu-Petru Tabacariu
 * @date 30.6.2017
 */

#include "traffic_sign_detection.hpp"
#include "configuration.hpp"

bool TrafficSignDetectionConfig::load (cv::FileStorage fs)
{
    if (!fs.isOpened()) {
        fs.release();
        std::cerr << "ERROR: File storage not opened" << std::endl;
        return false;
    }
    else {
        fs["trafficSignDetectionActive"] >> active;
    }
    fs.release();
    return true;
}

void TrafficSignDetectionConfig::save (cv::FileStorage fs)
{
    if (!fs.isOpened()) {
        fs.release();
        std::cerr << "ERROR: File storage not opened" << std::endl;
    }
    else {
        fs.writeComment("traffic sign detection config");
        fs << "trafficSignDetectionActive" << active;
    }
    fs.release();
}

void TrafficSignDetector::run (ImageData& inputImageData, ImageData& outputImageData, TrafficSignData& trafficSignData)
{
    std::cout << "THREAD: Traffic sign detection started." << std::endl;
    running = true;
    
    Configurator& config = Configurator::instance();
    camCalibConfig = config.getCameraCalibrationConfig();
    trafficSignDetConfig = config.getTrafficSignDetectionConfig();
    
    cv::CascadeClassifier stopSignCascade;
    
    if (!trafficSignDetConfig.active) {
        running = false;
    }
    if (!stopSignCascade.load("../input/stopsign_classifier.xml")) {
        std::cerr << "ERROR: Couldn't load classifier data!" << std::endl;
        running = false;
        error = true;
    }
    
    while (running && !error) {
        cv::Mat inputImage;
        inputImage = inputImageData.read();
        
        std::vector<cv::Rect> stopSigns;
        double distance = (-1);
        
        if (!inputImage.empty()) {
            cv::Mat grayImage;
            cvtColor(inputImage, grayImage, CV_BGR2GRAY);

            stopSignCascade.detectMultiScale(grayImage, stopSigns, 1.1, 5, 0 | cv::CASCADE_SCALE_IMAGE, cv::Size(10, 10));

            if (stopSigns.size() > 0) {
                for (size_t i = 0; i < stopSigns.size(); i++) {
                    rectangle(inputImage, stopSigns.at(i), cv::Scalar(0, 255, 0), 2);
                    cv::Point signCenter;
                    signCenter = getSignCenter(stopSigns.at(i));
                    std::cout << "Traffic sign detection: Stop sign detected at [" << signCenter.x << ", "<< signCenter.y << "]" <<  std::endl;
                    
                    trafficSignData.setRoi(stopSigns.at(0));
                }
            }
            outputImageData.write(inputImage);
            outputImageData.setTime(inputImageData.getTime());
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(20));
    }

    std::cout << "THREAD: Traffic sign detection ended." << std::endl;
}
