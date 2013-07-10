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
            Color();
            virtual ~Color();
            float r,g,b,a;
    };

} /* namespace gal */
#endif /* COLOR_H_ */
