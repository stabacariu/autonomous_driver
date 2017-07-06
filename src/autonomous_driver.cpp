/**
 * @file autonomous_driver.cpp
 * @author Sergiu-Petru Tabacariu
 * @date 27.6.2017
 * 
 * @brief This programm holds all functions to demonstrate an autonmous
 * driving car.
 */
 
#include "autonomous_driver.hpp"
 
SystemState systemState;

 using namespace std;
 
void systemStateInit (void)
{
    pthread_mutex_init(&systemState.lock, NULL);
    setSystemState(SYS_MODE_STANDBY);
}

void setSystemState (SystemMode state)
{
    if (pthread_mutex_lock(&systemState.lock)) {
        cerr << "ERROR: Couldn't lock status mutex!" << endl;
    }
    
    systemState.mode = state;
    
    if (pthread_mutex_unlock(&systemState.lock)) {
        cerr << "ERROR: Couldn't unlock status mutex!" << endl;
    }
}

SystemMode getSystemState (void)
{
    SystemMode state;
    
    if (pthread_mutex_lock(&systemState.lock)) {
        cerr << "ERROR: Couldn't lock status mutex!" << endl;
    }
    
    state = systemState.mode;
    
    if (pthread_mutex_unlock(&systemState.lock)) {
        cerr << "ERROR: Couldn't unlock status mutex!" << endl;
    }
    
    return state;
}
