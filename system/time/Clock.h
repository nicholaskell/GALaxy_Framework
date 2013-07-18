/*
 * Clock.h
 *
 *  Created on: Jul 10, 2013
 *      Author: nicholaskell
 */

#ifndef CLOCK_H_
#define CLOCK_H_

#include "Time.h";

namespace gal {

    /*
     *
     */
    class Clock {
        public:
            Clock();
            virtual ~Clock();
            virtual void start();
            virtual Time getCurrentOSTime();
            virtual Time getElapsedTime();
            virtual Time restart();
            virtual Time stop();

        protected:
            Time startTime;
    };

} /* namespace gal */
#endif /* CLOCK_H_ */
