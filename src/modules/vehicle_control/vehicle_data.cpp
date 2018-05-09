/**
 * @file vehicle_data.cpp
 * @author Sergiu-Petru Tabacariu
 * @date 5.4.2018
 */

#include "vehicle_data.hpp"

void VehicleModel::setAcceleration (double value)
{
    std::lock_guard<std::mutex> guard(lock);
    acceleration = value;
}

double VehicleModel::getAcceleration (void)
{
    std::lock_guard<std::mutex> guard(lock);
    return acceleration;
}

void VehicleModel::setDirection (VehicleDirection value)
{
    std::lock_guard<std::mutex> guard(lock);
    direction = value;
}

VehicleDirection VehicleModel::getDirection (void)
{
    std::lock_guard<std::mutex> guard(lock);
    return direction;
}

void VehicleModel::setSpeed (double value)
{
    std::lock_guard<std::mutex> guard(lock);
    speed = value;
}

double VehicleModel::getSpeed (void)
{
    std::lock_guard<std::mutex> guard(lock);
    return speed;
}

void VehicleModel::setSteering (double value)
{
    std::lock_guard<std::mutex> guard(lock);
    steering = value;
}

double VehicleModel::getSteering (void)
{
    std::lock_guard<std::mutex> guard(lock);
    return steering;
}

void VehicleModel::setWidth (double value)
{
    std::lock_guard<std::mutex> guard(lock);
    width = value;
}

double VehicleModel::getWidth (void)
{
    std::lock_guard<std::mutex> guard(lock);
    return width;
}

void VehicleModel::setLength (double value)
{
    std::lock_guard<std::mutex> guard(lock);
    lenght = value;
}

double VehicleModel::getLenght (void)
{
    std::lock_guard<std::mutex> guard(lock);
    return lenght;
}

void VehicleModel::setHeight (double value)
{
    std::lock_guard<std::mutex> guard(lock);
    height = value;
}

double VehicleModel::getHeight(void)
{
    std::lock_guard<std::mutex> guard(lock);
    return height;
}

void VehicleModel::setWheelbase(double value)
{
    std::lock_guard<std::mutex> guard(lock);
    wheelbase = value;
}

double VehicleModel::getWheelbase(void)
{
    std::lock_guard<std::mutex> guard(lock);
    return wheelbase;
}

void VehicleModel::setFrontOverhang(double value)
{
    std::lock_guard<std::mutex> guard(lock);
    frontOverhang = value;
}

double VehicleModel::getFrontOverhang(void)
{
    std::lock_guard<std::mutex> guard(lock);
    return frontOverhang;
}

void VehicleModel::setRearOverhang(double value)
{
    std::lock_guard<std::mutex> guard(lock);
    rearOverhang = value;
}

double VehicleModel::getRearOverhang(void)
{
    std::lock_guard<std::mutex> guard(lock);
    return rearOverhang;
}
