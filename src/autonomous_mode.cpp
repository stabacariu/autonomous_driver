/**
 * @file autonomous_mode.cpp
 * @author Sergiu-Petru Tabacariu
 * @date 5.4.2018
 */

#include "autonomous_mode.hpp"
#include "closing_mode.hpp"
#include "standby_mode.hpp"
#include "ui_autonomous_mode.hpp"

void AutonomousMode::start (SystemState* s)
{
    std::cout << "---------------------------------" << std::endl;
    std::cout << "MODE: Autonomous Driving Mode started" << std::endl;
    running = true;
    
    uiState.setMode(new UIAutonomousMode(vehicle, lane, obstacle));
    std::thread uiShowThread(&UserInterface::start, &ui, std::ref(outputImage), std::ref(uiState));
    std::thread uiInputThread(&UserInterface::consoleInput, &ui, std::ref(uiState));
    std::thread imageAcquisitionThread(&CameraImageAcquisitor::start, &camera, std::ref(inputImage));
    std::thread laneDetectonThread(&LaneDetector::start, &laneDetetor, std::ref(inputImage), std::ref(outputImage), std::ref(lane));
    //~ std::thread trafficSignDetectionThread(&TrafficSignDetector::start, &trafficSignDetector, std::ref(inputImage), std::ref(outputImage));
    //~ std::thread objectDetectionThread(&ObstacleDetector::start, &obstacleDetector, std::ref(obstacle));
    std::thread pathPlanningThread(&PathPlanner::start, &pathPlanner, std::ref(inputImage), std::ref(lane), std::ref(obstacle), std::ref(vehicle));
    std::thread vehicleControlThread(&VehicleControler::start, &vehicleControler, std::ref(vehicle));
    
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
    stop();
    
    uiShowThread.join();
    uiInputThread.join();
    imageAcquisitionThread.join();
    laneDetectonThread.join();
    //~ trafficSignDetectionThread.join();
    //~ objectDetectionThread.join();
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

void AutonomousMode::stop ()
{
    stopModules();
    std::cout << "MODE: Autonomous System Mode stopped." << std::endl;
    running = false;
}

void AutonomousMode::stopModules ()
{
    std::cout << "MODE: Stopping all modules..." << std::endl;
    ui.stop();
    camera.stop();
    laneDetetor.stop();
    trafficSignDetector.stop();
    obstacleDetector.stop();
    pathPlanner.stop();
    vehicleControler.stop();
}
