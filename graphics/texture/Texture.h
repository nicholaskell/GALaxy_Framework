/*
 * Texture.h
 *
 *  Created on: Jul 11, 2013
 *      Author: nicholaskell
 */

#ifndef GAL_TEXTURE_H_
#define GAL_TEXTURE_H_

#include <iostream>
#include <GL/gl.h>

namespace gal {

    /*
     *
     */
    class Texture {
        public:
            Texture();
            virtual ~Texture();
            virtual void loadPNG(std::string fileName);
            bool loadRAW(std::string filename, bool wrap = 1);
            GLuint getTextureId();
            void setTextureId(GLuint textureId);

        protected:
            GLuint textureId;
    };

} /* namespace gal */
#endif /* TEXTURE_H_ */
