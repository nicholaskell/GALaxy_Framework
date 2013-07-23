/*
 * TextureDemo.cpp
 *
 *  Created on: Jul 11, 2013
 *      Author: nicholaskell
 */

#include <GL/glut.h>
#include "TextureDemo.h"
#include "graphics/Color.h"

namespace gal {

    TextureDemo* TextureDemo::instance = NULL;

    TextureDemo* TextureDemo::getInstance() {
        if (!TextureDemo::instance) {
            TextureDemo::instance = new TextureDemo();
        }
        return TextureDemo::instance;
    }

    void TextureDemo::idleMethod() {
        TextureDemo::getInstance()->idle();
    }

    void TextureDemo::drawMethod() {
        TextureDemo::getInstance()->draw();
    }

    void TextureDemo::draw() {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear The Screen And The Depth Buffer
        glLoadIdentity();               // Reset The View

        glTranslatef(0.0f, 0.50f, -5.0f);       // move 5 units into the screen.
        //                glRotatef(45,1,0,0);

        glRotatef(xAngle, 1.0, 1.0, 1.0);     // Rotate On The X Axis

        this->texturedQuad.draw();

        glutSwapBuffers();
        xAngle += 0.9;
    }

    void TextureDemo::idle() {
    }

    TextureDemo::TextureDemo() {
        this->xAngle = 0.0;
        this->texturedQuad.loadRAW("resources/texture.raw", true);
    }

    TextureDemo::~TextureDemo() {
        // TODO Auto-generated destructor stub
    }

} /* namespace gal */
