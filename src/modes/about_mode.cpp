/**
 * @file about_mode.hpp
 * @author Sergiu-Petru Tabacariu
 * @date 5.4.2018
 */

#include "about_mode.hpp"
#include "closing_mode.hpp"
#include "standby_mode.hpp"
#include "ui_about_mode.hpp"

void AboutMode::run (SystemState* s)
{
    std::cout << "---------------------------------" << std::endl;
    std::cout << "MODE: About Mode started." << std::endl;
    running = true;
    
    uiState.setMode(new UIAboutMode());
    std::thread uiShow(&UserInterface::run, &ui, std::ref(outputImage), std::ref(uiState));
        
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
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }
    quit();
    
    uiShow.join();
    
    switch (key) {
        case 27: s->setMode(new ClosingMode()); break;
        case 'q': s->setMode(new ClosingMode()); break;
        case 'Q': s->setMode(new ClosingMode()); break;
        case 'B': s->setMode(new StandbyMode()); break;
    }
    delete this;
}

void AboutMode::quit ()
{
    stopModules();
    std::cout << "MODE: Quitting about mode..." << std::endl;
    running = false;
}

void AboutMode::stopModules ()
{
    std::cout << "MODE: Stopping all modules..." << std::endl;
    ui.quit();
}
