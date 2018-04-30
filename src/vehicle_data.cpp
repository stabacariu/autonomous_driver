/**
 * @file vehicle_data.cpp
 * @author Sergiu-Petru Tabacariu
 * @date 5.4.2018
 */

#include "vehicle_data.hpp"

void VehicleData::setAcceleration (double value)
{
    std::lock_guard<std::mutex> guard(lock);
    acceleration = value;
}

double VehicleData::getAcceleration (void)
{
    std::lock_guard<std::mutex> guard(lock);
    return acceleration;
}

void VehicleData::setDirection (VehicleData::Direction value)
{
    std::lock_guard<std::mutex> guard(lock);
    direction = value;
}

VehicleData::Direction VehicleData::getDirection (void)
{
    std::lock_guard<std::mutex> guard(lock);
    return direction;
}

void VehicleData::setSpeed (double value)
{
    std::lock_guard<std::mutex> guard(lock);
    speed = value;
}

double VehicleData::getSpeed (void)
{
    std::lock_guard<std::mutex> guard(lock);
    return speed;
}

void VehicleData::setSteering (double value)
{
    std::lock_guard<std::mutex> guard(lock);
    steering = value;
}

double VehicleData::getSteering (void)
{
    std::lock_guard<std::mutex> guard(lock);
    return steering;
}

void VehicleData::setWidth (double value)
{
    std::lock_guard<std::mutex> guard(lock);
    width = value;
}

double VehicleData::getWidth (void)
{
    std::lock_guard<std::mutex> guard(lock);
    return width;
}

void VehicleData::setLength (double value)
{
    std::lock_guard<std::mutex> guard(lock);
    lenght = value;
}

double VehicleData::getLenght (void)
{
    std::lock_guard<std::mutex> guard(lock);
    return lenght;
}

void VehicleData::setHeight (double value)
{
    std::lock_guard<std::mutex> guard(lock);
    height = value;
}

double VehicleData::getHeight(void)
{
    std::lock_guard<std::mutex> guard(lock);
    return height;
}

void VehicleData::setWheelbase(double value)
{
    std::lock_guard<std::mutex> guard(lock);
    wheelbase = value;
}

double VehicleData::getWheelbase(void)
{
    std::lock_guard<std::mutex> guard(lock);
    return wheelbase;
}

void VehicleData::setFrontOverhang(double value)
{
    std::lock_guard<std::mutex> guard(lock);
    frontOverhang = value;
}

double VehicleData::getFrontOverhang(void)
{
    std::lock_guard<std::mutex> guard(lock);
    return frontOverhang;
}

void VehicleData::setRearOverhang(double value)
{
    std::lock_guard<std::mutex> guard(lock);
    rearOverhang = value;
}

double VehicleData::getRearOverhang(void)
{
    std::lock_guard<std::mutex> guard(lock);
    return rearOverhang;
}
