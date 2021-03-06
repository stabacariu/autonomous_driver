/**
 * @file remote_control_mode.cpp
 * @author Sergiu-Petru Tabacariu
 * @date 5.4.2018
 */

#include "remote_control_mode.hpp"
#include "closing_mode.hpp"
#include "error_mode.hpp"
#include "standby_mode.hpp"
#include "autonomous_mode.hpp"
#include "ui_remote_control_mode.hpp"

void RemoteControlMode::run (SystemState* s)
{
    std::cout << "---------------------------------" << std::endl;
    std::cout << "Remote Control System Mode started." << std::endl;
    running = true;
    
    uiState.setMode(new UIRemoteControlMode(vehicle));
    
    std::thread uiShowThread(&UserInterface::run, &ui, std::ref(inputImage), std::ref(uiState));
    std::thread imageAcquisitionThread(&CameraImageAcquisitor::run, &camera, std::ref(inputImage));
    std::thread remoteControlThread(&RemoteController::run, &remoteController, std::ref(vehicle), std::ref(uiState));
    std::thread vehicleControlThread(&VehicleController::run, &vehicleController, std::ref(trajectory), std::ref(vehicle));
    
    char key = (char)(-1);
    
    while (running) {
        // Check valid user input
        key = uiState.getKey();
        if ((key == 27) ||
            (key == 'q') ||
            (key == 'Q') ||
            (key == 'B')) {
            running = false;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
        
        // Check for module error
        if (ui.isError() ||
            camera.isError() ||
            remoteController.isError() ||
            vehicleController.isError()) {
            running = false;
            error = true;
        }
    }
    quit();
    
    uiShowThread.join();
    imageAcquisitionThread.join();
    remoteControlThread.join();
    vehicleControlThread.join();
    
    if (error) {
        s->setMode(new StandbyMode());
    }
    else {
        switch (key) {
            case 27: s->setMode(new ClosingMode()); break;
            case 'q': s->setMode(new ClosingMode()); break;
            case 'Q': s->setMode(new ClosingMode()); break;
            case 'B': s->setMode(new StandbyMode()); break;
            default: s->setMode(new ErrorMode()); break;
        }
    }
    delete this;
}

void RemoteControlMode::quit ()
{
    stopModules();
    std::cout << "Remote Control System Mode stopped." << std::endl;
    running = false;
}

void RemoteControlMode::stopModules ()
{
    std::cout << "MODE: Quiting Remoute Control Mode Modules..." << std::endl;
    ui.quit();
    camera.quit();
    remoteController.quit();
    vehicleController.quit();
}
