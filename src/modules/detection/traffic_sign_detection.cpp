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
    
    if (!stopSignCascade.load("../input/stopsign_classifier.xml")) {
        std::cerr << "ERROR: Couldn't load classifier data!" << std::endl;
        running = false;
    }
    
    //~ while (running && trafficSignDetConfig.active) {
    while (running) {
        cv::Mat inputImage, outputImage, homography;
        inputImage = inputImageData.read();
        outputImage = outputImageData.read();
        homography = camCalibConfig.homography;
        
        std::vector<cv::Rect> stopSigns;
        double signDistance = (-1);
        
        if (!inputImage.empty()) {
            cv::Mat grayImage;
            cvtColor(inputImage, grayImage, CV_BGR2GRAY);

            stopSignCascade.detectMultiScale(grayImage, stopSigns, 1.1, 3, 0 | cv::CASCADE_SCALE_IMAGE, cv::Size(20, 20), cv::Size(35,35));

            //~ if ((stopSigns.size() > 0) && !outputImage.empty() && !homography.empty()) {
            if (stopSigns.size() > 0) {
                for (size_t i = 0; i < stopSigns.size(); i++) {
                    //~ rectangle(outputImage, stopSigns[i], cv::Scalar(0, 255, 0), 1);
                    rectangle(inputImage, stopSigns[i], cv::Scalar(0, 255, 0), 1);
                    //! @todo Convert sign mid to perspective to get correct distance.
                    std::vector<cv::Point> signCenter;
                    signCenter.push_back(getSignCenter(stopSigns[i].tl(), stopSigns[i].br()));
                    signDistance = signCenter[0].y * camCalibConfig.mmPerPixel; 
                    std::cout << "Traffic sign detection: Stop sign detected at " << signCenter[0] << " approx " << signDistance << std::endl;
                                        
                    trafficSignData.setRoi(stopSigns[i]);
                    trafficSignData.setDistance(signDistance);
                }
            }
            //~ outputImageData.write(outputImage);
            outputImageData.write(inputImage);
        }
    }

    std::cout << "THREAD: Traffic sign detection ended." << std::endl;
}

void TrafficSignDetector::quit ()
{
    running = false;
}

bool TrafficSignDetector::isRunning ()
{
    return running;
}
