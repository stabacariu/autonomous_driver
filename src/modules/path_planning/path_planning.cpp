/**
 * @file path_planning.cpp
 * @author Sergiu-Petru Tabacariu
 * @date 25.8.2017
 */

#include "path_planning.hpp"
#include "configuration.hpp"

void PathPlanner::run (ImageData& inputImage, LaneData& lane, TrafficSignData& trafficSigns, ObstacleData& obstacle, VehicleModel& vehicle, TrajectoryData& trajectory)
{
    std::cout << "THREAD: Path planning started." << std::endl;
    running = true;
    
    Configurator& config = Configurator::instance();
    camConfig = config.getCameraConfig();
    obstacleDetConfig = config.getObstacleDetectionConfig();
    
    cv::KalmanFilter kfT(4, 4, 0);
    initLinePrediction(kfT, 4);
    
    std::vector<cv::Vec4i> actualLane;
    RoadMarking actualLeftLine;
    RoadMarking actualRightLine;
    
    while (running && !error) {
        actualLeftLine = lane.getLeftLine();
        if (actualLeftLine.size() > 0) {
            actualLane.push_back(cvtRoadMarkingToVec4i(actualLeftLine));
        }
        actualRightLine = lane.getRightLine();
        if (actualRightLine.size() > 0) {
            actualLane.push_back(cvtRoadMarkingToVec4i(actualRightLine));
        }
        
        // Obtacle Detection before trajectory calculation
        bool safetyDistance = false;
        if (obstacleDetConfig.active) {
            if (obstacle.getDistance() > 25) {
                safetyDistance = true;
            }
        }
        else {
            safetyDistance = true; //! @warning Safety distance cannot be measured if ultrasonic sensor is not plugged in!
        }
        
        if (trafficSigns.getDistance() != (-1)) {
            cv::Rect stopSign = trafficSigns.getRoi();
            if ((stopSign.width > 25) || (stopSign.height > 25)) {
                safetyDistance = false;
                std::cout << "Stop sign in safety distance! Stop!" << std::endl;
            }
        }
        
        if (safetyDistance && (actualLane.size() > 0)) {
            calcTrajectory(vehicle, actualLane, trajectory, kfT, camConfig.imageSize);
        }
        else {
            vehicle.stop();
            vehicle.setSteering(CV_PI/2);
            vehicle.setAcceleration(0);
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(20));
    }

    std::cout << "THREAD: Path planning ended." << std::endl;
}

void calcTrajectory (VehicleModel& vehicle, std::vector<cv::Vec4i> actualLane, TrajectoryData& trajectory, cv::KalmanFilter kfT, cv::Size imageSize)
{
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
    
    // @todo Convert from Vec4i to Point vector
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
    
    trajectory.clear();
    trajectory.push_back(cv::Point(laneMid[0], laneMid[1]));
    trajectory.push_back(cv::Point(laneMid[2], laneMid[3]));
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
