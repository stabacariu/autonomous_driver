/**
 * @file ultrasonic.hpp
 * @author Sergiu-Tabacariu
 * @date 29.6.2017
 */

#ifndef ULTRASONIC_HPP
#define ULTRASONIC_HPP

double minDistance = 0; //!< Minimum measurable distance in mm
double maxDistance = 0; //!< Maximum measurable distance in mm
double resolution = 0; //!< Resolution of measurement in mm

void setMinDistance(double distance);
double getMinDistance(void);
void setMaxDistance(double distance);
double getMaxDistance(void);
void setResolution(double resolution);
double getResolution(void);

#endif // ULTRASONIC_HPP
