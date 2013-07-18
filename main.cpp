/*
 * main.cpp
 *
 *  Created on: Jul 10, 2013
 *      Author: nicholaskell
 */

#include "window/MainWindow.h"
#include "system/time/Clock.h"

#include "sample/RotatingCube.h"
#include "sample/TextureDemo.h"
#include "sample/FontDemo.h"

//gal::Clock* clock;

int main(int argc, char **argv) {

    gal::MainWindow* mainWindow;
    mainWindow = gal::MainWindow::getInstance(argc, argv);

//    gal::TextureDemo* rotatingCube = gal::TextureDemo::getInstance();


    int demoNumber = 1;
    switch (demoNumber) {
        default:
        case 0:
//            mainWindow->setIdleFunction(gal::RotatingCube::idleMethod);
//            mainWindow->setDisplayFunction(gal::RotatingCube::drawMethod);
//            mainWindow->setSetupOpenGLFunction(gal::RotatingCube::setupMethod);
            break;
        case 1:
            mainWindow->setIdleFunction(gal::TextureDemo::idleMethod);
            mainWindow->setDisplayFunction(gal::TextureDemo::drawMethod);
            break;
        case 2:
//            mainWindow->setIdleFunction(gal::FontDemo::idleMethod);
//            mainWindow->setDisplayFunction(gal::FontDemo::drawMethod);
//            mainWindow->setSetupOpenGLFunction(gal::FontDemo::setupMethod);
            break;
    }

//    mainWindow = &window;
    mainWindow->create();
    void* nothing;
    mainWindow->runMainLoop(nothing);
    return 1;

}

