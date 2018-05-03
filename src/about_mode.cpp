/**
 * @file about_mode.hpp
 * @author Sergiu-Petru Tabacariu
 * @date 5.4.2018
 */

#include "about_mode.hpp"
#include "closing_mode.hpp"
#include "standby_mode.hpp"
#include "ui_about_mode.hpp"

void AboutMode::start (SystemState* s)
{
    std::cout << "---------------------------------" << std::endl;
    std::cout << "MODE: About Mode started." << std::endl;
    running = true;
    
    uiState.setMode(new UIAboutMode());
    std::thread uiShow(&UserInterface::start, &ui, std::ref(outputImage), std::ref(uiState));
    std::thread uiInput(&UserInterface::consoleInput, &ui, std::ref(uiState));
    
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
    stop();
    
    uiShow.join();
    uiInput.join();
    
    switch (key) {
        case 27: s->setMode(new ClosingMode()); break;
        case 'q': s->setMode(new ClosingMode()); break;
        case 'Q': s->setMode(new ClosingMode()); break;
        case 'B': s->setMode(new StandbyMode()); break;
    }
    delete this;
}

void AboutMode::stop ()
{
    stopModules();
    std::cout << "MODE: About mode stopped." << std::endl;
    running = false;
}

void AboutMode::stopModules ()
{
    std::cout << "MODE: Stopping all modules..." << std::endl;
    ui.stop();
}
