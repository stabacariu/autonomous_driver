/**
 * @file vehicle.cpp
 * @author Sergiu-Petru Tabacariu
 * @date 3.7.2017
 */

#include "vehicle.hpp"

Vehicle vehicle;

void initVehicle (void)
{
    pthread_mutex_init(&vehicle.lock, NULL);
}

void setAcceleration (double value)
{
    if (pthread_mutex_lock(&vehicle.lock)) {
        std::cerr << "ERROR: Couldn't lock vehicle mutex!" << std::endl;
    }
    
    vehicle.acceleration = value;
    
    if (pthread_mutex_unlock(&vehicle.lock)) {
        std::cerr << "ERROR: Couldn't unlock vehicle mutex!" << std::endl;
    }
}

double getAcceleration (void)
{
    double value;
    
    if (pthread_mutex_lock(&vehicle.lock)) {
        std::cerr << "ERROR: Couldn't lock vehicle mutex!" << std::endl;
    }
    
    value = vehicle.acceleration;
    
    if (pthread_mutex_unlock(&vehicle.lock)) {
        std::cerr << "ERROR: Couldn't unlock vehicle mutex!" << std::endl;
    }
    
    return value;
}

void setDirection (VehicleDirection value)
{
    if (pthread_mutex_lock(&vehicle.lock)) {
        std::cerr << "ERROR: Couldn't lock vehicle mutex!" << std::endl;
    }
    
    vehicle.direction = value;
    
    if (pthread_mutex_unlock(&vehicle.lock)) {
        std::cerr << "ERROR: Couldn't unlock vehicle mutex!" << std::endl;
    }
}

VehicleDirection getDirection (void)
{
    VehicleDirection value;
    
    if (pthread_mutex_lock(&vehicle.lock)) {
        std::cerr << "ERROR: Couldn't lock vehicle mutex!" << std::endl;
    }
    
    value = vehicle.direction;
    
    if (pthread_mutex_unlock(&vehicle.lock)) {
        std::cerr << "ERROR: Couldn't unlock vehicle mutex!" << std::endl;
    }
    
    return value;
}

void setSpeed (double value)
{
    if (pthread_mutex_lock(&vehicle.lock)) {
        std::cerr << "ERROR: Couldn't lock vehicle mutex!" << std::endl;
    }
    
    vehicle.speed = value;
    
    if (pthread_mutex_unlock(&vehicle.lock)) {
        std::cerr << "ERROR: Couldn't unlock vehicle mutex!" << std::endl;
    }
}

double getSpeed (void)
{
    int value;
    
    if (pthread_mutex_lock(&vehicle.lock)) {
        std::cerr << "ERROR: Couldn't lock vehicle mutex!" << std::endl;
    }
    
    value = vehicle.speed;
    
    if (pthread_mutex_unlock(&vehicle.lock)) {
        std::cerr << "ERROR: Couldn't unlock vehicle mutex!" << std::endl;
    }
    
    return value;
}

void setSteering (double value)
{
    if (pthread_mutex_lock(&vehicle.lock)) {
        std::cerr << "ERROR: Couldn't lock vehicle mutex!" << std::endl;
    }
    
    vehicle.steering = value;
    
    if (pthread_mutex_unlock(&vehicle.lock)) {
        std::cerr << "ERROR: Couldn't unlock vehicle mutex!" << std::endl;
    }
}

double getSteering (void)
{
    double value;
    
    if (pthread_mutex_lock(&vehicle.lock)) {
        std::cerr << "ERROR: Couldn't lock vehicle mutex!" << std::endl;
    }
    
    value = vehicle.steering;
    
    if (pthread_mutex_unlock(&vehicle.lock)) {
        std::cerr << "ERROR: Couldn't unlock vehicle mutex!" << std::endl;
    }
    
    return value;
}

void setWidth (double value)
{
    if (pthread_mutex_lock(&vehicle.lock)) {
        std::cerr << "ERROR: Couldn't lock vehicle mutex!" << std::endl;
    }
    
    vehicle.width = value;
    
    if (pthread_mutex_unlock(&vehicle.lock)) {
        std::cerr << "ERROR: Couldn't unlock vehicle mutex!" << std::endl;
    }
}

double getWidth (void)
{
    int value;
    
    if (pthread_mutex_lock(&vehicle.lock)) {
        std::cerr << "ERROR: Couldn't lock vehicle mutex!" << std::endl;
    }
    
    value = vehicle.width;
    
    if (pthread_mutex_unlock(&vehicle.lock)) {
        std::cerr << "ERROR: Couldn't unlock vehicle mutex!" << std::endl;
    }
    
    return value;
}

void setLength (double value)
{
    if (pthread_mutex_lock(&vehicle.lock)) {
        std::cerr << "ERROR: Couldn't lock vehicle mutex!" << std::endl;
    }
    
    vehicle.lenght = value;
    
    if (pthread_mutex_unlock(&vehicle.lock)) {
        std::cerr << "ERROR: Couldn't unlock vehicle mutex!" << std::endl;
    }
}

double getLenght (void)
{
    int value;
    
    if (pthread_mutex_lock(&vehicle.lock)) {
        std::cerr << "ERROR: Couldn't lock vehicle mutex!" << std::endl;
    }
    
    value = vehicle.lenght;
    
    if (pthread_mutex_unlock(&vehicle.lock)) {
        std::cerr << "ERROR: Couldn't unlock vehicle mutex!" << std::endl;
    }
    
    return value;
}

void setHeight (double value)
{
    if (pthread_mutex_lock(&vehicle.lock)) {
        std::cerr << "ERROR: Couldn't lock vehicle mutex!" << std::endl;
    }
    
    vehicle.height = value;
    
    if (pthread_mutex_unlock(&vehicle.lock)) {
        std::cerr << "ERROR: Couldn't unlock vehicle mutex!" << std::endl;
    }
}

double getHeight(void)
{
    int value;
    
    if (pthread_mutex_lock(&vehicle.lock)) {
        std::cerr << "ERROR: Couldn't lock vehicle mutex!" << std::endl;
    }
    
    value = vehicle.height;
    
    if (pthread_mutex_unlock(&vehicle.lock)) {
        std::cerr << "ERROR: Couldn't unlock vehicle mutex!" << std::endl;
    }
    
    return value;
}

void setWheelbase(double value)
{
    if (pthread_mutex_lock(&vehicle.lock)) {
        std::cerr << "ERROR: Couldn't lock vehicle mutex!" << std::endl;
    }
    
    vehicle.wheelbase = value;
    
    if (pthread_mutex_unlock(&vehicle.lock)) {
        std::cerr << "ERROR: Couldn't unlock vehicle mutex!" << std::endl;
    }
}

double getWheelbase(void)
{
    int value;
    
    if (pthread_mutex_lock(&vehicle.lock)) {
        std::cerr << "ERROR: Couldn't lock vehicle mutex!" << std::endl;
    }
    
    value = vehicle.wheelbase;
    
    if (pthread_mutex_unlock(&vehicle.lock)) {
        std::cerr << "ERROR: Couldn't unlock vehicle mutex!" << std::endl;
    }
    
    return value;
}

void setFrontOverhang(double value)
{
    if (pthread_mutex_lock(&vehicle.lock)) {
        std::cerr << "ERROR: Couldn't lock vehicle mutex!" << std::endl;
    }
    
    vehicle.frontOverhang = value;
    
    if (pthread_mutex_unlock(&vehicle.lock)) {
        std::cerr << "ERROR: Couldn't unlock vehicle mutex!" << std::endl;
    }
}

double getFrontOverhang(void)
{
    int value;
    
    if (pthread_mutex_lock(&vehicle.lock)) {
        std::cerr << "ERROR: Couldn't lock vehicle mutex!" << std::endl;
    }
    
    value = vehicle.frontOverhang;
    
    if (pthread_mutex_unlock(&vehicle.lock)) {
        std::cerr << "ERROR: Couldn't unlock vehicle mutex!" << std::endl;
    }
    
    return value;
}

void setRearOverhang(double value)
{
    if (pthread_mutex_lock(&vehicle.lock)) {
        std::cerr << "ERROR: Couldn't lock vehicle mutex!" << std::endl;
    }
    
    vehicle.rearOverhang = value;
    
    if (pthread_mutex_unlock(&vehicle.lock)) {
        std::cerr << "ERROR: Couldn't unlock vehicle mutex!" << std::endl;
    }
}

double getRearOverhang(void)
{
    int value;
    
    if (pthread_mutex_lock(&vehicle.lock)) {
        std::cerr << "ERROR: Couldn't lock vehicle mutex!" << std::endl;
    }
    
    value = vehicle.rearOverhang;
    
    if (pthread_mutex_unlock(&vehicle.lock)) {
        std::cerr << "ERROR: Couldn't unlock vehicle mutex!" << std::endl;
    }
    
    return value;
}
