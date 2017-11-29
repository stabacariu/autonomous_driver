/**
 * @file remote_control.cpp
 * @author Sergiu-Petru Tabacariu
 * @date 11.10.2017
 */

#include "remote_control.hpp"

using namespace std;
using namespace cv;

void *remoteControl (void *arg)
{
    cout << "THREAD: Remote control started." << endl;
    
    char key = -1;
    setAcceleration(50);
    setSteering(CV_PI/2);
    
    while ((getModuleState() & MODULE_CONTROL_REMOTE) == MODULE_CONTROL_REMOTE) {
        char prevKey = key;
        key = getUiInputKey();
        
        double acceleration = getAcceleration();
        double steering = getSteering();
        
        if (acceleration == 0) {
            acceleration = 50;
        }
        
        if (prevKey != key) {
            // Set acceleration from 0 to 100 %
            if (key == 'w') {
                acceleration += 0.5;
            }
            else if (key == 's') {
                acceleration -= 0.5;
            }
            // Stop vehicle
            else if (key == ' ') {
                acceleration = getAcceleration();
                if (acceleration >= 60) {
                    acceleration = 0;
                }
                else {
                    acceleration = 50;
                }
            }
            if (acceleration < 0) {
                acceleration = 25;
            }
            else if (acceleration > 100) {
                acceleration = 75;
            }
            
            // Set steering from 0 to CV_PI rad
            if (key == 'a') {
                steering -= CV_PI/4;
            }
            else if (key == 'd') {
                steering += CV_PI/4;
            }
            
            if (steering < 0) {
                steering = 0;
            }
            else if (steering > CV_PI) {
                steering = CV_PI;
            }
            
            setAcceleration(acceleration);
            setSteering(steering);
        }
    }
    
    cout << "THREAD: Remote control ended." << endl;
    return NULL;
}
