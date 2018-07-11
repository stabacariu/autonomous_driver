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
#include "ui_calibration_mode.hpp"

void IntrinsicsCalibrationMode::run (SystemState* s)
{
    std::cout << "---------------------------------" << std::endl;
    std::cout << "MODE: Intrinsics Calibration Mode started." << std::endl;
    running = true;
    
    uiState.setMode(new UIIntrinsicsCalibrationMode());
    std::thread uiShowThread(&UserInterface::run, &ui, std::ref(outputImage), std::ref(uiState));
    
    std::thread imageAcquisitionThread(&CameraImageAcquisitor::run, &camera, std::ref(inputImage));
    std::thread calibrationThread(&CameraImageAcquisitor::runIntrinsicCalibration, &camera, std::ref(inputImage), std::ref(outputImage), std::ref(uiState));
    
    char key = (char)(-1);
    
    // Process user input
    while (running) {
        key = uiState.getKey();
        if ((key == 27) ||
            (key == 'q') ||
            (key == 'Q') ||
            (key == 'B')) {
            running = false;
        }
    }
    quit();
    
    uiShowThread.join();
    
    imageAcquisitionThread.join();
    calibrationThread.join();
    
    switch (key) {
        case 27: s->setMode(new ClosingMode()); break;
        case 'q': s->setMode(new ClosingMode()); break;
        case 'Q': s->setMode(new ClosingMode()); break;
        case 'B': s->setMode(new ConfigurationMode()); break;
    }
    delete this;
}

void IntrinsicsCalibrationMode::quit ()
{
    stopModules();
    running = false;
    std::cout << "MODE: Quitting Intrinsics Calibration Mode..." << std::endl;
}

void IntrinsicsCalibrationMode::stopModules ()
{
    std::cout << "MODE: Quiting Intrinsics Calibration System Mode Modules..." << std::endl;
    ui.quit();
    camera.quit();
}


void ExtrinsicsCalibrationMode::run (SystemState* s)
{
    std::cout << "---------------------------------" << std::endl;
    std::cout << "MODE: Extrinsics Calibration Mode started." << std::endl;
    running = true;
    
    uiState.setMode(new UIExtrinsicsCalibrationMode());
    std::thread uiShowThread(&UserInterface::run, &ui, std::ref(outputImage), std::ref(uiState));
    std::thread imageAcquisitionThread(&CameraImageAcquisitor::run, &camera, std::ref(inputImage));
    std::thread calibrationThread(&CameraImageAcquisitor::runExtrinsicCalibration, &camera, std::ref(inputImage), std::ref(outputImage), std::ref(uiState));
        
    char key = (char)(-1);
    
    // Process user input
    while (running) {
        key = uiState.getKey();
        if ((key == 27) ||
            (key == 'q') ||
            (key == 'Q') ||
            (key == 'B')) {
            running = false;
        }
    }
    quit();
    
    uiShowThread.join();
    imageAcquisitionThread.join();
    calibrationThread.join();
    
    switch (key) {
        case 27: s->setMode(new ClosingMode()); break;
        case 'q': s->setMode(new ClosingMode()); break;
        case 'Q': s->setMode(new ClosingMode()); break;
        case 'B': s->setMode(new ConfigurationMode()); break;
    }
    delete this;
}

void ExtrinsicsCalibrationMode::quit ()
{
    stopModules();
    running = false;
    std::cout << "MODE: Quitting Extrinsics Calibration Mode..." << std::endl;
}

void ExtrinsicsCalibrationMode::stopModules ()
{
    std::cout << "MODE: Quiting Extrinsics Calibration System Mode Modules..." << std::endl;
    ui.quit();
    camera.quit();
}

void ImageAdjustmentMode::run (SystemState* s)
{
    std::cout << "---------------------------------" << std::endl;
    std::cout << "MODE: Image Adjustment Mode started." << std::endl;
    running = true;
    
    uiState.setMode(new UIImageAdjustmentMode());
    std::thread uiShowThread(&UserInterface::run, &ui, std::ref(outputImage), std::ref(uiState));
    std::thread imageAcquisitionThread(&CameraImageAcquisitor::run, &camera, std::ref(inputImage));
    //~ std::thread calibrationThread(&CameraImageAcquisitor::runImageAdjustment, &camera, std::ref(inputImage), std::ref(outputImage), std::ref(uiState));
      
    char key = (char)(-1);
    
    // Process user input
    while (running) {
        key = uiState.getKey();
        if ((key == 27) ||
            (key == 'q') ||
            (key == 'Q') ||
            (key == 'B')) {
            running = false;
        }
    }
    quit();
    
    uiShowThread.join();
    imageAcquisitionThread.join();
    //~ calibrationThread.join();
    
    switch (key) {
        case 27: s->setMode(new ClosingMode()); break;
        case 'q': s->setMode(new ClosingMode()); break;
        case 'Q': s->setMode(new ClosingMode()); break;
        case 'B': s->setMode(new ConfigurationMode()); break;
    }
    delete this;
}

void ImageAdjustmentMode::quit ()
{
    stopModules();
    running = false;
    std::cout << "MODE: Quitting Image Adjustment Mode..." << std::endl;
}

void ImageAdjustmentMode::stopModules ()
{
    std::cout << "MODE: Quiting Image Adjustment System Mode Modules..." << std::endl;
    ui.quit();
    camera.quit();
}
