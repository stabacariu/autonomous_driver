/**
 * @file obstacle_detection.cpp
 * @author Sergiu-Petru Tabacariu
 * @date 4.12.2017
 */

#include "obstacle_detection.hpp"
#include "autonomous_driver.hpp"

ObstacleData obstacle;

void initObstacleData (void)
{
    pthread_mutex_init(&obstacle.lock, NULL);
}

double getDistance (void)
{
    double distance;
    
    if (pthread_mutex_lock(&obstacle.lock)) {
        std::cerr << "ERROR: Couldn't lock actual position mutex!" << std::endl;
    }
    
    distance = obstacle.distance;
    
    if (pthread_mutex_unlock(&obstacle.lock)) {
        std::cerr << "ERROR: Couldn't unlock actual position mutex!" << std::endl;
    }
    
    return distance;
}

void setDistance (double distance)
{
    if (pthread_mutex_lock(&obstacle.lock)) {
        std::cerr << "ERROR: Couldn't lock actual position mutex!" << std::endl;
    }
    
    obstacle.distance = distance;
    
    if (pthread_mutex_unlock(&obstacle.lock)) {
        std::cerr << "ERROR: Couldn't unlock actual position mutex!" << std::endl;
    }
}

void *obstacleDetection (void *arg)
{
    std::cout << "THREAD: Obstacle detection started." << std::endl;
    
    int trigger = 3; //!< WiringPi lib pin number 
    int echo = 2; //!< Wirring Pi lib pin number
    
    if (wiringPiSetup() == -1) {
        std::cerr << "ERROR: Couldn't init wiringPi lib!" << std::endl;
    }

    Sonar sonar;
    sonar.init(trigger, echo);
    
    initObstacleData();
        
    while ((getModuleState() & MODULE_DETECT_OBSTACLE) == MODULE_DETECT_OBSTACLE) {
        //~ std::cout << "Obstacle detection: Distance is " << sonar.distance(1000) << " cm." << std::endl;
        setDistance(sonar.distance(500));
        delay(500);
    }

    std::cout << "THREAD: Obstacle detection ended." << std::endl;
    return NULL;
}
