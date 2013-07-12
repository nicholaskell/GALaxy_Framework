/*
 * TexturedQuad.cpp
 *
 *  Created on: Jul 11, 2013
 *      Author: nicholaskell
 */

#include "TexturedQuad.h"

#include "graphics/Color.h"

namespace gal {

    TexturedQuad::TexturedQuad() {
        // TODO Auto-generated constructor stub

        this->bl = &this->points[0];
        this->br = &this->points[1];
        this->tr = &this->points[2];
        this->tl = &this->points[3];

        bl->x = -1;
        bl->y = -1;
        bl->z = 0;

        br->x = 1;
        br->y = -1;
        br->z = 0;

        tr->x = 1;
        tr->y = 1;
        tr->z = 0;

        tl->x = -1;
        tl->y = 1;
        tl->z = 0;
    }

    TexturedQuad::~TexturedQuad() {
        // TODO Auto-generated destructor stub
    }

    void TexturedQuad::draw() {

        glBegin(GL_QUADS);                      // begin drawing a cube
        {
//            Color::setColor(Color::red);
            glBindTexture(GL_TEXTURE_2D, texture.getId()); // choose the texture to use.
            glTexCoord2f(0.0f, 0.0f);
            glVertex3f(bl->x,bl->y,bl->z); // Bottom Left Of The Texture and Quad
            glTexCoord2f(1.0f, 0.0f);
            glVertex3f(br->x,br->y,br->z); // Bottom Right Of The Texture and Quad
            glTexCoord2f(1.0f, 1.0f);
            glVertex3f(tr->x,tr->y,tr->z);  // Top Right Of The Texture and Quad
            glTexCoord2f(0.0f, 1.0f);
            glVertex3f(tl->x,tl->y,tl->z);  // Top Left Of The Texture and Quad
        }
        glEnd();
    }

    void TexturedQuad::setPoints(Point points[NUMBER_OF_POINTS_IN_A_QUAD]) {
        //TODO override = operator in Point
    }

    void TexturedQuad::setPoints(Point bl, Point br, Point tr, Point tl) {
        //TODO override = operator in Point
    }

    bool TexturedQuad::loadRAW(std::string filename, bool wrapping) {
        return this->texture.loadRAW(filename, wrapping);
    }

} /* namespace gal */
