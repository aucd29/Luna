/*
 * ccCoreAPI.cpp
 *
 *  Created on: 2016. 1. 26.
 *      Author: kmansoo
 */

#include <thread>
#include <chrono>

#include "ccCoreAPI.h"

namespace Luna {

// simulation of Windows GetTickCount()
static unsigned long long GetChronoTickCount()
{
    using namespace std::chrono;
    return duration_cast<milliseconds>(steady_clock::now().time_since_epoch()).count();
}

//
//  I'll use following code!
//
//// Clock built upon Windows GetTickCount()
//struct TickCountClock
//{
//    typedef unsigned long long                       rep;
//    typedef std::milli                               period;
//    typedef std::chrono::duration<rep, period>       duration;
//    typedef std::chrono::time_point<TickCountClock>  time_point;
//    static const bool is_steady = true;
//
//    static time_point now() noexcept
//    {
//        return time_point(duration(GetChronoTickCount()));
//    }
//};


void    sleep(int milliseconds)
{
    std::this_thread::sleep_for(std::chrono::milliseconds{ milliseconds });
}

void    usleep(int microseconds)
{
    std::this_thread::sleep_for(std::chrono::microseconds{ microseconds });
}

unsigned long long getTickCount()
{
    return GetChronoTickCount();
}

}

