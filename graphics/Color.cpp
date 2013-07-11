/*
 * Color.cpp
 *
 *  Created on: Jul 10, 2013
 *      Author: nicholaskell
 */


#include <GL/gl.h>
#include "Color.h"

namespace gal {

    Color Color::red(1,0,0);
    Color Color::green(0,1,0);
    Color Color::blue(0,0,1);

    Color::Color() {
        // TODO Auto-generated constructor stub
        r = 0.5;
        g = 0.5;
        b = 0.5;
        a = 1;
    }

    Color::~Color() {
        // TODO Auto-generated destructor stub
    }

    Color::Color(float r, float g, float b) {
        this->r = r;
        this->g = g;
        this->b = b;
        this->a = 1.0f;
    }

    Color::Color(float r, float g, float b, float a) {
        this->r = r;
        this->g = g;
        this->b = b;
        this->a = 1.0f;
    }

    void Color::setColor(Color color) {
        glColor4f(color.r,color.g,color.b,color.a);
    }

} /* namespace gal */
