/**
 * @file user_interface_data.hpp
 * @author Sergiu-Petru Tabacariu
 * @date 25.4.2018
 */

#ifndef USER_INTERFACE_DATA_HPP
#define USER_INTERFACE_DATA_HPP

#include <iostream>
#include <mutex>

class UserInterfaceData {
public:
    ~UserInterfaceData() = default;
    
    void setKey (char k);
    char getKey (void);
    char getLastKey (void);

private:
    char key {(char)(-1)};
    char lastKey {(char)(-1)};
    std::mutex lock; //!< Mutex lock for synchronized access
};

#endif // USER_INTERFACE_DATA_HPP
