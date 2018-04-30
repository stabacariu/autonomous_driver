/**
 * @file remote_control_mode.cpp
 * @author Sergiu-Petru Tabacariu
 * @date 5.4.2018
 */

#include "remote_control_mode.hpp"
#include "closing_mode.hpp"
#include "standby_mode.hpp"

void RemoteControlMode::start (SystemState* s)
{
    std::cout << "---------------------------------" << std::endl;
    std::cout << "Remote Control System Mode started." << std::endl;
    running = true;
    
    std::thread uiShowThread(&UserInterface::start, &ui, std::ref(inputImage), std::ref(uiData));
    std::thread uiInputThread(&UserInterface::consoleInput, &ui, std::ref(uiData));
    std::thread imageAcquisitionThread(&CameraImageAcquisitor::start, &camera, std::ref(inputImage));
    std::thread remoteControlThread(&RemoteControler::start, &remoteControl, std::ref(vehicle), std::ref(uiData));
    
    char key = (char)(-1);
    
    // Process user input
    while (running) {
        key = uiData.getKey();
        if ((key == 27) ||
            (key == 'q') ||
            (key == 'a') ||
            (key == 'r') ||
            (key == 'c') ||
            (key == 's')) {
            running = false;
        }
        
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
    stop();
    
    uiShowThread.join();
    uiInputThread.join();
    imageAcquisitionThread.join();
    remoteControlThread.join();
        
    switch (key) {
        case 27: s->setMode(new ClosingMode()); break;
        case 'q': s->setMode(new ClosingMode()); break;
        case 'b': s->setMode(new StandbyMode()); break;
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
    remoteControl.stop();
}
