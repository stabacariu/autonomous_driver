/**
 * @file traffic_sign_detection.cpp
 * @author Sergiu-Petru Tabacariu
 * @date 30.6.2017
 */

#include "traffic_sign_detection.hpp"
#include "configuration.hpp"

void TrafficSignDetector::run (ImageData& inputImageData, ImageData& outputImageData, TrafficSignData& trafficSignData)
{
    std::cout << "THREAD: Traffic sign detection started." << std::endl;
    running = true;
    
    Configurator& config = Configurator::instance();
    camCalibConfig = config.getCameraCalibrationConfig();
    
    cv::CascadeClassifier stopSignCascade;
    
    bool detectionFlag = true;
    if (!stopSignCascade.load("../input/stopsign_classifier.xml")) {
        std::cerr << "ERROR: Couldn't load classifier data!" << std::endl;
        detectionFlag = false;
    }
    
    while (running) {
        cv::Mat inputImage, outputImage, homography;
        inputImage = inputImageData.read();
        outputImage = outputImageData.read();
        homography = camCalibConfig.homography;
        
        std::vector<cv::Rect> stopSigns;
        double signDistance = (-1);
        
        if (!inputImage.empty() && detectionFlag) {
            cv::Mat grayImage;
            cvtColor(inputImage, grayImage, CV_BGR2GRAY);

            stopSignCascade.detectMultiScale(grayImage, stopSigns, 1.5, 3, 0 | cv::CASCADE_SCALE_IMAGE, cv::Size(15, 15));

            //~ if ((stopSigns.size() > 0) && !outputImage.empty() && !homography.empty()) {
            if ((stopSigns.size() > 0) && !inputImage.empty()) {
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

cv::Point getSignCenter (cv::Point tl, cv::Point br)
{
    return cv::Point(tl.x + (br.x - tl.x)/2, tl.y + (br.y - tl.y)/2);
}