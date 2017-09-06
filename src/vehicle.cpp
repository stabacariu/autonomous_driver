/**
 * @file vehicle.cpp
 * @author Sergiu-Petru Tabacariu
 * @date 3.7.2017
 */

#include "vehicle.hpp"

using namespace std;

Vehicle vehicle;

void initVehicle (void)
{
    pthread_mutex_init(&vehicle.lock, NULL);
}

void setAcceleration (int value)
{
    if (pthread_mutex_lock(&vehicle.lock)) {
        cerr << "ERROR: Couldn't lock vehicle mutex!" << endl;
    }
    
    vehicle.acceleration = value;
    
    if (pthread_mutex_unlock(&vehicle.lock)) {
        cerr << "ERROR: Couldn't unlock vehicle mutex!" << endl;
    }
}

int getAcceleration (void)
{
    int value;
    
    if (pthread_mutex_lock(&vehicle.lock)) {
        cerr << "ERROR: Couldn't lock vehicle mutex!" << endl;
    }
    
    value = vehicle.acceleration;
    
    if (pthread_mutex_unlock(&vehicle.lock)) {
        cerr << "ERROR: Couldn't unlock vehicle mutex!" << endl;
    }
    
    return value;
}

void setDirection (int value)
{
    if (pthread_mutex_lock(&vehicle.lock)) {
        cerr << "ERROR: Couldn't lock vehicle mutex!" << endl;
    }
    
    vehicle.direction = value;
    
    if (pthread_mutex_unlock(&vehicle.lock)) {
        cerr << "ERROR: Couldn't unlock vehicle mutex!" << endl;
    }
}

int getDirection (void)
{
    int value;
    
    if (pthread_mutex_lock(&vehicle.lock)) {
        cerr << "ERROR: Couldn't lock vehicle mutex!" << endl;
    }
    
    value = vehicle.direction;
    
    if (pthread_mutex_unlock(&vehicle.lock)) {
        cerr << "ERROR: Couldn't unlock vehicle mutex!" << endl;
    }
    
    return value;
}

void setSpeed (double value)
{
    if (pthread_mutex_lock(&vehicle.lock)) {
        cerr << "ERROR: Couldn't lock vehicle mutex!" << endl;
    }
    
    vehicle.speed = value;
    
    if (pthread_mutex_unlock(&vehicle.lock)) {
        cerr << "ERROR: Couldn't unlock vehicle mutex!" << endl;
    }
}

double getSpeed (void)
{
    int value;
    
    if (pthread_mutex_lock(&vehicle.lock)) {
        cerr << "ERROR: Couldn't lock vehicle mutex!" << endl;
    }
    
    value = vehicle.speed;
    
    if (pthread_mutex_unlock(&vehicle.lock)) {
        cerr << "ERROR: Couldn't unlock vehicle mutex!" << endl;
    }
    
    return value;
}

void setSteering (double value)
{
    if (pthread_mutex_lock(&vehicle.lock)) {
        cerr << "ERROR: Couldn't lock vehicle mutex!" << endl;
    }
    
    vehicle.steering = value;
    
    if (pthread_mutex_unlock(&vehicle.lock)) {
        cerr << "ERROR: Couldn't unlock vehicle mutex!" << endl;
    }
}

double getSteering (void)
{
    double value;
    
    if (pthread_mutex_lock(&vehicle.lock)) {
        cerr << "ERROR: Couldn't lock vehicle mutex!" << endl;
    }
    
    value = vehicle.steering;
    
    if (pthread_mutex_unlock(&vehicle.lock)) {
        cerr << "ERROR: Couldn't unlock vehicle mutex!" << endl;
    }
    
    return value;
}

void setWidth (double value)
{
    if (pthread_mutex_lock(&vehicle.lock)) {
        cerr << "ERROR: Couldn't lock vehicle mutex!" << endl;
    }
    
    vehicle.width = value;
    
    if (pthread_mutex_unlock(&vehicle.lock)) {
        cerr << "ERROR: Couldn't unlock vehicle mutex!" << endl;
    }
}

double getWidth (void)
{
    int value;
    
    if (pthread_mutex_lock(&vehicle.lock)) {
        cerr << "ERROR: Couldn't lock vehicle mutex!" << endl;
    }
    
    value = vehicle.width;
    
    if (pthread_mutex_unlock(&vehicle.lock)) {
        cerr << "ERROR: Couldn't unlock vehicle mutex!" << endl;
    }
    
    return value;
}

void setLength (double value)
{
    if (pthread_mutex_lock(&vehicle.lock)) {
        cerr << "ERROR: Couldn't lock vehicle mutex!" << endl;
    }
    
    vehicle.lenght = value;
    
    if (pthread_mutex_unlock(&vehicle.lock)) {
        cerr << "ERROR: Couldn't unlock vehicle mutex!" << endl;
    }
}

double getLenght (void)
{
    int value;
    
    if (pthread_mutex_lock(&vehicle.lock)) {
        cerr << "ERROR: Couldn't lock vehicle mutex!" << endl;
    }
    
    value = vehicle.lenght;
    
    if (pthread_mutex_unlock(&vehicle.lock)) {
        cerr << "ERROR: Couldn't unlock vehicle mutex!" << endl;
    }
    
    return value;
}

void setHeight (double value)
{
    if (pthread_mutex_lock(&vehicle.lock)) {
        cerr << "ERROR: Couldn't lock vehicle mutex!" << endl;
    }
    
    vehicle.height = value;
    
    if (pthread_mutex_unlock(&vehicle.lock)) {
        cerr << "ERROR: Couldn't unlock vehicle mutex!" << endl;
    }
}

double getHeight(void)
{
    int value;
    
    if (pthread_mutex_lock(&vehicle.lock)) {
        cerr << "ERROR: Couldn't lock vehicle mutex!" << endl;
    }
    
    value = vehicle.height;
    
    if (pthread_mutex_unlock(&vehicle.lock)) {
        cerr << "ERROR: Couldn't unlock vehicle mutex!" << endl;
    }
    
    return value;
}

void setWheelbase(double value)
{
    if (pthread_mutex_lock(&vehicle.lock)) {
        cerr << "ERROR: Couldn't lock vehicle mutex!" << endl;
    }
    
    vehicle.wheelbase = value;
    
    if (pthread_mutex_unlock(&vehicle.lock)) {
        cerr << "ERROR: Couldn't unlock vehicle mutex!" << endl;
    }
}

double getWheelbase(void)
{
    int value;
    
    if (pthread_mutex_lock(&vehicle.lock)) {
        cerr << "ERROR: Couldn't lock vehicle mutex!" << endl;
    }
    
    value = vehicle.wheelbase;
    
    if (pthread_mutex_unlock(&vehicle.lock)) {
        cerr << "ERROR: Couldn't unlock vehicle mutex!" << endl;
    }
    
    return value;
}

void setFrontOverhang(double value)
{
    if (pthread_mutex_lock(&vehicle.lock)) {
        cerr << "ERROR: Couldn't lock vehicle mutex!" << endl;
    }
    
    vehicle.frontOverhang = value;
    
    if (pthread_mutex_unlock(&vehicle.lock)) {
        cerr << "ERROR: Couldn't unlock vehicle mutex!" << endl;
    }
}

double getFrontOverhang(void)
{
    int value;
    
    if (pthread_mutex_lock(&vehicle.lock)) {
        cerr << "ERROR: Couldn't lock vehicle mutex!" << endl;
    }
    
    value = vehicle.frontOverhang;
    
    if (pthread_mutex_unlock(&vehicle.lock)) {
        cerr << "ERROR: Couldn't unlock vehicle mutex!" << endl;
    }
    
    return value;
}

void setRearOverhang(double value)
{
    if (pthread_mutex_lock(&vehicle.lock)) {
        cerr << "ERROR: Couldn't lock vehicle mutex!" << endl;
    }
    
    vehicle.rearOverhang = value;
    
    if (pthread_mutex_unlock(&vehicle.lock)) {
        cerr << "ERROR: Couldn't unlock vehicle mutex!" << endl;
    }
}

double getRearOverhang(void)
{
    int value;
    
    if (pthread_mutex_lock(&vehicle.lock)) {
        cerr << "ERROR: Couldn't lock vehicle mutex!" << endl;
    }
    
    value = vehicle.rearOverhang;
    
    if (pthread_mutex_unlock(&vehicle.lock)) {
        cerr << "ERROR: Couldn't unlock vehicle mutex!" << endl;
    }
    
    return value;
}
