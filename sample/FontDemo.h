/*
 * FontDemo.h
 *
 *  Created on: Jul 12, 2013
 *      Author: nicholaskell
 */

#ifndef FONTDEMO_H_
#define FONTDEMO_H_

#include <graphics/GalaxyApplicationBase.h>

namespace gal {

    /*
     *
     */
    class FontDemo: public GalaxyApplicationBase<FontDemo> {
        protected:

        public:
            FontDemo();
            ~FontDemo();

            void draw();
            void idle();
            void setup();

        protected:

    };

} /* namespace gal */
#endif /* FONTDEMO_H_ */
