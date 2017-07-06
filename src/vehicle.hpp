/**
 * @file vehicle.hpp
 * @author Sergiu-Petru Tabacariu
 * @date 29.6.2017
 */

#ifndef VEHICLE_HPP
#define VEHICLE_HPP

#include <iostream>
 
int acceleration = 0; //!< Accerelration from 0 to 4095
double speed = 0; //!< Speed in m/s
double steering = 0; //!< Steering angle in radian
double width = 0; //!< Vehicle width in mm
double lenght = 0; //!< Vehicle length in mm
double height = 0; //!< Vehicle height in mm
double wheelbase = 0; //!< Vehicle wheelbase in mm
double frontOverhang = 0; //!< Vehicle front overhang in mm
double rearOverhang = 0; //!< Vehicle rear overhang in mm

void setAcceleration(int value);
int getAcceleration(void);
void setSpeed(double value);
double getSpeed(double value);
void setSteering(double value);
double getSteering(void);
void setWidth(double value);
double getWidth(void);
void setLength(double value);
double getLenght(void);
void setHeight(double value);
double getHeight(void);
void setWheelbase(double value);
double getWheelbase(void);
void setFrontOverhang(double value);
double getFrontOverhang(void);
void setRearOverhang(double value);
double getRearOverhang(void);

#endif // VEHICLE_HPP
