/**
 * @file about_mode.hpp
 * @author Sergiu-Petru Tabacariu
 * @date 5.4.2018
 */

#include "about_mode.hpp"
#include "closing_mode.hpp"
#include "standby_mode.hpp"

void AboutMode::start (SystemState* s)
{
    std::cout << "---------------------------------" << std::endl;
    std::cout << "MODE: About Mode started." << std::endl;
    
    std::thread uiShow(&UserInterface::start, &ui, std::ref(outputImage), std::ref(uiData));
    std::thread uiInput(&UserInterface::consoleInput, &ui, std::ref(uiData));
    
    char key = (char)(-1);
    
    // Process user input
    while (running) {
        key = uiData.getKey();
        if ((key == 27) ||
            (key == 'q') ||
            (key == 'b')) {
            running = false;
        }
        
    }
    stop();
    
    uiShow.join();
    uiInput.join();
    
    switch (key) {
        case 27: s->setMode(new ClosingMode()); break;
        case 'q': s->setMode(new ClosingMode()); break;
        case 'b': s->setMode(new StandbyMode()); break;
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
