/**
 * @file vehicle_data.cpp
 * @author Sergiu-Petru Tabacariu
 * @date 5.4.2018
 */

#include "vehicle_data.hpp"

void VehicleDimensions::set(double w, double l, double h, double wb, double fO, double rO)
{
    width = w;
    length = l;
    height = h;
    wheelbase = wb;
    frontOverhang = fO;
    rearOverhang = rO;
}

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
    dimensions.width = value;
}

double VehicleModel::getWidth (void)
{
    std::lock_guard<std::mutex> guard(lock);
    return dimensions.width;
}

void VehicleModel::setLength (double value)
{
    std::lock_guard<std::mutex> guard(lock);
    dimensions.length = value;
}

double VehicleModel::getlength (void)
{
    std::lock_guard<std::mutex> guard(lock);
    return dimensions.length;
}

void VehicleModel::setHeight (double value)
{
    std::lock_guard<std::mutex> guard(lock);
    dimensions.height = value;
}

double VehicleModel::getHeight(void)
{
    std::lock_guard<std::mutex> guard(lock);
    return dimensions.height;
}

void VehicleModel::setWheelbase(double value)
{
    std::lock_guard<std::mutex> guard(lock);
    dimensions.wheelbase = value;
}

double VehicleModel::getWheelbase(void)
{
    std::lock_guard<std::mutex> guard(lock);
    return dimensions.wheelbase;
}

void VehicleModel::setFrontOverhang(double value)
{
    std::lock_guard<std::mutex> guard(lock);
    dimensions.frontOverhang = value;
}

double VehicleModel::getFrontOverhang(void)
{
    std::lock_guard<std::mutex> guard(lock);
    return dimensions.frontOverhang;
}

void VehicleModel::setRearOverhang(double value)
{
    std::lock_guard<std::mutex> guard(lock);
    dimensions.rearOverhang = value;
}

double VehicleModel::getRearOverhang(void)
{
    std::lock_guard<std::mutex> guard(lock);
    return dimensions.rearOverhang;
}

void VehicleModel::setDimensions(double w, double l, double h, double wb, double fO, double rO)
{
    std::lock_guard<std::mutex> guard(lock);
    dimensions.width = w;
    dimensions.length = l;
    dimensions.height = h;
    dimensions.wheelbase = wb;
    dimensions.frontOverhang = fO;
    dimensions.rearOverhang = rO;
}

void VehicleModel::setDimensions(VehicleDimensions d)
{
    std::lock_guard<std::mutex> guard(lock);
    dimensions = d;
}

VehicleDimensions VehicleModel::getDimensions (void)
{
    std::lock_guard<std::mutex> guard(lock);
    return dimensions;
}

void VehicleModel::stop (void)
{
    std::lock_guard<std::mutex> guard(lock);
    stopFlag = true;
}

void VehicleModel::releaseStop (void)
{
    std::lock_guard<std::mutex> guard(lock);
    stopFlag = false;
}

bool VehicleModel::checkStop (void)
{
    std::lock_guard<std::mutex> guard(lock);
    return stopFlag;
}
