/*
 * RotatingCube.cpp
 *
 *  Created on: Jul 10, 2013
 *      Author: nicholaskell
 */

#include <cstddef>

#include <GL/glut.h>

#include "RotatingCube.h"
#include <graphics/Color.h>

namespace gal {

    RotatingCube* RotatingCube::instance = NULL;

    RotatingCube::RotatingCube() {
        xAngle = 0;
        yAngle = 0;
        zAngle = 0;
    }

    RotatingCube* RotatingCube::getInstance() {
        if (!RotatingCube::instance) {
            RotatingCube::instance = new RotatingCube();
        }
        return RotatingCube::instance;
    }

    void RotatingCube::draw() {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear The Screen And The Depth Buffer
        glLoadIdentity();               // Reset The View

        glTranslatef(0.0f, 0.50f, -5.0f);       // move 5 units into the screen.
//                glRotatef(45,1,0,0);

        glRotatef(xAngle, 1.0, 1.0, 1.0);     // Rotate On The X Axis
//                glRotatef(yrot, 0.0f, 1.0f, 0.0f);     // Rotate On The Y Axis
//                glRotatef(zrot, 0.0f, 1.0f, 1.0f);     // Rotate On The Z Axis

        //        glBindTexture(GL_TEXTURE_2D, texture[0]);  // choose the texture to use.

        // done with the polygon.

        this->drawCube();

        // since this is double buffered, swap the buffers to display what just got drawn.
        glutSwapBuffers();
    }

    void RotatingCube::idle() {
    }

    void RotatingCube::drawCube() {
        glBegin(GL_QUADS);                      // begin drawing a cube
        {

            // Front Face (note that the texture's corners have to match the quad's corners)
            //glColor3f(1, 0, 0);
            Color::setColor(Color::red);
//            glBindTexture(GL_TEXTURE_2D, texture[0]);  // choose the texture to use.
            glTexCoord2f(0.0f, 0.0f);
            glVertex3f(-1.0f, -1.0f, 1.0f); // Bottom Left Of The Texture and Quad
            glTexCoord2f(1.0f, 0.0f);
            glVertex3f(1.0f, -1.0f, 1.0f); // Bottom Right Of The Texture and Quad
            glTexCoord2f(1.0f, 1.0f);
            glVertex3f(1.0f, 1.0f, 1.0f);  // Top Right Of The Texture and Quad
            glTexCoord2f(0.0f, 1.0f);
            glVertex3f(-1.0f, 1.0f, 1.0f);  // Top Left Of The Texture and Quad

            // Back Face
            glColor3f(1, 1, 0);
            //            glBindTexture(GL_TEXTURE_2D, texture[0]);  // choose the texture to use.
            glTexCoord2f(1.0f, 0.0f);
            glVertex3f(-1.0f, -1.0f, -1.0f); // Bottom Right Of The Texture and Quad
            glTexCoord2f(1.0f, 1.0f);
            glVertex3f(-1.0f, 1.0f, -1.0f); // Top Right Of The Texture and Quad
            glTexCoord2f(0.0f, 1.0f);
            glVertex3f(1.0f, 1.0f, -1.0f);  // Top Left Of The Texture and Quad
            glTexCoord2f(0.0f, 0.0f);
            glVertex3f(1.0f, -1.0f, -1.0f); // Bottom Left Of The Texture and Quad

            // Top Face
            glColor3f(1, 0, 1);
            //            glBindTexture(GL_TEXTURE_2D, texture[0]);  // choose the texture to use.
            glTexCoord2f(0.0f, 1.0f);
            glVertex3f(-1.0f, 1.0f, -1.0f);  // Top Left Of The Texture and Quad
            glTexCoord2f(0.0f, 0.0f);
            glVertex3f(-1.0f, 1.0f, 1.0f); // Bottom Left Of The Texture and Quad
            glTexCoord2f(1.0f, 0.0f);
            glVertex3f(1.0f, 1.0f, 1.0f); // Bottom Right Of The Texture and Quad
            glTexCoord2f(1.0f, 1.0f);
            glVertex3f(1.0f, 1.0f, -1.0f);  // Top Right Of The Texture and Quad

            // Bottom Face
            Color::setColor(Color::green);
            //            glBindTexture(GL_TEXTURE_2D, texture[0]);  // choose the texture to use.
            glTexCoord2f(1.0f, 1.0f);
            glVertex3f(-1.0f, -1.0f, -1.0f); // Top Right Of The Texture and Quad
            glTexCoord2f(0.0f, 1.0f);
            glVertex3f(1.0f, -1.0f, -1.0f);  // Top Left Of The Texture and Quad
            glTexCoord2f(0.0f, 0.0f);
            glVertex3f(1.0f, -1.0f, 1.0f); // Bottom Left Of The Texture and Quad
            glTexCoord2f(1.0f, 0.0f);
            glVertex3f(-1.0f, -1.0f, 1.0f); // Bottom Right Of The Texture and Quad

            // Right face
            glColor3f(0, 1, 1);
            //            glBindTexture(GL_TEXTURE_2D, texture[0]);  // choose the texture to use.
            glTexCoord2f(1.0f, 0.0f);
            glVertex3f(1.0f, -1.0f, -1.0f); // Bottom Right Of The Texture and Quad
            glTexCoord2f(1.0f, 1.0f);
            glVertex3f(1.0f, 1.0f, -1.0f);  // Top Right Of The Texture and Quad
            glTexCoord2f(0.0f, 1.0f);
            glVertex3f(1.0f, 1.0f, 1.0f);  // Top Left Of The Texture and Quad
            glTexCoord2f(0.0f, 0.0f);
            glVertex3f(1.0f, -1.0f, 1.0f); // Bottom Left Of The Texture and Quad

            // Left Face
            Color::setColor(Color::blue);
            //            glBindTexture(GL_TEXTURE_2D, texture[0]);  // choose the texture to use.
            glTexCoord2f(0.0f, 0.0f);
            glVertex3f(-1.0f, -1.0f, -1.0f); // Bottom Left Of The Texture and Quad
            glTexCoord2f(1.0f, 0.0f);
            glVertex3f(-1.0f, -1.0f, 1.0f); // Bottom Right Of The Texture and Quad
            glTexCoord2f(1.0f, 1.0f);
            glVertex3f(-1.0f, 1.0f, 1.0f);  // Top Right Of The Texture and Quad
            glTexCoord2f(0.0f, 1.0f);
            glVertex3f(-1.0f, 1.0f, -1.0f);  // Top Left Of The Texture and Quad
        }
        glEnd();
    }

    void RotatingCube::update() {
        xAngle += 12.8f;                        // X Axis Rotation
        yAngle += 0.6f;                        // Y Axis Rotation
        zAngle += 0.7f;                        // Z Axis Rotation
    }

    RotatingCube::~RotatingCube() {
        delete RotatingCube::instance;
        RotatingCube::instance = NULL;
    }

    void RotatingCube::idleMethod() {
        RotatingCube::getInstance()->idle();
    }

    void RotatingCube::drawMethod() {
        RotatingCube::getInstance()->draw();
    }

} /* namespace gal */
