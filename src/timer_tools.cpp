/**
 * @file timer_tools.cpp
 * @author Sergiu-Petru Tabacariu
 * @date 13.9.2017
 */

#include "timer_tools.hpp"

//~ void timespec_norm (timespec& ts)
//~ {
    //~ if (ts.tv_nsec >= NSEC_PER_SEC) {
        //~ ts.tv_nsec -= NSEC_PER_SEC;
        //~ ts.tv_sec++;
    //~ }
    //~ else if (ts.tv_nsec < 0) {
        //~ ts.tv_nsec += NSEC_PER_SEC;
        //~ ts.tv_sec--;
    //~ }
//~ }
//~ 
//~ void timespec_add (timespec& ts1, timespec& ts2)
//~ {
    //~ do {
        //~ ts1.tv_nsec += ts2.tv_nsec;
        //~ ts1.tv_sec += ts2.tv_sec;
        //~ timespec_norm(ts1);
    //~ } while (0);
//~ }

void delay_ms (long value)
{
    timespec time;
    timespec period;
    
    period.tv_sec = 0;
    period.tv_nsec = value * NSEC_PER_MSEC;
    
    clock_gettime(CLOCK_MONOTONIC, &time);
    timespec_add(&time, &period);
    clock_nanosleep(CLOCK_MONOTONIC, TIMER_ABSTIME, &time, NULL);
}

void delay_us (long value)
{
    timespec time;
    timespec period;
    
    period.tv_sec = 0;
    period.tv_nsec = value * NSEC_PER_USEC;
    
    clock_gettime(CLOCK_MONOTONIC, &time);
    timespec_add(&time, &period);
    clock_nanosleep(CLOCK_MONOTONIC, TIMER_ABSTIME, &time, NULL);
}
