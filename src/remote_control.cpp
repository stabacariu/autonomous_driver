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
    
    while ((getModuleState() & MODULE_CONTROL_REMOTE) == MODULE_CONTROL_REMOTE) {
        char key = getUiInputKey();
        
        // Increase acceleration
        if (key == 'w') {
            setAcceleration(getAcceleration() + 10);
        }
        // Decrease acceleration
        else if (key == 's') {
            setAcceleration(getAcceleration() - 10);
        }
        else if (key == 'a') {
            setSteering(getSteering() + 5);
        }
        else if (key == 'd') {
            setSteering(getSteering() + 5);
        }
    }
    
    cout << "THREAD: Remote control ended." << endl;
    return NULL;
}
