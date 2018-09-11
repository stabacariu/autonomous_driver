/**
 * @file obstacle_detection.cpp
 * @author Sergiu-Petru Tabacariu
 * @date 4.12.2017
 */

#include "obstacle_detection.hpp"
#include "configuration.hpp"

bool ObstacleDetectionConfig::load (cv::FileStorage fs)
{
    if (!fs.isOpened()) {
        fs.release();
        std::cerr << "ERROR: File storage not opened" << std::endl;
        return false;
    }
    else {
        fs["obstacleDetectionActive"] >> active;
    }
    fs.release();
    return true;
}

void ObstacleDetectionConfig::save (cv::FileStorage fs)
{
    if (!fs.isOpened()) {
        fs.release();
        std::cerr << "ERROR: File storage not opened" << std::endl;
    }
    else {
        fs.writeComment("obstacle detection config");
        fs << "obstacleDetectionActive" << active;
    }
    fs.release();
}

void ObstacleDetector::run (ObstacleData& obstacleData)
{
    std::cout << "THREAD: Obstacle detection started." << std::endl;
    running = true;
    
    Configurator& config = Configurator::instance();
    obstacleDetConfig = config.getObstacleDetectionConfig();
    
    int triggerPin = 3; //!< WiringPi lib pin number 
    int echoPin = 2; //!< Wirring Pi lib pin number
    
    if (!obstacleDetConfig.active) {
        running = false;
    }
    if (wiringPiSetup() == -1) {
        std::cerr << "ERROR: Couldn't init wiringPi library!" << std::endl;
        running = false;
        error = true;
    }

    Sonar ultrasonic;
    ultrasonic.init(triggerPin, echoPin);
    
    while (running && !error) {
        double distance = ultrasonic.distance(500);
        //~ std::cout << "INFO: Obstacle detected at " << distance << " cm." << std::endl;
        obstacleData.setDistance(distance);
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }

    std::cout << "THREAD: Obstacle detection ended." << std::endl;
}
