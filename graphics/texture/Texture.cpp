/*
 * Texture.cpp
 *
 *  Created on: Jul 11, 2013
 *      Author: nicholaskell
 */

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include "GL/gl.h"
#include "GL/glu.h"

#include "Texture.h"

namespace gal {

    Texture::Texture() {
        this->textureId = 0;

    }

    Texture::~Texture() {
        // TODO Auto-generated destructor stub
    }

    // load a 256x256 RGB .RAW file as a texture
    bool Texture::loadRAW(const char * filename, int wrap) {
//        GLuint texture;
        bool isLoaded = false;
        int width, height;
        char* data;
        FILE* file;

        // open texture data
        file = fopen(filename, "rb");
        if (file == NULL){
            return isLoaded;
        }else{

        }

        // allocate buffer
        width = 256;
        height = 256;
        data = (char*) malloc(width * height * 3);

        // read texture data
        fread(data, width * height * 3, 1, file);
        fclose(file);
        isLoaded = true;

        // allocate a texture name
        glGenTextures(1, &this->textureId);

        // select our current texture
        glBindTexture(GL_TEXTURE_2D, this->textureId);

        // select modulate to mix texture with color for shading
        glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

        // when texture area is small, bilinear filter the closest mipmap
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
                GL_LINEAR_MIPMAP_NEAREST);
        // when texture area is large, bilinear filter the first mipmap
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        // if wrap is true, the texture wraps over at the edges (repeat)
        //       ... false, the texture ends at the edges (clamp)
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,
                wrap ? GL_REPEAT : GL_CLAMP);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T,
                wrap ? GL_REPEAT : GL_CLAMP);

        // build our texture mipmaps
        gluBuild2DMipmaps(GL_TEXTURE_2D, 3, width, height, GL_RGB,
                GL_UNSIGNED_BYTE, data);

        // free buffer
        free(data);
//        this->textureId = texture;
//        return texture;
        return isLoaded;
    }

} /* namespace gal */
