/**
 * @file vehicle_data.hpp
 * @author Sergiu-Petru Tabacariu
 * @date 29.6.2017
 */

#ifndef VEHICLE_DATA_HPP
#define VEHICLE_DATA_HPP

#include <iostream>
#include <mutex>

//! @addtogroup vehicle_control
//! @{



/**
 * @brief A class to describe a vehicle
 */
class VehicleData {
public:
    ~VehicleData() = default;
    
    /**
     * @brief An enum to describe the steering direction of the vehicle
     */
    enum Direction {
        VEHICLE_LEFT = -1,
        VEHICLE_STRAIGHT = 0,
        VEHICLE_RIGHT = 1
    };
    
    /**
     * @brief An enum to describe the driving direction and gear of the
     *        vehicle.
     */
    enum Gear {
        VEHICLE_FORWARD = 1,
        VEHICLE_NEUTRAL = 0,
        VEHICLE_BACKWARD = -1,
    };
    
    /**
     * @brief A function to set the vehicle acceleration
     * 
     * This function sets the vehicle acceleration from 0 to 100 %.
     * 
     * @param value Percentage from 0 to 100 %
     */
    void setAcceleration (double value);
    
    /**
     * @brief A function to get the vehicle acceleration
     * 
     * This function gets the vehicle acceleration from 0 to 100 %.
     * 
     * @return Acceleration from 0 to 100 %
     */
    double getAcceleration (void);
    
    /**
     * @brief A function to set the vehicle steering direction
     * 
     * This function sets the vehicle steering direction.
     * 
     * @param value Steering direction
     */
    void setDirection (Direction value);
    
    /**
     * @brief A function to get the vehicle steering direction
     * 
     * This function gets the vehicle steering direction.
     * 
     * @return Steering direction
     */
    Direction getDirection (void);
    
    /**
     * @brief A function to set the vehicle speed
     * 
     * This function sets the vehicle speed in m/s.
     * 
     * @param value Speed value in m/s
     */
    void setSpeed (double value);
    
    /**
     * @brief A function to get the vehicle speed
     * 
     * This function gets the vehicle speed in m/s.
     * 
     * @return Speed value in m/s
     */
    double getSpeed (void);
    
    /**
     * @brief A function to set the vehicle steering angle
     * 
     * This function sets the vehicle steering angle in radiants from 0 to &pi;.
     * 
     * @param value Steering angle in radiants from 0 to &pi;
     */
    void setSteering (double value);
    
    /**
     * @brief A function to get the vehicle steering angle
     * 
     * This function gets the vehicle steering angle in radiants from 0 to &pi;.
     * 
     * @return Steering angle in radiants from 0 to &pi;
     */
    double getSteering (void);
    
    /**
     * @brief A function to set the vehicle width
     * 
     * This function sets the vehicle width in mm.
     * 
     * @param value Vehicle width in mm
     */
    void setWidth (double value);
    
    /**
     * @brief A function to get the vehicle width
     * 
     * This function gets the vehicle width in mm.
     * 
     * @return Vehicle width in mm
     */
    double getWidth (void);
    
    /**
     * @brief A function to set the vehicle length
     * 
     * This function sets the vehicle length in mm.
     * 
     * @param value Vehicle length in mm
     */
    void setLength (double value);
    
    /**
     * @brief A function to get the vehicle length
     * 
     * This function gets the vehicle length in mm.
     * 
     * @return Vehicle length in mm
     */
    double getLenght (void);
    
    /**
     * @brief A function to set the vehicle height
     * 
     * This function sets the vehicle height in mm.
     * 
     * @param value Vehicle height in mm
     */
    void setHeight (double value);
    
    /**
     * @brief A function to get the vehicle height
     * 
     * This function gets the vehicle height in mm.
     * 
     * @return Vehicle height in mm
     */
    double getHeight (void);
    
    /**
     * @brief A function to set the vehicle wheelbase length
     * 
     * This function sets the vehicle wheelbase length in mm.
     * 
     * @param value Vehicle wheelbase length in mm
     */
    void setWheelbase (double value);
    
    /**
     * @brief A function to get the vehicle wheelbase length
     * 
     * This function gets the vehicle wheelbase length in mm.
     * 
     * @return Vehicle wheelbase length in mm
     */
    double getWheelbase (void);
    
    /**
     * @brief A function to set the vehicle front overhang
     * 
     * This function sets the vehicle front overhang in mm.
     * 
     * @param value Vehicle front overhang in mm
     */
    void setFrontOverhang (double value);
    
    /**
     * @brief A function to get the vehicle front overhang
     * 
     * This function gets the vehicle front overhang in mm.
     * 
     * @return Vehicle front overhang in mm
     */
    double getFrontOverhang (void);
    
    /**
     * @brief A function to set the vehicle rear overhang
     * 
     * This function sets the vehicle rear overhang in mm.
     * 
     * @param value Vehicle rear overhang in mm
     */
    void setRearOverhang (double value);
    
    /**
     * @brief A function to get the vehicle rear overhang
     * 
     * This function gets the vehicle rear overhang in mm.
     * 
     * @return Vehicle rear overhang in mm
     */
    double getRearOverhang (void);
    
private:
    double acceleration; //!< Accerelration from -100 to 100 percent
    double speed; //!< Speed in m/s
    Gear gear; //!< Driving gear
    double steering; //!< Steering angle in radian
    Direction direction; //!< Direction from -1 to 1
    double width; //!< Vehicle width in mm
    double lenght; //!< Vehicle length in mm
    double height; //!< Vehicle height in mm
    double wheelbase; //!< Vehicle wheelbase in mm
    double frontOverhang; //!< Vehicle front overhang in mm
    double rearOverhang; //!< Vehicle rear overhang in mm
    std::mutex lock;
};

//! @} vehicle_control

#endif // VEHICLE_DATA_HPP
