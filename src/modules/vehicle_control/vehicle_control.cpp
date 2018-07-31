/**
 * @file vehicle_control.cpp
 * @author Sergiu-Petru Tabcariu
 * @date 3.7.2017
 */

#include "vehicle_control.hpp"
#include "configuration.hpp"
#include "camera_image_acquisitor.hpp"
#include "lane_detection.hpp"

void VehicleController::run (TrajectoryData& trajectory, VehicleModel& vehicle)
{
    std::cout << "THREAD: Vehicle control started." << std::endl;
    running = true;
    
    Configurator& config = Configurator::instance();
    CameraConfig camConfig = config.getCameraConfig();
    
    MotorDriver motor;
    bool motorInitFlag = motor.init();
    
    while (running && motorInitFlag) {
        if (vehicle.checkStop()) {
            motor.stop();
        }
        
        float theta = 0;
        bool drv = false;
        int diffX1 = 0;
        int diffX2 = 0;
        
        // Convert Trajectory to steering and acceleration values
        if (trajectory.size() == 2) {
            diffX1 = trajectory.at(0).x - (camConfig.imageSize.width/2-1); // If result positive then lane is to much to the right. Car must steer to the right.
            diffX2 = trajectory.at(1).x - (camConfig.imageSize.width/2-1);
            
            theta = getTheta(trajectory.at(0), trajectory.at(1));
            drv = true;
        }
        
        double acVal = 18; // 59% if 100% full forward and 0% full reverse
        double brVal = 0; // 50% if 100% full forward and 0% full reverse
        
        if ((theta < (CV_PI*0.1)) || (theta > (CV_PI*0.9))) {
            vehicle.setAcceleration(brVal);
        }
        else if (drv) {
            // Set steering angle
            if ((theta > 0) && (theta < CV_PI/2*0.9)) {
                vehicle.setDirection(VehicleDirection::VEHICLE_LEFT);
                vehicle.setSteering(theta-CV_PI/8);
            }
            else if ((theta < CV_PI) && (theta > CV_PI/2*1.1)) {
                vehicle.setDirection(VehicleDirection::VEHICLE_RIGHT);
                vehicle.setSteering(theta+CV_PI/8);
            }
            else {
                vehicle.setDirection(VehicleDirection::VEHICLE_STRAIGHT);
                vehicle.setSteering(theta);
            }
            
            // Set acceleration percentage
            // Vehicle is too much to the left
            // Counter steer to the right
            if ((diffX2 > 10) && (diffX1 > 10)) {
                vehicle.setSteering(3*CV_PI/4);
                vehicle.setAcceleration(acVal-0.5);
            }
            // Vehicle is too much to the right
            // Counter steer to the left
            else if ((diffX2 < -10) && (diffX1 < -10)) {
                vehicle.setSteering(CV_PI/4);
                vehicle.setAcceleration(acVal-0.5);
            }
            else {
                vehicle.setAcceleration(acVal);
            }
        }
        
        // Calculate steering value from rad to a value from 0 to 4096
        double steering = vehicle.getSteering();
        int steeringValue = (int) round(STEERING_MIN + steering/((double) CV_PI/(STEERING_MAX - STEERING_MIN)));
        motor.setSteering(steeringValue);

        // Calculate acceleration value from percent to value from 0 to 4096
        double acceleration = vehicle.getAcceleration();
        int accelerationValue = (int) round(ESC_N + acceleration/((double) 100/(ESC_N - ESC_MIN)));
        motor.setAcceleration(accelerationValue);
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    motor.reset();

    std::cout << "THREAD: Vehicle control ended." << std::endl;
}

void VehicleController::quit ()
{
    running = false;
}

bool VehicleController::isRunning ()
{
    return running;
}
