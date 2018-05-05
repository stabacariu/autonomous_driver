/**
 * @file obstacle_detection.cpp
 * @author Sergiu-Petru Tabacariu
 * @date 4.12.2017
 */

#include "obstacle_detection.hpp"

void ObstacleDetector::start (ObstacleDetectionConfig& config, ObstacleData& obstacleData)
{
    std::cout << "THREAD: Obstacle detection started." << std::endl;
    running = true;
    
    int trigger = 0; //!< WiringPi lib pin number 
    int echo = 2; //!< Wirring Pi lib pin number
    
    if (wiringPiSetup() == -1) {
        std::cerr << "ERROR: Couldn't init wiringPi lib!" << std::endl;
    }

    Sonar sonar;
    sonar.init(trigger, echo);
    
    while (running) {
        if (config.active) {
            std::cout << "Obstacle detection: Distance is " << sonar.distance(500) << " cm." << std::endl;
            obstacleData.setDistance(sonar.distance(500));
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }

    std::cout << "THREAD: Obstacle detection ended." << std::endl;
}

void ObstacleDetector::stop ()
{
    running = false;
}

bool ObstacleDetector::isRunning ()
{
    return running;
}
