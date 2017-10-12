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
        // Calculate steering value from rad to a value from 0 to 4096
        double steering = getSteering();
        int steeringValue = (int) round(STEERING_MIN + steering/((double) CV_PI/(STEERING_MAX - STEERING_MIN)));
        setSteeringValue(steeringValue);
        
        // Calculate acceleration value from percent to value from 0 to 4096
        double acceleration = getAcceleration();
        int accelerationValue = (int) round(ESC_MIN + acceleration/((double) 100/(ESC_MAX - ESC_MIN)));
        setAccelerationValue(accelerationValue);
    }
    
    resetMotorDriver();
    
    cout << "Thread: Vehicle control ended." << endl;
    return NULL;
}
