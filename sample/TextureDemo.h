/*
 * TextureDemo.h
 *
 *  Created on: Jul 11, 2013
 *      Author: nicholaskell
 */

#ifndef TEXTUREDEMO_H_
#define TEXTUREDEMO_H_

#include <graphics/TexturedQuad.h>

namespace gal {

    /*
     *
     */
    class TextureDemo {
        public:
            static TextureDemo* getInstance();
            virtual ~TextureDemo();

            static void idleMethod();
            static void drawMethod();

            virtual void draw();
            virtual void idle();

        protected:
            static TextureDemo* instance;
            TextureDemo();
            TexturedQuad texturedQuad;
            float xAngle;
    };

} /* namespace gal */
#endif /* TEXTUREDEMO_H_ */
