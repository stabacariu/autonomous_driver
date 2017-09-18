/**
 * @file configuration.cpp
 * @author Sergiu-Petru Tabacariu
 * @date 18.09.2017
 */

#include "configuration.hpp"

void *configure (void *arg)
{
    while ((getSystemState() & SYS_MODE_CONFIG) == SYS_MODE_CONFIG) {
        
    }
}
