/**
 * @file vehicle_control.cpp
 * @author Sergiu-Petru Tabcariu
 * @date 3.7.2017
 */

#include "vehicle_control.hpp"

void VehicleControler::start (VehicleData& vehicle)
{
    std::cout << "THREAD: Vehicle control started." << std::endl;
    
    MotorDriver motor;
    
    while (running) {
        // Calculate steering value from rad to a value from 0 to 4096
        double steering = vehicle.getSteering();
        int steeringValue = (int) round(STEERING_MIN + steering/((double) CV_PI/(STEERING_MAX - STEERING_MIN)));
        motor.setSteering(steeringValue);

        // Calculate acceleration value from percent to value from 0 to 4096
        double acceleration = vehicle.getAcceleration();
        int accelerationValue = (int) round(ESC_N + acceleration/((double) 100/(ESC_N - ESC_MIN)));
        motor.setAcceleration(accelerationValue);
    }

    motor.reset();

    std::cout << "THREAD: Vehicle control ended." << std::endl;
}

void VehicleControler::stop ()
{
    running = false;
}

bool VehicleControler::isRunning ()
{
    return running;
}
