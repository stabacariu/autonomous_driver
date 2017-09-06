/**
 * @file vehicle_control.cpp
 * @author Sergiu-Petru Tabcariu
 * @date 3.7.2017
 */

#include "vehicle_control.hpp"

using namespace std;

void *vehicleControl (void* arg)
{
    cout << "Thread: Vehicle control started." << endl;
    
    initVehicle();
    initMotorDriver();
    
    while ((getModuleState() & MODULE_CONTROL_VEHICLE) == MODULE_CONTROL_VEHICLE) {
        // TODO: Check vehicle state and manipulate steering and speed
        double steering = getSteering();
        int value = (int) round(STEERING_MIN + steering / (CV_PI/(STEERING_MAX-STEERING_MIN)));
        cout << "Steering angle: " << steering << " PWM value: " << value << endl;
        
        setSteeringValue(value);
    }
    
    resetMotorDriver();
    
    cout << "Thread: Vehicle control ended." << endl;
    return NULL;
}
