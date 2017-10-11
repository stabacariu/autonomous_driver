/**
 * @file timer_tools.hpp
 * @author Sergiu-Petru Tabacariu
 * @date 13.9.2017
 */

#include <ctime>

#define NSEC_PER_SEC    (1000000000)
#define NSEC_PER_MSEC   (1000000)
#define NSEC_PER_USEC   (1000)

#define timespec_norm(t) {                                             \
    if ((t)->tv_nsec >= NSEC_PER_SEC) {                                \
        (t)->tv_nsec -= NSEC_PER_SEC;                                  \
        (t)->tv_sec++;                                                 \
    } else if ((t)->tv_nsec < 0) {                                     \
        (t)->tv_nsec += NSEC_PER_SEC;                                  \
        (t)->tv_sec--;                                                 \
    }                                                                  \
}

#define timespec_add(t1, t2) do {                                      \
    (t1)->tv_nsec += (t2)->tv_nsec;                                    \
    (t1)->tv_sec += (t2)->tv_sec;                                      \
    timespec_norm(t1);                                                 \
} while (0)

void delay_ms (long value);
void delay_us (long value);
