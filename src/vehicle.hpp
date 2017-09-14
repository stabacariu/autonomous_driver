/**
 * @file vehicle.hpp
 * @author Sergiu-Petru Tabacariu
 * @date 29.6.2017
 */

#ifndef VEHICLE_HPP
#define VEHICLE_HPP

#include <iostream>
#include <pthread.h>

struct Vehicle {
    double acceleration; //!< Accerelration from 0 to 4095
    int direction; //!< Direction from 0 to 4095
    double speed; //!< Speed in m/s
    double steering; //!< Steering angle in radian
    double width; //!< Vehicle width in mm
    double lenght; //!< Vehicle length in mm
    double height; //!< Vehicle height in mm
    double wheelbase; //!< Vehicle wheelbase in mm
    double frontOverhang; //!< Vehicle front overhang in mm
    double rearOverhang; //!< Vehicle rear overhang in mm
    pthread_mutex_t lock;
};

void initVehicle (void);
void setAcceleration (double value);
double getAcceleration (void);
void setDirection (int value);
int getDirection (void);
void setSpeed (double value);
double getSpeed (double value);
void setSteering (double value);
double getSteering (void);
void setWidth (double value);
double getWidth (void);
void setLength (double value);
double getLenght (void);
void setHeight (double value);
double getHeight (void);
void setWheelbase (double value);
double getWheelbase (void);
void setFrontOverhang (double value);
double getFrontOverhang (void);
void setRearOverhang (double value);
double getRearOverhang (void);

#endif // VEHICLE_HPP
