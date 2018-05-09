/**
 * @file obstacle_detection.cpp
 * @author Sergiu-Petru Tabacariu
 * @date 4.12.2017
 */

#include "obstacle_detection.hpp"
#include "configuration.hpp"

void ObstacleDetector::run (ObstacleData& obstacleData)
{
    std::cout << "THREAD: Obstacle detection started." << std::endl;
    running = true;
    
    Configurator& config = Configurator::instance();
    obstacleDetConfig = config.getObstacleDetectionConfig();
    
    int trigger = 0; //!< WiringPi lib pin number 
    int echo = 2; //!< Wirring Pi lib pin number
    
    if (wiringPiSetup() == -1) {
        std::cerr << "ERROR: Couldn't init wiringPi library!" << std::endl;
    }

    Sonar sonar;
    sonar.init(trigger, echo);
    
    while (running) {
        if (obstacleDetConfig.active) {
            std::cout << "Obstacle detection: Distance is " << sonar.distance(500) << " cm." << std::endl;
            obstacleData.setDistance(sonar.distance(500));
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(250));
    }

    std::cout << "THREAD: Obstacle detection ended." << std::endl;
}

void ObstacleDetector::quit ()
{
    running = false;
}

bool ObstacleDetector::isRunning ()
{
    return running;
}
