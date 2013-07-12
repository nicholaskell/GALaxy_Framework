/*
 * TexturedQuad.h
 *
 *  Created on: Jul 11, 2013
 *      Author: nicholaskell
 */

#ifndef TEXTUREDQUAD_H_
#define TEXTUREDQUAD_H_

#include "graphics/geometry/Point.h"
#include "graphics/texture/Texture.h"

#define NUMBER_OF_POINTS_IN_A_QUAD 4

namespace gal {

    /*
     *
     */
    class TexturedQuad {
        public:
            TexturedQuad();
            virtual ~TexturedQuad();
            virtual void draw();
            virtual void setPoints(Point points[NUMBER_OF_POINTS_IN_A_QUAD]);
            virtual void setPoints(Point bl,Point br,Point tr,Point tl);
            virtual bool loadRAW(std::string filename, bool wrap = true);

        protected:
            Texture texture;
            Point points[NUMBER_OF_POINTS_IN_A_QUAD];
            Point* bl;
            Point* br;
            Point* tr;
            Point* tl;

    };

} /* namespace gal */
#endif /* TEXTUREDQUAD_H_ */
