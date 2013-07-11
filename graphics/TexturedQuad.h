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

        protected:
            Texture texture;
            Point points[NUMBER_OF_POINTS_IN_A_QUAD];

    };

} /* namespace gal */
#endif /* TEXTUREDQUAD_H_ */
