/**
 * @file path_planning.cpp
 * @author Sergiu-Petru Tabacariu
 * @date 25.8.2017
 */

#include "path_planning.hpp"


void PathPlanner::run (ImageData& inputImage, LaneData& laneData, ObstacleData& obstacleData, VehicleData& vehicle)
{
    std::cout << "THREAD: Path planning started." << std::endl;
    running = true;
    
    cv::KalmanFilter kfT(4, 4, 0);
    initLinePrediction(kfT, 4);
    
    std::vector<cv::Vec4i> actualLane;
    RoadMarking actualLeftLine;
    RoadMarking actualRightLine;
    
    while (running) {
        actualLeftLine = laneData.getLeftLine();
        actualRightLine = laneData.getRightLine();
        
        if (actualLeftLine.size() > 0) {
            actualLane.push_back(cvtRoadMarkingToVec4i(actualLeftLine));
        }
        if (actualRightLine.size() > 0) {
            actualLane.push_back(cvtRoadMarkingToVec4i(actualRightLine));
        }
        
        cv::Mat image;
        image = inputImage.read();
        
        // Obtacle Detection before trajectory calculation
        bool wObtacleDetection = false;
        bool safetyDistance = false;
        if (obstacleData.getDistance() > (-1)) {
            wObtacleDetection = true;
        }
        if (wObtacleDetection) {
            if (obstacleData.getDistance() > 25) {
                safetyDistance = true;
            }
        }
        else {
            safetyDistance = true; //! @warning Safety distance cannot be measured if ultrasonic sensor is not plugged in!
        }
        
        if (safetyDistance && (actualLane.size() > 0) && (!image.empty())) {
            calcTrajectory(vehicle, actualLane, kfT, image.size());
        }
        else {
            vehicle.setSteering(CV_PI/2);
            vehicle.setAcceleration(0);
        }
    }

    std::cout << "THREAD: Path planning ended." << std::endl;
}

void PathPlanner::quit ()
{
    running = false;
}

bool PathPlanner::isRunning ()
{
    return running;
}


void calcTrajectory (VehicleData& vehicle, std::vector<cv::Vec4i> actualLane, cv::KalmanFilter kfT, cv::Size imageSize)
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
    
    double acVal = 18; // 59% if 100% full forward and 0% full reverse
    double brVal = 0; // 50% if 100% full forward and 0% full reverse
    
    if ((theta < (CV_PI*0.1)) || (theta > (CV_PI*0.90))) {
        vehicle.setAcceleration(brVal);
    }
    else if (drv) {
        // Set steering angle
        if ((theta > 0) && (theta < CV_PI/2*0.9)) {
            vehicle.setDirection(VehicleData::Direction::VEHICLE_LEFT);
            vehicle.setSteering(theta-CV_PI/8);
        }
        else if ((theta < CV_PI) && (theta > CV_PI/2*1.1)) {
            vehicle.setDirection(VehicleData::Direction::VEHICLE_RIGHT);
            vehicle.setSteering(theta+CV_PI/8);
        }
        else {
            vehicle.setDirection(VehicleData::Direction::VEHICLE_STRAIGHT);
            vehicle.setSteering(theta);
        }
        
        // Set acceleration percentage
        // Vehicle is too much to the left
        // Counter steer to the right
        if ((diffX2 > 10) && (diffX1 > 10)) {
            vehicle.setSteering(3*CV_PI/4);
            vehicle.setAcceleration(acVal-0.5);
        }
        // Vehicle is too much to the right
        // Counter steer to the left
        else if ((diffX2 < -10) && (diffX1 < -10)) {
            vehicle.setSteering(CV_PI/4);
            vehicle.setAcceleration(acVal-0.5);
        }
        else {
            vehicle.setAcceleration(acVal);
            //~ if (diffX1 > 10) {
                //~ setAcceleration(acVal);
            //~ }
            //~ else if (diffX1 < -10) {
                //~ setAcceleration(acVal);
            //~ }
            //~ else {
                //~ setAcceleration(acVal);
            //~ }
        }
    }
}


// This thread works only with lane detection 2 thread in lane_detection.hpp
//~ void *pathPlanning2 (void *arg)
//~ {
    //~ std::cout << "THREAD: Path planning started." << std::endl;
    
    //~ initLaneData();
    //~ //~ initOutputImageData();
    
    //~ cv::KalmanFilter kfT(4, 4, 0);
    //~ initLinePrediction(kfT, 4);
    
    //~ std::vector<cv::Vec4i> actualLane;
    
    //~ while ((getModuleState() & MODULE_PLAN_PATH) == MODULE_PLAN_PATH) {
        //~ //! @todo Calculate difference between middle line and lane mid.
        //~ //      Correct driving trajectory by steering
        //~ getActualLane(actualLane);
        //~ cv::Mat inputImage;
        //~ getInputImageData(inputImage);
        //~ if ((getDistance() > 25) && (actualLane.size() == 6) && (!inputImage.empty())) {
            //~ // Calculate trajectory
            //~ std::vector<cv::Vec4i> nearLane;
            //~ nearLane.push_back(actualLane[5]);
            //~ nearLane.push_back(actualLane[6]);
            
            //~ if (!actualLane.empty()) {
                //~ calcTrajectory(nearLane, kfT, getImageSize());
            //~ }
        //~ }
        //~ else {
            //~ setSteering(CV_PI/2);
            //~ setAcceleration(0);
        //~ }
    //~ }

    //~ std::cout << "THREAD: Path planning ended." << std::endl;
    //~ return NULL;
//~ }
