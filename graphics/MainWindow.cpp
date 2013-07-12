/*
 * Window.cpp
 *
 *  Created on: Jun 27, 2013
 *      Author: nicholaskell
 */

//#include <pthread.h>
//#include <assert.h>
#include <GL/glut.h>
#include "MainWindow.h"

namespace gal {

    MainWindow* MainWindow::instance = NULL;

    int MainWindow::numberOfWindows = 0;
    int MainWindow::currentFPS = 0;
    int MainWindow::frameCount = 0;
    Time MainWindow::minimumTimeBetweenDraw;
    Time MainWindow::maximumTimeBetweenDraw;
    Clock MainWindow::lastDraw;
    Clock MainWindow::fpsClock;
    IdleFunction MainWindow::idleFunction;
    DisplayFunction MainWindow::displayFunction;
    ReshapeFunction MainWindow::reshapeFunction;
    KeyboardFunction MainWindow::keyboardFunction;
    MouseFunction MainWindow::mouseFunction;
    MotionFunction MainWindow::motionFunction;
    PassiveMotionFunction MainWindow::passiveMotionFunction;
    EntryFunction MainWindow::entryFunction;
    VisibilityFunction MainWindow::visibilityFunction;

    MainWindow::MainWindow(int argc, char **argv) {
        this->title = "Default GALaxy window";

//        this->currentFPS = 0;
        this->width = 640;
        this->height = 480;
        this->fullscreen = false;
        this->windowNumber = -1;
        glutInit(&argc, argv);
        glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_ALPHA | GLUT_DEPTH);
        glutInitWindowSize(width, height);
        glutInitWindowPosition(0, 0);

        this->idleFunction = MainWindow::defaultIdleMethod;
        this->displayFunction = MainWindow::defaultDisplayMethod;
        this->reshapeFunction = MainWindow::defaultReshapeMethod;
        this->keyboardFunction = MainWindow::defaultKeyboardMethod;
        this->mouseFunction = MainWindow::defaultMouseMethod;
        this->motionFunction = MainWindow::defaultMotionMethod;
        this->passiveMotionFunction = MainWindow::defaultPassiveMotionMethod;
        this->entryFunction = MainWindow::defaultEntryMethod;
        this->visibilityFunction = MainWindow::defaultVisibilityMethod;

        MainWindow::minimumTimeBetweenDraw = milliseconds(10);
        MainWindow::maximumTimeBetweenDraw = milliseconds(20);

    }

    MainWindow::~MainWindow() {

    }

    int MainWindow::getNumberOfWindows() const {
        return MainWindow::numberOfWindows;
    }

    bool MainWindow::isFullscreen() const {
        return fullscreen;
    }

    void MainWindow::setFullscreen(bool fullscreen) {
        this->fullscreen = fullscreen;
        if (fullscreen) {
            glutFullScreen();
        } else {
            glutReshapeWindow(this->width, this->height);
        }
    }

    int MainWindow::getHeight() const {
        return height;
    }

    void MainWindow::setHeight(int height) {
        this->height = height;
    }

    const std::string& MainWindow::getTitle() const {
        return title;
    }

    void MainWindow::setTitle(const std::string& title) {
        this->title = title;
    }

    int MainWindow::getWidth() const {
        return width;
    }

    void MainWindow::setWidth(int width) {
        this->width = width;
    }

    void MainWindow::close() {
        glutDestroyWindow(this->windowNumber);
    }

    int MainWindow::getWindowNumber() const {
        return windowNumber;
    }

    void* MainWindow::runMainLoop(void* args) {
        glutMainLoop();
    }

    void MainWindow::create() {
        this->windowNumber = glutCreateWindow(this->title.c_str());
        ++MainWindow::numberOfWindows;

        glEnable(GL_TEXTURE_2D);            // Enable Texture Mapping
        glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
        glClearDepth(1.0);              // Enables Clearing Of The Depth Buffer
        glDepthFunc(GL_LESS);           // The Type Of Depth Test To Do
        glEnable(GL_DEPTH_TEST);            // Enables Depth Testing
        glShadeModel(GL_SMOOTH);            // Enables Smooth Color Shading

        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();               // Reset The Projection Matrix

        gluPerspective(45.0f, (GLfloat) width / (GLfloat) height, 0.1f, 100.0f); // Calculate The Aspect Ratio Of The Window

        glMatrixMode(GL_MODELVIEW);

        glutDisplayFunc(defaultDisplayMethod);
        glutIdleFunc(defaultIdleMethod);
        glutReshapeFunc(this->reshapeFunction);
        glutKeyboardFunc(this->keyboardFunction);


        std::cout << "OpenGL version:"<< glGetString(GL_VERSION) << std::endl;

    }

    void MainWindow::initOpenGL() {

    }

    void MainWindow::reshape() {
        gluPerspective(45.0f, (GLfloat) width / (GLfloat) height, 0.1f, 100.0f);
    }

    void MainWindow::defaultIdleMethod() {
        if (MainWindow::lastDraw.getElapsedTime()
                > MainWindow::maximumTimeBetweenDraw) {
            MainWindow::defaultDisplayMethod();
        } else {
            if (MainWindow::idleFunction != MainWindow::defaultIdleMethod) {
                MainWindow::idleFunction();
            }

        }

    }

    void MainWindow::defaultDisplayMethod() {
        if(MainWindow::defaultDisplayMethod != MainWindow::displayFunction){
            MainWindow::displayFunction();
        }


        MainWindow::lastDraw.restart();
        ++MainWindow::frameCount;
        if (MainWindow::fpsClock.getElapsedTime().asSeconds() >= 1) {
            std::cout << MainWindow::frameCount << std::endl;
            MainWindow::currentFPS = MainWindow::frameCount;
            MainWindow::frameCount = 0;
            MainWindow::fpsClock.restart();
        }
    }

    void MainWindow::defaultReshapeMethod(int width, int height) {
        std::cout << "Default reshape method " << " \twidth:" << width
                << " \theight:" << height << std::endl;
    }

    void MainWindow::defaultKeyboardMethod(unsigned char key, int x, int y) {
        std::cout << "default keyboard method - Key:" << key << " Ki:"
                << int(key) << " \tX:" << x << " \tY:" << y << std::endl;

        if (key == 27) {
            glutDestroyWindow(MainWindow::numberOfWindows);
            --MainWindow::numberOfWindows;
            /* exit the program...normal termination. */
            exit(0);
        }
    }

    void MainWindow::defaultMouseMethod(int button, int state, int x, int y) {
        std::cout << "Default mouse method - Button:" << button << " \tX:" << x
                << " \tY:" << y << std::endl;
    }

    void MainWindow::defaultMotionMethod(int x, int y) {
        std::cout << "Default motion method " << " \tX:" << x << " \tY:" << y
                << std::endl;
    }

    void MainWindow::defaultPassiveMotionMethod(int x, int y) {
        std::cout << "Default passive method " << " \tX:" << x << " \tY:" << y
                << std::endl;
    }

    void MainWindow::defaultEntryMethod(int state) {
        std::cout << "Default entry method - state: " << state << std::endl;
    }

    DisplayFunction MainWindow::getDisplayFunction() const {
        return displayFunction;
    }

    void MainWindow::setDisplayFunction(DisplayFunction displayFunction) {
        this->displayFunction = displayFunction;
    }

    EntryFunction MainWindow::getEntryFunction() const {
        return entryFunction;
    }

    void MainWindow::setEntryFunction(EntryFunction entryFunction) {
        this->entryFunction = entryFunction;
    }

    IdleFunction MainWindow::getIdleFunction() const {
        return idleFunction;
    }

    void MainWindow::setIdleFunction(IdleFunction idleFunction) {
        this->idleFunction = idleFunction;
    }

    KeyboardFunction MainWindow::getKeyboardFunction() const {
        return keyboardFunction;
    }

    void MainWindow::setKeyboardFunction(KeyboardFunction keyboardFunction) {
        this->keyboardFunction = keyboardFunction;
    }

    MotionFunction MainWindow::getMotionFunction() const {
        return motionFunction;
    }

    void MainWindow::setMotionFunction(MotionFunction motionFunction) {
        this->motionFunction = motionFunction;
    }

    MouseFunction MainWindow::getMouseFunction() const {
        return mouseFunction;
    }

    void MainWindow::setMouseFunction(MouseFunction mouseFunction) {
        this->mouseFunction = mouseFunction;
    }

    PassiveMotionFunction MainWindow::getPassiveMotionFunction() const {
        return passiveMotionFunction;
    }

    void MainWindow::setPassiveMotionFunction(
            PassiveMotionFunction passiveMotionFunction) {
        this->passiveMotionFunction = passiveMotionFunction;
    }

    ReshapeFunction MainWindow::getReshapeFunction() const {
        return reshapeFunction;
    }

    void MainWindow::setReshapeFunction(ReshapeFunction reshapeFunction) {
        this->reshapeFunction = reshapeFunction;
    }

    VisibilityFunction MainWindow::getVisibilityFunction() const {
        return visibilityFunction;
    }

    void MainWindow::setVisibilityFunction(VisibilityFunction visibilityFunction) {
        this->visibilityFunction = visibilityFunction;
    }

    int MainWindow::getCurrentFps() const {
        return currentFPS;
    }

    void MainWindow::setCurrentFps(int currentFps) {
        currentFPS = currentFps;
    }

    MainWindow* MainWindow::getInstance(int argc, char** argv) {
        if(!MainWindow::instance){
            MainWindow::instance = new MainWindow(argc, argv);
        }

        return MainWindow::instance;
    }

    void MainWindow::defaultVisibilityMethod(int state) {
    }

} /* namespace gal */
