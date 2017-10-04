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
        // Get steering angle and set steering motor direction
        double steering = getSteering();
        int steeringValue = (int) round(STEERING_MIN + steering/((double) CV_PI/(STEERING_MAX - STEERING_MIN)));
        setSteeringValue(steeringValue);
        
        // Get acceleration 
        double acceleration = getAcceleration();
        int accelerationValue = (int) round(ESC_MIN + acceleration/((double) 100/(ESC_MAX - ESC_MIN)));
        setAccelerationValue(accelerationValue);
        
        cout << "STRG: " << steering << "° PWM: " << steeringValue << " ACL: " << acceleration << "% PWM: " << accelerationValue << endl;
    }
    cout  << endl;
    resetMotorDriver();
    
    cout << "Thread: Vehicle control ended." << endl;
    return NULL;
}
