/*
 * RotatingCube.h
 *
 *  Created on: Jul 10, 2013
 *      Author: nicholaskell
 */

#ifndef ROTATINGCUBE_H_
#define ROTATINGCUBE_H_

#include "GL/glut.h"

#include <system/time/Clock.h>

//#include <graphics/GalaxyApplicationBase.h>
#include <graphics/texture/Texture.h>

namespace gal {

    /*
     *
     */
    class RotatingCube {
        protected:


        public:
            static RotatingCube* getInstance();
             ~RotatingCube();

             void draw();
             void idle();
             void setup();

             static void idleMethod();
             static void drawMethod();
             static void setupMethod();


             void drawCube();
             void drawFloor();
             void update();


        protected:
            RotatingCube();
            static RotatingCube* instance;
            float xAngle, yAngle, zAngle;
            GLUquadric*  quadratic;
            Texture cubeTexture;
            Texture floorTexture;




    };

} /* namespace gal */
#endif /* ROTATINGCUBE_H_ */
