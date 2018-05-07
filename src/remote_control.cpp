/**
 * @file remote_control.cpp
 * @author Sergiu-Petru Tabacariu
 * @date 11.10.2017
 */

#include "remote_control.hpp"

void RemoteControler::run (VehicleData& vehicle, UserInterfaceState& uiState)
{
    std::cout << "THREAD: Remote control started." << std::endl;
    running = true;
    
    char key = (char)(-1);
    vehicle.setAcceleration(0);
    vehicle.setSteering(CV_PI/2);
    
    while (running) {
        char prevKey = key;
        key = uiState.getKey();
        
        double prevAcceleration = vehicle.getAcceleration();
        double prevSteering = vehicle.getSteering();
        
        if (prevKey != key) {
            double acceleration = prevAcceleration;
            double steering = prevSteering;
            
            // Set acceleration from 0 to 100 %
            if (key == 'w') {
                acceleration += 0.5;
            }
            else if (key == 's') {
                acceleration -= 0.5;
            }
            // Stop vehicle
            //!< @note Add proper braking function
            else if (key == ' ') {
                acceleration = 0;
            }
            
            if (acceleration < (-30)) {
                acceleration = -30;
            }
            else if (acceleration > 30) {
                acceleration = 30;
            }
            
            // Set steering from 0 to pi
            if (key == 'a') {
                steering -= CV_PI/8;
            }
            else if (key == 'd') {
                steering += CV_PI/8;
            }
            
            if (steering < (CV_PI/4)) {
                steering = (CV_PI/4);
            }
            else if (steering > (3*CV_PI/4)) {
                steering = (3*CV_PI/4);
            }
            
            if (prevAcceleration != acceleration) {
                std::cout << "Actual acceleration: " << acceleration << " %" << std::endl;
                vehicle.setAcceleration(acceleration);
            }
            if (prevSteering != steering) {
                if (prevSteering != steering) 
                std::cout << "Actual steering angle: " << steering << " rad" << std::endl;
                vehicle.setSteering(steering);
            }
        }
    }
    
    std::cout << "THREAD: Remote control ended." << std::endl;
}

void RemoteControler::quit ()
{
    running = false;
}

bool RemoteControler::isRunning ()
{
    return running;
}
