/*
 * main.cpp
 *
 *  Created on: Jul 10, 2013
 *      Author: nicholaskell
 */

#include "graphics/Window.h"
#include "system/Clock.h"

#include "sample/RotatingCube.h"
#include "sample/TextureDemo.h"


gal::Window* mainWindow;



//gal::Clock* clock;



int main(int argc, char **argv) {
//    clock = new gal::Clock();
//    clock->start();
//    gal::Window window(argc, argv);
    mainWindow = new gal::Window(argc,argv);

//    gal::TextureDemo* rotatingCube = gal::TextureDemo::getInstance();

    int demoNumber = 1;
    switch(demoNumber){
        default:
        case 0:
            mainWindow->setIdleFunction(gal::RotatingCube::idleMethod);
            mainWindow->setDisplayFunction(gal::RotatingCube::drawMethod);
            break;
        case 1:
            mainWindow->setIdleFunction(gal::TextureDemo::idleMethod);
            mainWindow->setDisplayFunction(gal::TextureDemo::drawMethod);
            break;
    }

//    mainWindow = &window;
    mainWindow->create();
    void* nothing;
    mainWindow->runMainLoop(nothing);
    return 1;

}

