/*
 * main.cpp
 *
 *  Created on: Jul 10, 2013
 *      Author: nicholaskell
 */

#include "graphics/Window.h"
#include "system/Clock.h"

#include "sample/RotatingCube.h"


gal::Window* mainWindow;



//gal::Clock* clock;



int main(int argc, char **argv) {
//    clock = new gal::Clock();
//    clock->start();
//    gal::Window window(argc, argv);
    mainWindow = new gal::Window(argc,argv);
    gal::RotatingCube* rotatingCube = gal::RotatingCube::getInstance();

    mainWindow->setIdleFunction(gal::RotatingCube::idleMethod);
    mainWindow->setDisplayFunction(gal::RotatingCube::drawMethod);

//    mainWindow = &window;
    mainWindow->create();
    void* nothing;
    mainWindow->runMainLoop(nothing);
    return 1;

}

