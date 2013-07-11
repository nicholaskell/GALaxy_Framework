/*
 * Color.h
 *
 *  Created on: Jul 10, 2013
 *      Author: nicholaskell
 */

#ifndef COLOR_H_
#define COLOR_H_

namespace gal {

    class Color {
        public:

            static Color red;
            static Color green;
            static Color blue;

            Color();
            Color(float,float,float);
            Color(float,float,float,float);
            virtual ~Color();
            float r,g,b,a;

            static void setColor(Color);

            //TODO Add operator overloading for color math
    };

} /* namespace gal */
#endif /* COLOR_H_ */
