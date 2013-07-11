/*
 * Point.cpp
 *
 *  Created on: Jul 11, 2013
 *      Author: nicholaskell
 */

#include "Point.h"

namespace gal {

    Point::Point() {
        x = 0;
        y = 0;
        z = 0;
    }

    Point::Point(float x, float y, float z) {
        this->x = x;
        this->y = y;
        this->z = z;
    }

    Point::~Point() {
    }


    //TODO - add operator overloading for math on points....

} /* namespace gal */
