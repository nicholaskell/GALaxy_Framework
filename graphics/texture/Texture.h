/*
 * Texture.h
 *
 *  Created on: Jul 11, 2013
 *      Author: nicholaskell
 */

#ifndef GAL_TEXTURE_H_
#define GAL_TEXTURE_H_

#include <iostream>

namespace gal {

    /*
     *
     */
    class Texture {
        public:
            Texture();
            virtual ~Texture();
            virtual void loadPNG(std::string fileName);
            bool loadRAW(const char * filename, int wrap);

        protected:
            GLuint textureId;
    };

} /* namespace gal */
#endif /* TEXTURE_H_ */
