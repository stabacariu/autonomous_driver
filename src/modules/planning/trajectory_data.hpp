/**
 * @file trajectory_data.hpp
 * @author Sergiu-Petru Tabacariu
 * @date 29.3.2018
 */

#ifndef TRAJECTORY_DATA_HPP
#define TRAJECTORY_DATA_HPP

#include <iostream>
#include <mutex>
#include <opencv2/opencv.hpp>

//! @addtogroup path_planning
//! @{

/**
 * @brief A trajectory data class
 * 
 * This Class describes a trajectory data class. A trajectory is defined
 * by pixel coordinates in a captured image.
 */
class TrajectoryData {
public:
    ~TrajectoryData() = default;
    
    /**
     * @brief Push trajectory data point
     * 
     * This function pushes a trajectory data point to a vector. It must
     * be sorted in descenting order so that \f$\begin{pmatrix}x_n & y_n\end{pmatrix}\f$
     * and \f$\begin{pmatrix}x_m & y_m\end{pmatrix}\f$, with \f$y_n < y_m\f$.
     * It provides synchronised access with a mutex lock.
     * 
     * @param point Point to be pushed at the end of the vector
     */
    void push_back (cv::Point point);
    
    /**
     * @brief Point at index i
     * 
     * This function returns a trajectory point at index i. It provides
     * synchronised access with a mutex lock.
     * 
     * @param i Index of point
     * @return Point at index i
     */
    cv::Point at (int i);
    
    /**
     * @brief Size of trajectory data vector
     * 
     * This function returns the size of the trajectory data vector. It
     * provides synchronised access with a mutex lock.
     */
    int size (void);
    
    void clear (void);
    
private:
    std::vector<cv::Point> points; //!< Trajectory data point vector
    std::mutex lock; //!< Mutex lock
};

//! @} path_planning

#endif // TRAJECTORY_DATA_HPP
