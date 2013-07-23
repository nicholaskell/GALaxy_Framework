/*
 * RotatingCube.cpp
 *
 *  Created on: Jul 10, 2013
 *      Author: nicholaskell
 */

#include <cstddef>

#include <GL/glut.h>

#include <math.h> // sin(), cos()
#include "RotatingCube.h"
#include <graphics/Color.h>

namespace gal {

    RotatingCube* RotatingCube::instance = NULL;

    RotatingCube* RotatingCube::getInstance() {
        if(!RotatingCube::instance){
            RotatingCube::instance = new RotatingCube();
        }

        return RotatingCube::instance;
    }

    RotatingCube::RotatingCube() {
        quadratic = gluNewQuadric();
        xAngle = 0;
        yAngle = 0;
        zAngle = 0;
    }

    void RotatingCube::draw() {
        glClear(GL_COLOR_BUFFER_BIT | //
                GL_DEPTH_BUFFER_BIT | //
                GL_STENCIL_BUFFER_BIT //
        );
        glLoadIdentity();

        glPushMatrix();
        {
            //            glScalef(1, -1, 1);
            glTranslatef(0, 2, -20);
            glRotatef(zAngle, 1.0, 1.0, 1.0);
            this->drawCube();
            glRotatef(yAngle, 1.0, 1.0, 1.0);
            glTranslatef(0, 2, -20);
            glRotatef(xAngle, 1.0, 1.0, 1.0);

            glScalef(2, 2, 2);
            this->drawCube();

            glScalef(1, 1, 1);
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

        glutSwapBuffers();
    }

    void RotatingCube::idle() {
    }

    void RotatingCube::drawFloor() {
        float floorHeight = 0.0f;
        float floorSize = 200.0f;
        glPushMatrix();
        {
            //            float mcolor[] = { 0.50f, 0.50f, 0.50f, 1.0f };
            //            glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, mcolor);
            glTranslatef(0.0f, 0.0f, -floorSize / 2);
            glBegin(GL_QUADS);
            {
//                Color::setColor(Color::red);
                glBindTexture(GL_TEXTURE_2D, this->cubeTexture.getTextureId());
                glTexCoord2f(0.0f, 0.0f);
                glVertex3f(-floorSize, floorHeight, -floorSize); // Bottom Left Of The Texture and Quad
                glTexCoord2f(1.0f, 0.0f);
                glVertex3f(floorSize, floorHeight, -floorSize); // Bottom Right Of The Texture and Quad
                glTexCoord2f(1.0f, 1.0f);
                glVertex3f(floorSize, floorHeight, floorSize); // Top Right Of The Texture and Quad
                glTexCoord2f(0.0f, 1.0f);
                glVertex3f(-floorSize, floorHeight, floorSize); // Top Left Of The Texture and Quad

            }
            glEnd();
            //            glTranslatef(0.0f, 0.0f, floorSize / 2);
            //            glTranslatef(0.0f, floorHeight, 0.0f);

        }
    }

    void RotatingCube::drawCube() {
        glScalef(2, 2, 2);
        glBegin(GL_QUADS);                      // begin drawing a cube
        {

            // Front Face (note that the texture's corners have to match the quad's corners)

            glBindTexture(GL_TEXTURE_2D, this->cubeTexture.getTextureId());
            glTexCoord2f(0.0f, 0.0f);
            glVertex3f(-1.0f, -1.0f, 1.0f); // Bottom Left Of The Texture and Quad
            glTexCoord2f(1.0f, 0.0f);
            glVertex3f(1.0f, -1.0f, 1.0f); // Bottom Right Of The Texture and Quad
            glTexCoord2f(1.0f, 1.0f);
            glVertex3f(1.0f, 1.0f, 1.0f);  // Top Right Of The Texture and Quad
            glTexCoord2f(0.0f, 1.0f);
            glVertex3f(-1.0f, 1.0f, 1.0f);  // Top Left Of The Texture and Quad

            // Back Face
//            glColor3f(1, 1, 0);
            //            glBindTexture(GL_TEXTURE_2D, texture[0]);  // choose the texture to use.
            glBindTexture(GL_TEXTURE_2D, this->cubeTexture.getTextureId());
            glTexCoord2f(1.0f, 0.0f);
            glVertex3f(-1.0f, -1.0f, -1.0f); // Bottom Right Of The Texture and Quad
            glTexCoord2f(1.0f, 1.0f);
            glVertex3f(-1.0f, 1.0f, -1.0f); // Top Right Of The Texture and Quad
            glTexCoord2f(0.0f, 1.0f);
            glVertex3f(1.0f, 1.0f, -1.0f);  // Top Left Of The Texture and Quad
            glTexCoord2f(0.0f, 0.0f);
            glVertex3f(1.0f, -1.0f, -1.0f); // Bottom Left Of The Texture and Quad

            // Top Face
//            glColor3f(1, 0, 1);
            //            glBindTexture(GL_TEXTURE_2D, texture[0]);  // choose the texture to use.
            glBindTexture(GL_TEXTURE_2D, this->cubeTexture.getTextureId());
            glTexCoord2f(0.0f, 1.0f);
            glVertex3f(-1.0f, 1.0f, -1.0f);  // Top Left Of The Texture and Quad
            glTexCoord2f(0.0f, 0.0f);
            glVertex3f(-1.0f, 1.0f, 1.0f); // Bottom Left Of The Texture and Quad
            glTexCoord2f(1.0f, 0.0f);
            glVertex3f(1.0f, 1.0f, 1.0f); // Bottom Right Of The Texture and Quad
            glTexCoord2f(1.0f, 1.0f);
            glVertex3f(1.0f, 1.0f, -1.0f);  // Top Right Of The Texture and Quad

            // Bottom Face
//            Color::setColor(Color::green);
            //            glBindTexture(GL_TEXTURE_2D, texture[0]);  // choose the texture to use.
            glBindTexture(GL_TEXTURE_2D, this->cubeTexture.getTextureId());
            glTexCoord2f(1.0f, 1.0f);
            glVertex3f(-1.0f, -1.0f, -1.0f); // Top Right Of The Texture and Quad
            glTexCoord2f(0.0f, 1.0f);
            glVertex3f(1.0f, -1.0f, -1.0f);  // Top Left Of The Texture and Quad
            glTexCoord2f(0.0f, 0.0f);
            glVertex3f(1.0f, -1.0f, 1.0f); // Bottom Left Of The Texture and Quad
            glTexCoord2f(1.0f, 0.0f);
            glVertex3f(-1.0f, -1.0f, 1.0f); // Bottom Right Of The Texture and Quad

            // Right face
//            glColor3f(0, 1, 1);
            //            glBindTexture(GL_TEXTURE_2D, texture[0]);  // choose the texture to use.
            glBindTexture(GL_TEXTURE_2D, this->cubeTexture.getTextureId());
            glTexCoord2f(1.0f, 0.0f);
            glVertex3f(1.0f, -1.0f, -1.0f); // Bottom Right Of The Texture and Quad
            glTexCoord2f(1.0f, 1.0f);
            glVertex3f(1.0f, 1.0f, -1.0f);  // Top Right Of The Texture and Quad
            glTexCoord2f(0.0f, 1.0f);
            glVertex3f(1.0f, 1.0f, 1.0f);  // Top Left Of The Texture and Quad
            glTexCoord2f(0.0f, 0.0f);
            glVertex3f(1.0f, -1.0f, 1.0f);

            // Left Face
            glBindTexture(GL_TEXTURE_2D, this->cubeTexture.getTextureId());
            glTexCoord2f(0.0f, 0.0f);
            glVertex3f(-1.0f, -1.0f, -1.0f);
            glTexCoord2f(1.0f, 0.0f);
            glVertex3f(-1.0f, -1.0f, 1.0f);
            glTexCoord2f(1.0f, 1.0f);
            glVertex3f(-1.0f, 1.0f, 1.0f);
            glTexCoord2f(0.0f, 1.0f);
            glVertex3f(-1.0f, 1.0f, -1.0f);
        }
        glEnd();
    }

    void RotatingCube::setup() {

//        glMatrixMode(GL_PROJECTION);
//        glLoadIdentity();
//        gluPerspective(90, 640.0f / 480.0f, 1, 1000);
//        glMatrixMode(GL_MODELVIEW);
//        glLoadIdentity();
//        gluLookAt(0.0, 0.0, 640.0f / 2.0f, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

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

        glTranslatef(0, -15, -20);
        glRotatef(20, 1.0, 0, 0);

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

        gluQuadricNormals(quadratic, GLU_SMOOTH);
        gluQuadricTexture(quadratic, GL_TRUE);

        this->cubeTexture.loadRAW("resources/texture.RAW", true);
        this->floorTexture.loadRAW("resources/texture.RAW", true);

    }

    RotatingCube::~RotatingCube() {
    }

    void RotatingCube::idleMethod() {
        RotatingCube::getInstance()->idle();
    }

    void RotatingCube::drawMethod() {
        RotatingCube::getInstance()->draw();
    }

    void RotatingCube::setupMethod() {
        RotatingCube::getInstance()->setup();
    }

    void RotatingCube::update() {
        xAngle += 12.8f;                        // X Axis Rotation
        yAngle += 0.6f;                        // Y Axis Rotation
        zAngle += 0.7f;                        // Z Axis Rotation
        if (xAngle > 360) {
            xAngle = 0;
        }
        if (yAngle > 360) {
            yAngle = 0;
        }
        if (zAngle > 360) {
            zAngle = 0;
        }
    }

} /* namespace gal */
