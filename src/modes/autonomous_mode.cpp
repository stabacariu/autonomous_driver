/**
 * @file autonomous_mode.cpp
 * @author Sergiu-Petru Tabacariu
 * @date 5.4.2018
 */

#include "autonomous_mode.hpp"
#include "closing_mode.hpp"
#include "standby_mode.hpp"
#include "ui_autonomous_mode.hpp"

void AutonomousMode::run (SystemState* s)
{
    std::cout << "---------------------------------" << std::endl;
    std::cout << "MODE: Autonomous Driving Mode started" << std::endl;
    running = true;
    
    uiState.setMode(new UIAutonomousMode(vehicle, lane, obstacles, trafficSigns));
    
    std::thread uiShowThread(&UserInterface::run, &ui, std::ref(outputImage), std::ref(uiState));
    std::thread imageAcquisitionThread(&CameraImageAcquisitor::run, &camera, std::ref(inputImage));
    std::thread laneDetectonThread(&LaneDetector::run, &laneDetector, std::ref(inputImage), std::ref(outputImage), std::ref(lane));
    std::thread trafficSignDetectionThread(&TrafficSignDetector::run, &trafficSignDetector, std::ref(inputImage), std::ref(inputImage), std::ref(trafficSigns));
    std::thread objectDetectionThread(&ObstacleDetector::run, &obstacleDetector, std::ref(obstacles));
    std::thread pathPlanningThread(&PathPlanner::run, &pathPlanner, std::ref(inputImage), std::ref(lane), std::ref(obstacles), std::ref(vehicle));
    std::thread vehicleControlThread(&VehicleController::run, &vehicleController, std::ref(vehicle));
    
    char key = (char)(-1);
    
    while (running) {
        key = uiState.getKey();
        if ((key == 27) ||
            (key == 'q') ||
            (key == 'Q') ||
            (key == 'B')) {
            running = false;
        }
    }
    quit();
    
    uiShowThread.join();
    imageAcquisitionThread.join();
    laneDetectonThread.join();
    trafficSignDetectionThread.join();
    objectDetectionThread.join();
    pathPlanningThread.join();
    vehicleControlThread.join();
    
    switch (key) {
        case 27: s->setMode(new ClosingMode()); break;
        case 'q': s->setMode(new ClosingMode()); break;
        case 'Q': s->setMode(new ClosingMode()); break;
        case 'B': s->setMode(new StandbyMode()); break;
    }
    delete this;
}

void AutonomousMode::quit ()
{
    stopModules();
    std::cout << "MODE: Quitting autonomous system mode..." << std::endl;
    running = false;
}

void AutonomousMode::stopModules ()
{
    std::cout << "MODE: Stopping all modules..." << std::endl;
    ui.quit();
    camera.quit();
    laneDetector.quit();
    trafficSignDetector.quit();
    obstacleDetector.quit();
    pathPlanner.quit();
    vehicleController.quit();
}
