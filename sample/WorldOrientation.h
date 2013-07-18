/*
 * WorldOrientation.h
 *
 *  Created on: Jul 18, 2013
 *      Author: nicholaskell
 */

#ifndef WORLDORIENTATION_H_
#define WORLDORIENTATION_H_

#include "GL/glut.h"

#include <system/time/Clock.h>


namespace gal {

    /*
     *
     */
    class WorldOrientation {
        public:
            WorldOrientation();
            virtual ~WorldOrientation();

            void draw();
            void idle();
            void setup();

            void drawCube();
            void drawFloor();
            void update();

        protected:
            float xAngle, yAngle, zAngle;
            GLUquadric* quadratic;
    };

} /* namespace gal */
#endif /* WORLDORIENTATION_H_ */
