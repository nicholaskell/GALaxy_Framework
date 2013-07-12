/*
 * RotatingCube.h
 *
 *  Created on: Jul 10, 2013
 *      Author: nicholaskell
 */

#ifndef ROTATINGCUBE_H_
#define ROTATINGCUBE_H_

#include <system/Clock.h>

#include <graphics/GalaxyApplicationBase.h>

namespace gal {

    /*
     *
     */
    class RotatingCube: public GalaxyApplicationBase<RotatingCube> {
        protected:


        public:
            RotatingCube();
             ~RotatingCube();

             void draw();
             void idle();

             void drawCube();
             void update();

        protected:
            float xAngle, yAngle, zAngle;


    };

} /* namespace gal */
#endif /* ROTATINGCUBE_H_ */
