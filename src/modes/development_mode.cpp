/**
 * @file development_mode.cpp
 * @author Sergiu-Petru Tabacariu
 * @date 5.4.2018
 */

#include "development_mode.hpp"
#include "closing_mode.hpp"
#include "standby_mode.hpp"
#include "ui_development_mode.hpp"

void DevelopmentMode::run (SystemState* s)
{
    std::cout << "---------------------------------" << std::endl;
    std::cout << "MODE: Development Mode started" << std::endl;
    running = true;
    
    uiState.setMode(new UIDevelopmentMode(vehicle, lane, obstacle, trafficSignData));
    std::thread uiShowThread(&UserInterface::run, &ui, std::ref(outputImage), std::ref(uiState));
    std::thread imageAcquisitionThread(&CameraImageAcquisitor::run, &camera, std::ref(inputImage));
    std::thread laneDetectonThread(&LaneDetector::run, &laneDetector, std::ref(inputImage), std::ref(outputImage), std::ref(lane));
    std::thread trafficSignDetectionThread(&TrafficSignDetector::run, &trafficSignDetector, std::ref(inputImage), std::ref(inputImage), std::ref(trafficSignData));
    std::thread obstacleDetectionThread(&ObstacleDetector::run, &obstacleDetector, std::ref(obstacle));
    std::thread remoteControlThread(&RemoteController::run, &remoteController, std::ref(vehicle), std::ref(uiState));
    std::thread vehicleControlThread(&VehicleController::run, &vehicleController, std::ref(trajectory), std::ref(vehicle));
    
    char key = (char)(-1);
    
    while (running) {
        key = uiState.getKey();
        if ((key == 27) ||
            (key == 'q') ||
            (key == 'Q') ||
            (key == 'B')) {
            running = false;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }
    quit();
    
    uiShowThread.join();
    imageAcquisitionThread.join();
    laneDetectonThread.join();
    trafficSignDetectionThread.join();
    obstacleDetectionThread.join();
    remoteControlThread.join();
    vehicleControlThread.join();
    
    switch (key) {
        case 27: s->setMode(new ClosingMode()); break;
        case 'q': s->setMode(new ClosingMode()); break;
        case 'Q': s->setMode(new ClosingMode()); break;
        case 'B': s->setMode(new StandbyMode()); break;
    }
    delete this;
}

void DevelopmentMode::quit ()
{
    stopModules();
    std::cout << "MODE: Quitting development system mode..." << std::endl;
    running = false;
}

void DevelopmentMode::stopModules ()
{
    std::cout << "MODE: Stopping all modules..." << std::endl;
    ui.quit();
    camera.quit();
    laneDetector.quit();
    trafficSignDetector.quit();
    obstacleDetector.quit();
    remoteController.quit();
    vehicleController.quit();
}

