/*
 * Time.h
 *
 *  Created on: Jul 10, 2013
 *      Author: nicholaskell
 */

#ifndef TIME_H_
#define TIME_H_

#include "system/Config.h"

namespace gal {

    /*
     *
     */
    class Time {
        public:
            Time();
            float asSeconds() const;
            Int32 asMilliseconds() const;
            Int64 asMicroseconds() const;

        private:
            friend Time seconds(float);
            friend Time milliseconds(Int32);
            friend Time microseconds(Int64);
            explicit Time(Int64 microseconds);

        private:
            Int64 currentMicroseconds;
    };


    Time seconds(float amount);
    Time milliseconds(Int32 amount);
    Time microseconds(Int64 amount);
    bool operator ==(Time left, Time right);
    bool operator !=(Time left, Time right);
    bool operator <(Time left, Time right);
    bool operator >(Time left, Time right);
    bool operator <=(Time left, Time right);
    bool operator >=(Time left, Time right);
    Time operator -(Time right);
    Time operator +(Time left, Time right);
    Time& operator +=(Time& left, Time right);
    Time operator -(Time left, Time right);
    Time& operator -=(Time& left, Time right);
    Time operator *(Time left, float right);
    Time operator *(Time left, Int64 right);
    Time operator *(float left, Time right);
    Time operator *(Int64 left, Time right);
    Time& operator *=(Time& left, float right);
    Time& operator *=(Time& left, Int64 right);
    Time operator /(Time left, float right);
    Time operator /(Time left, Int64 right);
    Time& operator /=(Time& left, float right);
    Time& operator /=(Time& left, Int64 right);


} /* namespace gal */
#endif /* TIME_H_ */
