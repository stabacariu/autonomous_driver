/**
 * @file remote_control_mode.cpp
 * @author Sergiu-Petru Tabacariu
 * @date 5.4.2018
 */

#include "remote_control_mode.hpp"
#include "closing_mode.hpp"
#include "standby_mode.hpp"
#include "autonomous_mode.hpp"
#include "ui_remote_control_mode.hpp"

void RemoteControlMode::start (SystemState* s)
{
    std::cout << "---------------------------------" << std::endl;
    std::cout << "Remote Control System Mode started." << std::endl;
    running = true;
    
    uiState.setMode(new UIRemoteControlMode(vehicle));
    std::thread uiShowThread(&UserInterface::start, &ui, std::ref(inputImage), std::ref(uiState));
    std::thread uiInputThread(&UserInterface::consoleInput, &ui, std::ref(uiState));
    std::thread imageAcquisitionThread(&CameraImageAcquisitor::start, &camera, std::ref(inputImage));
    std::thread remoteControlThread(&RemoteControler::start, &remoteControler, std::ref(vehicle), std::ref(uiState));
    std::thread vehicleControlThread(&VehicleControler::start, &vehicleControler, std::ref(vehicle));
    
    char key = (char)(-1);
    
    // Process user input
    while (running) {
        key = uiState.getKey();
        if ((key == 27) ||
            (key == 'q') ||
            (key == 'Q') ||
            (key == 'B') ||
            (key == 'A')) {
            running = false;
        }
    }
    stop();
    
    uiShowThread.join();
    uiInputThread.join();
    imageAcquisitionThread.join();
    remoteControlThread.join();
    vehicleControlThread.join();
        
    switch (key) {
        case 27: s->setMode(new ClosingMode()); break;
        case 'q': s->setMode(new ClosingMode()); break;
        case 'Q': s->setMode(new ClosingMode()); break;
        case 'B': s->setMode(new StandbyMode()); break;
        case 'A': s->setMode(new AutonomousMode()); break;
    }
    delete this;
}

void RemoteControlMode::stop ()
{
    stopModules();
    std::cout << "Remote Control System Mode stopped." << std::endl;
    running = false;
}

void RemoteControlMode::stopModules ()
{
    std::cout << "MODE: Quiting Remoute Control Mode Modules..." << std::endl;
    ui.stop();
    camera.stop();
    remoteControler.stop();
    vehicleControler.stop();
}
