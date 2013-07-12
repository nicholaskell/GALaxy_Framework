/*
 * FontDemo.h
 *
 *  Created on: Jul 12, 2013
 *      Author: nicholaskell
 */

#ifndef FONTDEMO_H_
#define FONTDEMO_H_

namespace gal {

    /*
     *
     */
    class FontDemo {
        protected:
            FontDemo();

        public:
            static FontDemo* getInstance();
            virtual ~FontDemo();

            static void idleMethod();
            static void drawMethod();

            virtual void draw();
            virtual void idle();

        protected:
            static FontDemo* instance;

    };

} /* namespace gal */
#endif /* FONTDEMO_H_ */
