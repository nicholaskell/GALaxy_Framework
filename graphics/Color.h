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

            static Color black;
            static Color white;
            static Color red;
            static Color green;
            static Color blue;

            Color();
            Color(float r,float g,float b);
            Color(float r,float g,float b,float a);
            virtual ~Color();


            void setHex(unsigned char r,unsigned char g,unsigned char b);
            float r,g,b,a;

            static void setColor(Color);

            //TODO Add operator overloading for color math

            // brightness  =  sqrt( .241 R^2 + .691 G^2 + .068 B^2 )  #This si a formula for how humans perceive color brightness
            // I will use this when comparing using the > and < operators.
    };

} /* namespace gal */
#endif /* COLOR_H_ */
