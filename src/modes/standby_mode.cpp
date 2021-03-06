/**
 * @file standby_mode.cpp
 * @author Sergiu-Petru Tabacariu
 * @date 5.4.2018
 */

#include "standby_mode.hpp"
#include "closing_mode.hpp"
#include "error_mode.hpp"
#include "autonomous_mode.hpp"
#include "development_mode.hpp"
#include "remote_control_mode.hpp"
#include "configuration_mode.hpp"
#include "about_mode.hpp"
#include "ui_standby_mode.hpp"

void StandbyMode::run (SystemState* s)
{
    std::cout << "---------------------------------" << std::endl;
    std::cout << "MODE: Standby Mode started." << std::endl;
    running = true;
  
    uiState.setMode(new UIStandbyMode());
    std::thread uiShowThread(&UserInterface::run, &ui, std::ref(inputImage), std::ref(uiState));
    std::thread imageAcquisitionThread(&CameraImageAcquisitor::run, &camera, std::ref(inputImage));
    
    char key = (char)(-1);
        
    while (running && !error) {
        // Check valid user input
        key = uiState.getKey();
        if ((key == 27) ||
            (key == 'q') ||
            (key == 'Q') ||
            (key == 'A') ||
            (key == 'D') ||
            (key == 'R') ||
            (key == 'C') ||
            (key == 'B')) {
            running = false;
        }
        
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
        
        // Check for module error
        if (ui.isError() ||
            camera.isError()) {
            error = true;
            running = false;
        }
    }
    quit();
    
    uiShowThread.join();
    imageAcquisitionThread.join();
    
    if (error) {
        s->setMode(new ErrorMode());
    }
    else {
        switch (key) {
            case 27: s->setMode(new ClosingMode()); break;
            case 'q': s->setMode(new ClosingMode()); break;
            case 'Q': s->setMode(new ClosingMode()); break;
            case 'A': s->setMode(new AutonomousMode()); break;
            case 'D': s->setMode(new DevelopmentMode()); break;
            case 'R': s->setMode(new RemoteControlMode()); break;
            case 'C': s->setMode(new ConfigurationMode()); break;
            case 'B': s->setMode(new AboutMode()); break;
            default: s->setMode(new ErrorMode()); break;
        }
    }
    delete this;
}

void StandbyMode::quit ()
{
    stopModules();
    running = false;
    std::cout << "MODE: Quitting standby mode..." << std::endl;
}

void StandbyMode::stopModules ()
{
    std::cout << "MODE: Quiting Standby System Mode Modules..." << std::endl;
    ui.quit();
    camera.quit();
}
