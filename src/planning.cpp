/**
 * @file planning.cpp
 * @author Sergiu-Petru Tabacariu
 * @date 25.8.2017
 */

#include "planning.hpp"

using namespace std;
using namespace cv;

void calcTrajectory (vector<Vec4i> actualLane, KalmanFilter kfT, Size imageSize)
{
    //~ cv::Mat interImage;
    //~ getInterImageData(interImage);
    
    vector<Vec4i> trajectoryPredicted;
    bool llf = false;
    bool rlf = false;
    bool drv = false;
    // Check for left line
    if (actualLane[0] != Vec4i(0, 0, 0, 0)) {
        llf = true;
    }
    // Check for right line
    if (actualLane[1] != Vec4i(imageSize.width-1, 0, imageSize.width-1, 0)) {
        rlf = true;
    }
    
    Vec4i laneMid;
    Vec4i viewMid(imageSize.width/2-1, 0, imageSize.width/2-1, imageSize.height-1);
    
    drv = true;
    if (llf && rlf) {
        laneMid = getLaneMid(actualLane);
        vector<Vec4i> lM;
        lM.push_back(laneMid);
        predictLine(lM, kfT, 4, trajectoryPredicted);
        laneMid = trajectoryPredicted[0];
    }
    else if (llf && !rlf) {
        laneMid = actualLane[0];
        vector<Vec4i> lM;
        lM.push_back(laneMid);
        predictLine(lM, kfT, 4, trajectoryPredicted);
        laneMid = trajectoryPredicted[0];
    }
    else if (!llf && rlf) {
        laneMid = actualLane[1];
        vector<Vec4i> lM;
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

    float theta = getTheta(Point(laneMid[0], laneMid[1]), Point(laneMid[2], laneMid[3]));
    
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
    cout << "THREAD: Path planning started." << endl;
    
    initLaneData();
    //~ initOutputImageData();
    
    KalmanFilter kfT(4, 4, 0);
    initLinePrediction(kfT, 4);
    
    vector<Vec4i> actualLane;
    
    while ((getModuleState() & MODULE_PLAN_PATH) == MODULE_PLAN_PATH) {
        //! @todo Calculate difference between middle line and lane mid.
        //      Correct driving trajectory by steering
        getActualLane(actualLane);
        cv::Mat inputImage;
        getInputImageData(inputImage);
        if ((getDistance() > 25) && (actualLane.size() > 0) && (!inputImage.empty())) {
            calcTrajectory(actualLane, kfT, getImageSize());
        }
        else {
            setSteering(CV_PI/2);
            setAcceleration(50);
        }
    }

    cout << "THREAD: Path planning ended." << endl;
    return NULL;
}


// This thread works only with lane detection 2 thread in lane_detection.hpp
void *pathPlanning2 (void *arg)
{
    cout << "THREAD: Path planning started." << endl;
    
    initLaneData();
    //~ initOutputImageData();
    
    KalmanFilter kfT(4, 4, 0);
    initLinePrediction(kfT, 4);
    
    vector<Vec4i> actualLane;
    
    while ((getModuleState() & MODULE_PLAN_PATH) == MODULE_PLAN_PATH) {
        //! @todo Calculate difference between middle line and lane mid.
        //      Correct driving trajectory by steering
        getActualLane(actualLane);
        cv::Mat inputImage;
        getInputImageData(inputImage);
        if ((getDistance() > 25) && (actualLane.size() == 6) && (!inputImage.empty())) {
            // Calculate trajectory
            vector<Vec4i> nearLane;
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

    cout << "THREAD: Path planning ended." << endl;
    return NULL;
}
