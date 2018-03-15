/**
 * @file vehicle_control.cpp
 * @author Sergiu-Petru Tabcariu
 * @date 3.7.2017
 */

#include "vehicle_control.hpp"

void *vehicleControl (void* arg)
{
    std::cout << "THREAD: Vehicle control started." << std::endl;

    initVehicle();
    initMotorDriver();

    while ((getModuleState() & MODULE_CONTROL_VEHICLE) == MODULE_CONTROL_VEHICLE) {
        // Calculate steering value from rad to a value from 0 to 4096
        double steering = getSteering();
        int steeringValue = (int) round(STEERING_MIN + steering/((double) CV_PI/(STEERING_MAX - STEERING_MIN)));
        setSteeringMotorValue(steeringValue);

        // Calculate acceleration value from percent to value from 0 to 4096
        double acceleration = getAcceleration();
        int accelerationValue = (int) round(ESC_N + acceleration/((double) 100/(ESC_N - ESC_MIN)));
        setAccelerationMotorValue(accelerationValue);
    }

    resetMotorDriver();

    std::cout << "THREAD: Vehicle control ended." << std::endl;
    return NULL;
}
