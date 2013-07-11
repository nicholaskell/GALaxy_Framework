/*
 * RotatingCube.h
 *
 *  Created on: Jul 10, 2013
 *      Author: nicholaskell
 */

#ifndef ROTATINGCUBE_H_
#define ROTATINGCUBE_H_

#include <system/Clock.h>

namespace gal {

    /*
     *
     */
    class RotatingCube {
        protected:
            RotatingCube();

        public:
            virtual ~RotatingCube();
            static RotatingCube* getInstance();

            static void idleMethod();
            static void drawMethod();

            virtual void draw();
            virtual void idle();

            virtual void drawCube();
            virtual void update();

        protected:
            static RotatingCube* instance;
            float xAngle, yAngle, zAngle;


    };

} /* namespace gal */
#endif /* ROTATINGCUBE_H_ */
