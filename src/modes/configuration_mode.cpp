/**
 * @file configuration_mode.cpp
 * @author Sergiu-Petru Tabacariu
 * @date 5.4.2018
 */

#include "configuration_mode.hpp"
#include "closing_mode.hpp"
#include "error_mode.hpp"
#include "standby_mode.hpp"
#include "calibration_mode.hpp"
#include "ui_configuration_mode.hpp"

void ConfigurationMode::run (SystemState* s)
{
    std::cout << "---------------------------------" << std::endl;
    std::cout << "MODE: Configuration Mode started." << std::endl;
    running = true;
    
    uiState.setMode(new UIConfigurationMode());
    std::thread uiShowThread(&UserInterface::run, &ui, std::ref(inputImage), std::ref(uiState));
    std::thread imageAcquisitionThread(&CameraImageAcquisitor::run, &camera, std::ref(inputImage));
    
    char key = (char)(-1);
    
     while (running) {
        //Check for valid user input
        key = uiState.getKey();
        if ((key == 27) ||
            (key == 'q') ||
            (key == 'Q') ||
            (key == 'B') ||
            (key == 'I') ||
            (key == 'E')) {
            running = false;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
        
        // Check for module error
        if (ui.isError() ||
            camera.isError()) {
            running = false;
            error = true;
        }
    }
    quit();
    
    uiShowThread.join();
    imageAcquisitionThread.join();
    
    if (error) {
        s->setMode(new StandbyMode());
    }
    else {
        switch (key) {
            case 27: s->setMode(new ClosingMode()); break;
            case 'q': s->setMode(new ClosingMode()); break;
            case 'Q': s->setMode(new ClosingMode()); break;
            case 'B': s->setMode(new StandbyMode()); break;
            case 'I': s->setMode(new IntrinsicsCalibrationMode()); break;
            case 'E': s->setMode(new ExtrinsicsCalibrationMode()); break;
            //~ case 'P': s->setMode(new ImageAdjustmentMode()); break;
            default: s->setMode(new ErrorMode()); break;
        }
    }
    delete this;
}

void ConfigurationMode::quit ()
{
    stopModules();
    running = false;
    std::cout << "MODE: Configuration Mode stopped." << std::endl;
}

void ConfigurationMode::stopModules ()
{
    std::cout << "MODE: Stopping all modules..." << std::endl;
    ui.quit();
    camera.quit();
}
