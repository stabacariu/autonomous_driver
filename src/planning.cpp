/**
 * @file planning.cpp
 * @author Sergiu-Petru Tabacariu
 * @date 25.8.2017
 */

#include "planning.hpp"

void calcTrajectory (std::vector<cv::Vec4i> actualLane, cv::KalmanFilter kfT, cv::Size imageSize)
{
    //~ cv::Mat interImage;
    //~ getInterImageData(interImage);
    
    std::vector<cv::Vec4i> trajectoryPredicted;
    bool llf = false;
    bool rlf = false;
    bool drv = false;
    // Check for left line
    if (actualLane[0] != cv::Vec4i(0, 0, 0, 0)) {
        llf = true;
    }
    // Check for right line
    if (actualLane[1] != cv::Vec4i(imageSize.width-1, 0, imageSize.width-1, 0)) {
        rlf = true;
    }
    
    cv::Vec4i laneMid;
    cv::Vec4i viewMid(imageSize.width/2-1, 0, imageSize.width/2-1, imageSize.height-1);
    
    drv = true;
    if (llf && rlf) {
        laneMid = getLaneMid(actualLane);
        std::vector<cv::Vec4i> lM;
        lM.push_back(laneMid);
        predictLine(lM, kfT, 4, trajectoryPredicted);
        laneMid = trajectoryPredicted[0];
    }
    else if (llf && !rlf) {
        laneMid = actualLane[0];
        std::vector<cv::Vec4i> lM;
        lM.push_back(laneMid);
        predictLine(lM, kfT, 4, trajectoryPredicted);
        laneMid = trajectoryPredicted[0];
    }
    else if (!llf && rlf) {
        laneMid = actualLane[1];
        std::vector<cv::Vec4i> lM;
        lM.push_back(laneMid);
        predictLine(lM, kfT, 4, trajectoryPredicted);
        laneMid = trajectoryPredicted[0];
    }
    else {
        drv = false;
    }
    
    //~ drawArrowedLine(interImage, laneMid, Scalar(200, 200, 0));
    //~ setOutputImageData(interImage);
    
    int diffX1 = laneMid[0]-viewMid[0]; // If result positive then lane is to much to the right. Car must steer to the right.
    int diffX2 = laneMid[2]-viewMid[2];

    float theta = getTheta(cv::Point(laneMid[0], laneMid[1]), cv::Point(laneMid[2], laneMid[3]));
    
    double acVal = 59;
    double brVal = 50;
    
    if ((theta < (CV_PI*0.1)) || (theta > (CV_PI*0.90))) {
        setAcceleration(brVal);
    }
    else if (drv) {
        if ((theta > 0) && (theta < CV_PI/2*0.9)) {
            setDirection(VEHICLE_LEFT);
            setSteering(theta-CV_PI/8);
        }
        else if ((theta < CV_PI) && (theta > CV_PI/2*1.1)) {
            setDirection(VEHICLE_RIGHT);
            setSteering(theta+CV_PI/8);
        }
        else {
            setDirection(VEHICLE_STRAIGHT);
            setSteering(theta);
        }
        
        // Vehicle is too much to the left
        // Counter steer to the right
        if ((diffX2 > 10) && (diffX1 > 10)) {
            setSteering(3*CV_PI/4);
            setAcceleration(acVal-0.5);
        }
        // Vehicle is too much to the right
        // Counter steer to the left
        else if ((diffX2 < -10) && (diffX1 < -10)) {
            setSteering(CV_PI/4);
            setAcceleration(acVal-0.5);
        }
        else {
            if (diffX1 > 10) {
                setAcceleration(acVal);
            }
            else if (diffX1 < -10) {
                setAcceleration(acVal);
            }
            else {
                setAcceleration(acVal);
            }
        }
    }
}

void *pathPlanning (void *arg)
{
    std::cout << "THREAD: Path planning started." << std::endl;
    
    initLaneData();
    //~ initOutputImageData();
    
    cv::KalmanFilter kfT(4, 4, 0);
    initLinePrediction(kfT, 4);
    
    std::vector<cv::Vec4i> actualLane;
    
    while ((getModuleState() & MODULE_PLAN_PATH) == MODULE_PLAN_PATH) {
        getActualLane(actualLane);
        cv::Mat inputImage;
        getInputImageData(inputImage);
        
        bool wObjectDetection = false;
        bool safetyDistance = false;
        if ((getModuleState() & MODULE_DETECT_OBSTACLE) == MODULE_DETECT_OBSTACLE) {
            wObjectDetection = true;
        }
        if (wObjectDetection) {
            if (getDistance() > 25) {
                safetyDistance = true;
            }
        }
        else {
            safetyDistance = true; //!< @warning No safety distance can be measured if ultrasonic sensor is not plugged in!S
        }
        
        if (safetyDistance && (actualLane.size() > 0) && (!inputImage.empty())) {
            calcTrajectory(actualLane, kfT, getImageSize());
        }
        else {
            setSteering(CV_PI/2);
            setAcceleration(50);
        }
    }

    std::cout << "THREAD: Path planning ended." << std::endl;
    return NULL;
}


// This thread works only with lane detection 2 thread in lane_detection.hpp
void *pathPlanning2 (void *arg)
{
    std::cout << "THREAD: Path planning started." << std::endl;
    
    initLaneData();
    //~ initOutputImageData();
    
    cv::KalmanFilter kfT(4, 4, 0);
    initLinePrediction(kfT, 4);
    
    std::vector<cv::Vec4i> actualLane;
    
    while ((getModuleState() & MODULE_PLAN_PATH) == MODULE_PLAN_PATH) {
        //! @todo Calculate difference between middle line and lane mid.
        //      Correct driving trajectory by steering
        getActualLane(actualLane);
        cv::Mat inputImage;
        getInputImageData(inputImage);
        if ((getDistance() > 25) && (actualLane.size() == 6) && (!inputImage.empty())) {
            // Calculate trajectory
            std::vector<cv::Vec4i> nearLane;
            nearLane.push_back(actualLane[5]);
            nearLane.push_back(actualLane[6]);
            
            if (!actualLane.empty()) {
                calcTrajectory(nearLane, kfT, getImageSize());
            }
        }
        else {
            setSteering(CV_PI/2);
            setAcceleration(50);
        }
    }

    std::cout << "THREAD: Path planning ended." << std::endl;
    return NULL;
}
