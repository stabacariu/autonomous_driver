/**
 * @file standby_mode.cpp
 * @author Sergiu-Petru Tabacariu
 * @date 5.4.2018
 */

#include "standby_mode.hpp"
#include "closing_mode.hpp"
#include "autonomous_mode.hpp"
#include "remote_control_mode.hpp"
#include "configuration_mode.hpp"
#include "about_mode.hpp"
#include "ui_standby_mode.hpp"

void StandbyMode::start (SystemState* s)
{
    std::cout << "---------------------------------" << std::endl;
    std::cout << "MODE: Standby Mode started." << std::endl;
    running = true;
    
    uiState.setMode(new UIStandbyMode());
    std::thread uiShowThread(&UserInterface::start, &ui, std::ref(inputImage), std::ref(uiState));
    std::thread uiInputThread(&UserInterface::consoleInput, &ui, std::ref(uiState));
    std::thread imageAcquisitionThread(&CameraImageAcquisitor::start, &camera, std::ref(inputImage));
    
    char key = (char)(-1);
    
    // Process user input
    while (running) {
        key = uiState.getKey();
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
    
    switch (key) {
        case 27: s->setMode(new ClosingMode()); break;
        case 'q': s->setMode(new ClosingMode()); break;
        case 'a': s->setMode(new AutonomousMode()); break;
        case 'r': s->setMode(new RemoteControlMode()); break;
        case 'c': s->setMode(new ConfigurationMode()); break;
        case 's': s->setMode(new AboutMode()); break;
    }
    delete this;
}

void StandbyMode::stop ()
{
    stopModules();
    running = false;
    std::cout << "MODE: Standby Mode stopped." << std::endl;
}

void StandbyMode::stopModules ()
{
    std::cout << "MODE: Quiting Standby System Mode Modules..." << std::endl;
    ui.stop();
    camera.stop();
}
