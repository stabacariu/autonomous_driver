/**
 * @file configuration_mode.cpp
 * @author Sergiu-Petru Tabacariu
 * @date 5.4.2018
 */

#include "configuration_mode.hpp"
#include "closing_mode.hpp"
#include "standby_mode.hpp"
#include "calibration_mode.hpp"
#include "ui_configuration_mode.hpp"

void ConfigurationMode::start (SystemState* s)
{
    std::cout << "---------------------------------" << std::endl;
    std::cout << "MODE: Configuration Mode started." << std::endl;
    running = true;
    
    uiState.setMode(new UIConfigurationMode());
    std::thread uiShowThread(&UserInterface::start, &ui, std::ref(inputImage), std::ref(uiState));
    std::thread uiInputThread(&UserInterface::consoleInput, &ui, std::ref(uiState));
    std::thread imageAcquisitionThread(&CameraImageAcquisitor::start, &camera, std::ref(inputImage));
    
    char key = (char)(-1);
    
    // Process user input
    while (running) {
        key = uiState.getKey();
        if ((key == 27) ||
            (key == 'q') ||
            (key == 'Q') ||
            (key == 'B') ||
            (key == 'I') ||
            (key == 'E')) {
            running = false;
        }
    }
    stop();
    
    uiShowThread.join();
    uiInputThread.join();
    imageAcquisitionThread.join();
    
    switch (key) {
        case 27: s->setMode(new ClosingMode()); break;
        case 'q': s->setMode(new ClosingMode()); break;
        case 'Q': s->setMode(new ClosingMode()); break;
        case 'B': s->setMode(new StandbyMode()); break;
        case 'I': s->setMode(new IntrinsicsCalibrationMode()); break;
        case 'E': s->setMode(new ExtrinsicsCalibrationMode()); break;
    }
    delete this;
}

void ConfigurationMode::stop ()
{
    stopModules();
    running = false;
    std::cout << "MODE: Configuration Mode stopped." << std::endl;
}

void ConfigurationMode::stopModules ()
{
    std::cout << "MODE: Stopping all modules..." << std::endl;
    ui.stop();
    camera.stop();
}
