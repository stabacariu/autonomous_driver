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
    if (!motor.init()) {
        error = true;
        running = false;
    }
    
    while (running && !error) {
        if (vehicle.checkStop()) {
            motor.reset();
        }
        
        cv::Vec4i tLine = trajectory.getLine();
        std::vector<cv::Point> tPoints = trajectory.get();
        if (trajectory.active) {
            // Convert Trajectory to steering and acceleration values
            float theta = 0;
            int diffX1 = 0;
            int diffX2 = 0;
            
            double acVal = 19;
            double brVal = 0;
            
            theta = getTheta(cv::Point(tLine[0], tLine[1]), cv::Point(tLine[2], tLine[3]));
            
            if ((theta < (CV_PI*0.1)) || (theta > (CV_PI*0.9))) {
                vehicle.setAcceleration(brVal);
            }
            else {
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
                
                diffX1 = tLine[0] - (camConfig.imageSize.width/2-1); // If result positive then lane is to much to the right. Car must steer to the right.
                diffX2 = tLine[2] - (camConfig.imageSize.width/2-1);
                //~ diffX1 = tPoints.front().x - (camConfig.imageSize.width/2-1); // If result positive then lane is to much to the right. Car must steer to the right.
                //~ diffX2 = tPoints.back().x - (camConfig.imageSize.width/2-1);
                
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
        }
        
        // Calculate steering value from rad to a value from 0 to 4096
        double steering = vehicle.getSteering();
        int steeringValue = (int) round(STEERING_MIN + steering/((double) CV_PI/(STEERING_MAX - STEERING_MIN)));
        motor.setSteering(steeringValue);

        // Calculate acceleration value from percent to value from 0 to 4096
        double acceleration = vehicle.getAcceleration();
        int accelerationValue = (int) round(ESC_N + acceleration/((double) 100/(ESC_N - ESC_MIN)));
        motor.setAcceleration(accelerationValue);
        //~ std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }

    motor.reset();

    std::cout << "THREAD: Vehicle control ended." << std::endl;
}
