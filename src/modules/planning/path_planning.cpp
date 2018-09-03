/**
 * @file path_planning.cpp
 * @author Sergiu-Petru Tabacariu
 * @date 25.8.2017
 */

#include "path_planning.hpp"
#include "configuration.hpp"

void PathPlanner::run (ImageData& inputImage, ImageData& outputImage, LaneData& lane, TrafficSignData& trafficSigns, ObstacleData& obstacles, VehicleModel& vehicle, TrajectoryData& trajectory)
{
    std::cout << "THREAD: Path planning started." << std::endl;
    running = true;
    
    Configurator& config = Configurator::instance();
    camConfig = config.getCameraConfig();
    
    cv::KalmanFilter kfT(4, 4, 0);
    initLinePrediction(kfT, 4);
        
    cv::Vec4i actualLeftLine;
    cv::Vec4i actualRightLine;
    
    while (running && !error) {
        std::vector<cv::Vec4i> actualLane;
        actualLane.push_back(lane.getLeftLine());
        actualLane.push_back(lane.getRightLine());
        
        // Obtacle Detection before trajectory calculation
        bool safetyDistance = true;
        if (obstacles.getDistance() > 25) {
            safetyDistance = false;
        }
        
        cv::Rect stopSign = trafficSigns.getRoi();
        if (stopSign.width > 30 && stopSign.height > 30) {
            safetyDistance = false;
            std::cout << "INFO: Stop sign in safety distance!" << std::endl;
        }
        
        if (safetyDistance && (actualLane.size() > 1)) {
            calcTrajectory(actualLane, trajectory, kfT, camConfig.imageSize);
            cv::Mat image;
            image = inputImage.read();
            if (trajectory.active) {
                drawTrajectoryLine(image, trajectory);
                outputImage.write(image);
                outputImage.setTime(inputImage.getTime());
                trajectory.active = false;
            }
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

void calcTrajectory (std::vector<cv::Vec4i> actualLane, TrajectoryData& trajectory, cv::KalmanFilter kfT, cv::Size imageSize)
{
    std::vector<cv::Vec4i> trajectoryPredicted;
    bool leftLineFound = false;
    bool rightLineFound = false;
    
    
    if (actualLane.size() > 1) {
        // Check for left line
        if (actualLane.front() != cv::Vec4i(0, 0, 0, 0)) {
            leftLineFound = true;
        }
        // Check for right line
        if (actualLane.back() != cv::Vec4i(imageSize.width-1, 0, imageSize.width-1, 0)) {
            rightLineFound = true;
        }
        
        // @todo Convert from Vec4i to Point vector
        cv::Vec4i laneMid(imageSize.width/2-1, 0, imageSize.width/2-1, imageSize.height-1);
        cv::Vec4i viewMid(imageSize.width/2-1, 0, imageSize.width/2-1, imageSize.height-1);
        
        if (leftLineFound && rightLineFound) {
            laneMid = getLaneMid(actualLane);
            std::vector<cv::Vec4i> lM;
            lM.push_back(laneMid);
            predictLine(lM, kfT, 4, trajectoryPredicted);
            if (trajectoryPredicted.size() > 0) {
                laneMid = trajectoryPredicted.front();
            }
        }
        
        if (leftLineFound && !rightLineFound) {
            laneMid = actualLane.front();
            std::vector<cv::Vec4i> lM;
            lM.push_back(laneMid);
            predictLine(lM, kfT, 4, trajectoryPredicted);
            if (trajectoryPredicted.size() > 0) {
                laneMid = trajectoryPredicted.front();
            }
        }
        
        if (!leftLineFound && rightLineFound) {
            laneMid = actualLane.back();
            std::vector<cv::Vec4i> lM;
            lM.push_back(laneMid);
            predictLine(lM, kfT, 4, trajectoryPredicted);
            if (trajectoryPredicted.size() > 0) {
                laneMid = trajectoryPredicted.front();
            }
        }
        trajectory.setLine(laneMid);
        trajectory.active = true;
    }
    else {
        trajectory.active = false;
    }
}

void drawTrajectory (cv::Mat& image, TrajectoryData& trajectory) {
    std::vector<cv::Point>  tPoints = trajectory.get();
    //~ line(image, tPoints.front(), tPoints.back(), cv::Scalar(200,200,0), 2);
    const cv::Point *pts = (const cv::Point*) cv::Mat(tPoints).data;
    int numPts = cv::Mat(tPoints).rows;
    polylines(image,&pts, &numPts, 2, false, cv::Scalar(200,200,0));
}

void drawTrajectoryLine (cv::Mat& image, TrajectoryData& trajectory) {
    cv::Vec4i tLine = trajectory.getLine();
    line(image, cv::Point(tLine[0], tLine[1]), cv::Point(tLine[2], tLine[3]), cv::Scalar(200,200,0), 2);
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
