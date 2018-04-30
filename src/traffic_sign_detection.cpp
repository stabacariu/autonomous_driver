/**
 * @file traffic_sign_detection.cpp
 * @author Sergiu-Petru Tabacariu
 * @date 30.6.2017
 */

#include "traffic_sign_detection.hpp"

void TrafficSignDetector::start (ImageData& inputImageData, ImageData& outputImageData)
{
    std::cout << "THREAD: Traffic sign detection started." << std::endl;
    cv::CascadeClassifier stopSignCascade;
    
    if (!stopSignCascade.load("../input/stopsign_classifier.xml")) {
        std::cerr << "ERROR: Couldn't load classifier data!" << std::endl;
    }
    
    while (running) {
        cv::Mat inputImage, outputImage, homography;
        inputImage = inputImageData.read();
        outputImage = outputImageData.read();
        
        std::vector<cv::Rect> stopSigns;
        
        if (!inputImage.empty()) {
            cv::Mat grayImage;
            cvtColor(inputImage, grayImage, CV_BGR2GRAY);

            stopSignCascade.detectMultiScale(grayImage, stopSigns, 1.5, 3, 0 | cv::CASCADE_SCALE_IMAGE, cv::Size(15, 15));

            if ((stopSigns.size() > 0) && !outputImage.empty() && !homography.empty()) {
                for (size_t i = 0; i < stopSigns.size(); i++) {
                    rectangle(outputImage, stopSigns[i], cv::Scalar(0, 255, 0), 1);
                    //! @todo Convert sign mid to perspective to get correct distance.
                    std::vector<cv::Point> signCenter;
                    signCenter.push_back(getSignCenter(stopSigns[i].tl(), stopSigns[i].br()));
                    //~ perspectiveTransform(signCenter, signCenter, homography);
                    //~ std::cout << "Traffic sign detection: Stop sign detected at " << signCenter[0] << " approx " << getPxPerMm()*signCenter[0].y << std::endl;
                    std::cout << "Traffic sign detection: Stop sign detected at " << signCenter[0] << " approx " << signCenter[0].y << std::endl;
                }
            }
            //~ setOutputImageData(outputImage);
            outputImageData.write(outputImage);
        }
    }

    std::cout << "THREAD: Traffic sign detection ended." << std::endl;
}

void TrafficSignDetector::stop ()
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
