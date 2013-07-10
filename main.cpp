/*
 * main.cpp
 *
 *  Created on: Jul 10, 2013
 *      Author: nicholaskell
 */

#include "graphics/Window.h"
#include "system/Clock.h"

gal::Window* mainWindow;



//gal::Clock* clock;

void idleLoop() {


    static gal::Clock clock;
//    std::cout << "Current time secs:"<<clock.getElapsedTime().asSeconds() << std::endl;
    if (clock.getElapsedTime().asSeconds() > 30) {
        mainWindow->close();
        exit(0);
    }
//    mainWindow::defaultDisplayMethod();
//    std::cout << "Current time secs:"<<clock.getElapsedTime().asSeconds() << std::endl;

//    std::cout << "Current time secs:"<<clock.getElapsedTime().asSeconds() << std::endl;
}

int main(int argc, char **argv) {
//    clock = new gal::Clock();
//    clock->start();
//    gal::Window window(argc, argv);
    mainWindow = new gal::Window(argc,argv);
    mainWindow->setIdleFunction(idleLoop);

//    mainWindow = &window;
    mainWindow->create();
    void* nothing;
    mainWindow->runMainLoop(nothing);
    return 1;

}

