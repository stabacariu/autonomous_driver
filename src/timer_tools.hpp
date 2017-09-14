/**
 * @file timer_tools.hpp
 * @author Sergiu-Petru Tabacariu
 * @date 13.9.2017
 */

#include <ctime>

#define NSEC_PER_SEC    1000000000
#define NSEC_PER_MSEC   1000000
#define NSEC_PER_USEC   1000

void delay_ms (long value);
void delay_us (long value);
