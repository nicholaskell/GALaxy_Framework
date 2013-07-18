/*
 * FontDemo.cpp
 *
 *  Created on: Jul 12, 2013
 *      Author: nicholaskell
 */

#include "FontDemo.h"

#define FONT_FILE "/opt/X11/share/fonts/TTF/VeraSe.ttf"
#include <iostream>
#include <math.h> // sin(), cos()
#include <stdlib.h> // exit()
#include <GL/glut.h>

#include <FTGL/ftgl.h>

static FTFont *font[3];
static int fontindex = 0;
static int lastfps = 0;
static int frames = 0;

//
//  FTHaloGlyph is a derivation of FTPolygonGlyph that also displays a
//  halo of FTOutlineGlyph objects at varying positions and with varying
//  outset values.
//
class FTHaloGlyph: public FTPolygonGlyph {
    public:
        FTHaloGlyph(FT_GlyphSlot glyph) :
                FTPolygonGlyph(glyph, 0, true) {
            for (int i = 0; i < 5; i++) {
                subglyph[i] = new FTOutlineGlyph(glyph, i, true);
            }
        }

    private:
        const FTPoint& Render(const FTPoint& pen, int renderMode) {
            glPushMatrix();
            for (int i = 0; i < 5; i++) {
                glTranslatef(0.0, 0.0, -2.0);
                subglyph[i]->Render(pen, renderMode);
            }
            glPopMatrix();

            return FTPolygonGlyph::Render(pen, renderMode);
        }

        FTGlyph *subglyph[5];
};

//
//  FTHaloFont is a simple FTFont derivation that builds FTHaloGlyph
//  objects.
//
class FTHaloFont: public FTFont {
    public:
        FTHaloFont(char const *fontFilePath) :
                FTFont(fontFilePath) {
        }

    private:
        virtual FTGlyph* MakeGlyph(FT_GlyphSlot slot) {
            return new FTHaloGlyph(slot);
        }
};

namespace gal {

    void FontDemo::idle() {
    }

    void FontDemo::draw() {

        int now = glutGet(GLUT_ELAPSED_TIME);

        float n = (float) now / 20.;
        float t1 = sin(n / 80);
        float t2 = sin(n / 50 + 1);
        float t3 = sin(n / 30 + 2);

        float ambient[4] =
//        { (t1 + 2.0) / 3, (t2 + 2.0) / 3, (t3 + 2.0) / 3, 0.3 };
        { ( 2.0) / 3, ( 2.0) / 3, ( 2.0) / 3, 0.3 };
        float diffuse[4] = { 1.0, 0.9, 0.9, 1.0 };
        float specular[4] = { 1.0, 0.7, 0.7, 1.0 };
        float position[4] = { 100.0, 100.0, 0.0, 1.0 };

        float front_ambient[4] = { 0.7, 0.7, 0.7, 0.0 };

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glEnable(GL_LIGHTING);
        glEnable(GL_DEPTH_TEST);

        glPushMatrix();
        {

            glRotatef(n / 1.11, 0.0, 1.0, 0.0);
            glRotatef(n / 2.23, 1.0, 0.0, 0.0);
            glRotatef(n / 3.17, 0.0, 0.0, 1.0);
            glTranslatef(-0.9, -0.2, -10.0);
            glLightfv(GL_LIGHT1, GL_AMBIENT, ambient);
            glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuse);
            glLightfv(GL_LIGHT1, GL_SPECULAR, specular);
            glLightfv(GL_LIGHT1, GL_POSITION, position);
            glEnable(GL_LIGHT1);
        }
        glPopMatrix();

        glPushMatrix();
        {
            glMaterialfv(GL_FRONT, GL_AMBIENT, front_ambient);
            glColorMaterial(GL_FRONT, GL_DIFFUSE);
            glTranslatef(0.0, 0.0, 20.0);
//            glRotatef(n / 1.11, 0.0, 1.0, 0.0);
//            glRotatef(n / 2.23, 1.0, 0.0, 0.0);
//            glRotatef(n / 3.17, 0.0, 0.0, 1.0);
            glTranslatef(-260.0, -0.2, 0.0);
            glColor3f(1.0, 1.0, 1.0);
            font[fontindex]->Render("Hoya!");

            glTranslatef(0.0, -200.2, 0.0);
            glRotatef(abs(30.0f - ((float)((int)n%60)))-30, 3.0, 0.0, 0.0);
            font[fontindex]->Render("Hoya!");
        }
        glPopMatrix();

        glutSwapBuffers();

        frames++;

        if (now - lastfps > 5000) {
            fprintf(stderr, "%i frames in 5.0 seconds = %g FPS\n", frames,
                    frames * 1000. / (now - lastfps));
            lastfps += 5000;
            frames = 0;
        }
//        fprintf(stderr, "%i frames in 5.0 seconds = %g FPS\n", frames,
//                            frames * 1000. / (now - lastfps));

    }

    FontDemo::FontDemo() {
    }

    FontDemo::~FontDemo() {
    }

    void FontDemo::setup() {
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        gluPerspective(90, 640.0f / 480.0f, 1, 1000);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        gluLookAt(0.0, 0.0, 640.0f / 2.0f, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
        // Initialise FTGL stuff
        char const *file = FONT_FILE;
        font[0] = new FTExtrudeFont(file);
        font[1] = new FTBufferFont(file);
        font[2] = new FTHaloFont(file);

//        if (font[0]->Error() || font[1]->Error() || font[2]->Error()) {
//            fprintf(stderr, "%s: could not load font `%s'\n", argv[0], file);
//            return EXIT_FAILURE;
//        }

        font[0]->FaceSize(80);
        font[0]->Depth(10);
        font[0]->Outset(0, 3);
        font[0]->CharMap(ft_encoding_unicode);

        font[1]->FaceSize(80);
        font[1]->CharMap(ft_encoding_unicode);

        font[2]->FaceSize(80);
        font[2]->CharMap(ft_encoding_unicode);


        std::cout << "Setup FontDemo." << std::endl;
    }

} /* namespace gal */
