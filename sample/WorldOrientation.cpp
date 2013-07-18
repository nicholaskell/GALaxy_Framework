/*
 * WorldOrientation.cpp
 *
 *  Created on: Jul 18, 2013
 *      Author: nicholaskell
 */

#include "WorldOrientation.h"

namespace gal {

    WorldOrientation::WorldOrientation() {

        quadratic = gluNewQuadric();
        xAngle = 0;
        yAngle = 0;
        zAngle = 0;

    }

    WorldOrientation::~WorldOrientation() {
        // TODO Auto-generated destructor stub
    }

    void WorldOrientation::draw() {
        glClear(
                GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT
                        | GL_STENCIL_BUFFER_BIT); // Clear The Screen And The Depth Buffer

        glLoadIdentity();
//         Reset The View
//        glEnable(GL_LIGHTING);
//        glEnable(GL_DEPTH_TEST);
//        glShadeModel(GL_FLAT);

        glPushMatrix();
        {
            //            glScalef(1, -1, 1);
            glTranslatef(0, 0, -20);
            glRotatef(xAngle, 1.0, 1.0, 1.0);
            this->drawCube();
        }
        glPopMatrix();

        this->drawFloor();

        glPushMatrix();
        {
            glScalef(1, -1, 1);
            glTranslatef(0, 0, -20);
            glRotatef(xAngle, 1.0, 1.0, 1.0);
            this->drawCube();
        }
        glPopMatrix();

        this->update();

        // since this is double buffered, swap the buffers to display what just got drawn.
        glutSwapBuffers();
    }

    void WorldOrientation::idle() {
    }

    void WorldOrientation::setup() {
        glEnable(GL_TEXTURE_2D);            // Enable Texture Mapping
        glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
        glClearDepth(1.0);              // Enables Clearing Of The Depth Buffer
        glDepthFunc(GL_LESS);           // The Type Of Depth Test To Do
        glEnable(GL_DEPTH_TEST);            // Enables Depth Testing
        glShadeModel(GL_FLAT);            // Enables Smooth Color Shading

        glFrontFace(GL_CCW);
        glEnable(GL_COLOR_MATERIAL);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();               // Reset The Projection Matrix

        gluPerspective(45.0f, 640.0 / 480.0, 0.1f, 500.0f); // Calculate The Aspect Ratio Of The Window

        glTranslatef(0, 5, -20);
        glRotatef(-10, 1.0, 0, 0);

        glMatrixMode(GL_MODELVIEW);

        glEnable(GL_LIGHTING);

        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

//        GLfloat mat_shininess[] = { 50.0 };
//        glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);

        // Create light components
        GLfloat ambientLight[] = { 0.2f, 0.2f, 0.2f, 1.0f };
        GLfloat diffuseLight[] = { 0.8f, 0.8f, 0.8, 1.0f };
        GLfloat specularLight[] = { 0.5f, 0.5f, 0.5f, 1.0f };
        GLfloat position[] = { -1.5f, 1.0f, -4.0f, 1.0f };

        // Assign created components to GL_LIGHT0
        glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
        glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
        glLightfv(GL_LIGHT0, GL_SPECULAR, specularLight);
        glLightfv(GL_LIGHT0, GL_POSITION, position);

        GLfloat light1_ambient[] = { 0.2, 0.2, 0.2, 1.0 };
        GLfloat light1_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
        GLfloat light1_specular[] = { 1.0, 1.0, 1.0, 1.0 };
        GLfloat light1_position[] = { -2.0, 2.0, 1.0, 1.0 };
        GLfloat spot_direction[] = { -1.0, -1.0, 0.0 };

        glLightfv(GL_LIGHT1, GL_AMBIENT, light1_ambient);
        glLightfv(GL_LIGHT1, GL_DIFFUSE, light1_diffuse);
        glLightfv(GL_LIGHT1, GL_SPECULAR, light1_specular);
        glLightfv(GL_LIGHT1, GL_POSITION, light1_position);
        glLightf(GL_LIGHT1, GL_CONSTANT_ATTENUATION, 1.5);
        glLightf(GL_LIGHT1, GL_LINEAR_ATTENUATION, 0.5);
        glLightf(GL_LIGHT1, GL_QUADRATIC_ATTENUATION, 0.2);

        glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, 45.0);
        glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, spot_direction);
        glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, 2.0);

        glEnable(GL_LIGHT0);
        glEnable(GL_LIGHT1);
        glEnable(GL_LIGHT2);
//        glEnable(GL_LIGHT3);

        gluQuadricNormals(quadratic, GLU_SMOOTH);
        //gluQuadricDrawStyle( quadratic, GLU_FILL);
        gluQuadricTexture(quadratic, GL_TRUE);
    }

    void WorldOrientation::drawCube() {
    }

    void WorldOrientation::drawFloor() {
    }

    void WorldOrientation::update() {
        xAngle += 12.8f;                        // X Axis Rotation
        yAngle += 0.6f;                        // Y Axis Rotation
        zAngle += 0.7f;
    }

} /* namespace gal */
