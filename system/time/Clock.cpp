/*
 * Clock.cpp
 *
 *  Created on: Jul 10, 2013
 *      Author: nicholaskell
 */

#include "Clock.h"
#include <iostream>
#include "system/Config.h"

#ifdef GAL_SYSTEM_MACOS
    #include <mach/mach_time.h>
#else
    #include <time.h>
#endif

namespace gal {

    Clock::Clock() {
        this->start();
    }

    Clock::~Clock() {
    }

    void Clock::start() {
        this->startTime = getCurrentOSTime();
    }

    Time Clock::getElapsedTime() {
        return this->getCurrentOSTime() - this->startTime;
    }

    Time Clock::getCurrentOSTime() {

#ifdef GAL_SYSTEM_MACOS
        static mach_timebase_info_data_t frequency = { 0, 0 };
        if (frequency.denom == 0)
            mach_timebase_info(&frequency);
        Uint64 nanoseconds = mach_absolute_time() * frequency.numer
                / frequency.denom;
        Time time = gal::microseconds(nanoseconds / 1000);
//        std::cout << "Getting time:"<<time.asMilliseconds() << std::endl;
        return time;

#else
        timespec time;
        clock_gettime(CLOCK_MONOTONIC, &time);
        return gal::microseconds(static_cast<Uint64>(time.tv_sec) * 1000000 + time.tv_nsec / 1000);
#endif

    }

    Time Clock::restart() {
        Time now = getCurrentOSTime();
        Time elapsed = now - startTime;
        startTime = now;
        return elapsed;
    }

    Time Clock::stop() {
        return getCurrentOSTime() - startTime;
    }

} /* namespace gal */
