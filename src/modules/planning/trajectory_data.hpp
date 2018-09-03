/**
 * @file trajectory_data.hpp
 * @author Sergiu-Petru Tabacariu
 * @date 29.3.2018
 */

#ifndef TRAJECTORY_DATA_HPP
#define TRAJECTORY_DATA_HPP

#include <iostream>
#include <atomic>
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
     * @brief Set trajectory data point vector
     * 
     * This function sets a trajectory data point vector. It must
     * be sorted in descenting order so that \f$\begin{pmatrix}x_n & y_n\end{pmatrix}\f$
     * and \f$\begin{pmatrix}x_m & y_m\end{pmatrix}\f$, with \f$y_n < y_m\f$.
     * It provides synchronised access with a mutex lock.
     * 
     * @param pv Point vector
     */
    void set (std::vector<cv::Point> pv);
    
    /**
     * @brief Get trajectory data point vector
     * 
     * This function gets a trajectory data point vector.
     * It provides synchronised access with a mutex lock.
     * 
     * @return Point vector
     */
    std::vector<cv::Point> get (void);
    
    /**
     * @brief Size of trajectory point vector
     * 
     * This function returns the size of the trajectory data vector.
     * 
     * @return Size of trajectory point vector
     */
    int size (void);
    
    /**
     * @brief Clear trajectory point vector
     * 
     * This function clears the trajectory point vector content.
     * The vector size is 0 after this operation.
     */
    void clear (void);
    
    /**
     * @brief Set trajectory line
     * 
     * This function sets a trajectory line described by two points, which
     * the starting and the ending points of the line.
     * 
     * @note This function is for compatibility usage only.
     * 
     * @param l Line as integer vector
     */
    void setLine (cv::Vec4i l);
    
    /**
     * @brief Get trajectory line
     * 
     * This function gets a trajectory line described by two points, which
     * the starting and the ending points of the line.
     * 
     * @note This function is for compatibility usage only.
     * 
     * @return Line as integer vector
     */
    cv::Vec4i getLine (void);
    
    std::atomic_bool active { false };
    
private:
    std::vector<cv::Point> points; //!< Trajectory data point vector
    cv::Vec4i line; //!< For compatibility only
    std::mutex lock; //!< Mutex lock
};

//! @} path_planning

#endif // TRAJECTORY_DATA_HPP
