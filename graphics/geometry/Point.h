/*
 * Point.h
 *
 *  Created on: Jul 11, 2013
 *      Author: nicholaskell
 */

#ifndef POINT_H_
#define POINT_H_

namespace gal {

    /*
     *
     */
    class Point {
        public:
            Point();
            Point(float x, float y, float z);
            virtual ~Point();
            float x,y,z;
    };

} /* namespace gal */
#endif /* POINT_H_ */
