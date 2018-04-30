/**
 * @file calibration_mode.cpp
 * @author Sergiu-Petru Tabacariu
 * @date 25.4.2018
 */

#include "calibration_mode.hpp"
#include "closing_mode.hpp"
#include "autonomous_mode.hpp"
#include "remote_control_mode.hpp"
#include "configuration_mode.hpp"

void IntrinsicsCalibrationMode::start (SystemState* s)
{
    std::cout << "---------------------------------" << std::endl;
    std::cout << "MODE: Intrinsics Calibration Mode started." << std::endl;
    running = true;
    
    std::thread uiShowThread(&UserInterface::start, &ui, std::ref(outputImage), std::ref(uiData));
    std::thread uiInputThread(&UserInterface::consoleInput, &ui, std::ref(uiData));
    std::thread imageAcquisitionThread(&CameraImageAcquisitor::start, &camera, std::ref(inputImage));
    std::thread calibrationThread(&CameraImageAcquisitor::runIntrinsicCalibration, &camera, std::ref(inputImage), std::ref(outputImage));
    
    char key = (char)(-1);
    
    // Process user input
    while (running) {
        key = uiData.getKey();
        if ((key == 27) ||
            (key == 'q') ||
            (key == 'b') ||
            (key == 's')) {
            running = false;
        }
        
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
    stop();
    
    uiShowThread.join();
    uiInputThread.join();
    imageAcquisitionThread.join();
    calibrationThread.join();
    
    switch (key) {
        case 27: s->setMode(new ClosingMode()); break;
        case 'q': s->setMode(new ClosingMode()); break;
        case 'b': s->setMode(new ConfigurationMode()); break;
        case 's': /* Save data */; break;
    }
    delete this;
}

void IntrinsicsCalibrationMode::stop ()
{
    stopModules();
    running = false;
    std::cout << "MODE: Intrinsics Calibration Mode stopped." << std::endl;
}

void IntrinsicsCalibrationMode::stopModules ()
{
    std::cout << "MODE: Quiting Intrinsics Calibration System Mode Modules..." << std::endl;
    ui.stop();
    camera.stop();
}


void ExtrinsicsCalibrationMode::start (SystemState* s)
{
    std::cout << "---------------------------------" << std::endl;
    std::cout << "MODE: Extrinsics Calibration Mode started." << std::endl;
    running = true;
    
    std::thread uiShowThread(&UserInterface::start, &ui, std::ref(outputImage), std::ref(uiData));
    std::thread uiInputThread(&UserInterface::consoleInput, &ui, std::ref(uiData));
    std::thread imageAcquisitionThread(&CameraImageAcquisitor::start, &camera, std::ref(inputImage));
    std::thread calibrationThread(&CameraImageAcquisitor::runIntrinsicCalibration, &camera, std::ref(inputImage), std::ref(outputImage));
        
    char key = (char)(-1);
    
    // Process user input
    while (running) {
        key = uiData.getKey();
        if ((key == 27) ||
            (key == 'q') ||
            (key == 'b') ||
            (key == 's')) {
            running = false;
        }
        
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
    stop();
    
    uiShowThread.join();
    uiInputThread.join();
    imageAcquisitionThread.join();
    calibrationThread.join();
    
    switch (key) {
        case 27: s->setMode(new ClosingMode()); break;
        case 'q': s->setMode(new ClosingMode()); break;
        case 'b': s->setMode(new ConfigurationMode()); break;
        case 's': /* Save data */; break;
    }
    delete this;
}

void ExtrinsicsCalibrationMode::stop ()
{
    stopModules();
    running = false;
    std::cout << "MODE: Extrinsics Calibration Mode stopped." << std::endl;
}

void ExtrinsicsCalibrationMode::stopModules ()
{
    std::cout << "MODE: Quiting Extrinsics Calibration System Mode Modules..." << std::endl;
    ui.stop();
    camera.stop();
}
