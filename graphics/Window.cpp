/*
 * Window.cpp
 *
 *  Created on: Jun 27, 2013
 *      Author: nicholaskell
 */

//#include <pthread.h>
//#include <assert.h>
#include <GL/glut.h>
#include "Window.h"

namespace gal {

    int Window::numberOfWindows = 0;
    int Window::currentFPS = 0;
    int Window::frameCount = 0;
    Time Window::minimumTimeBetweenDraw;
    Time Window::maximumTimeBetweenDraw;
    Clock Window::lastDraw;
    Clock Window::fpsClock;
    IdleFunction Window::idleFunction;
    DisplayFunction Window::displayFunction;
    ReshapeFunction Window::reshapeFunction;
    KeyboardFunction Window::keyboardFunction;
    MouseFunction Window::mouseFunction;
    MotionFunction Window::motionFunction;
    PassiveMotionFunction Window::passiveMotionFunction;
    EntryFunction Window::entryFunction;
    VisibilityFunction Window::visibilityFunction;

    Window::Window(int argc, char **argv) {
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

        this->idleFunction = Window::defaultIdleMethod;
        this->displayFunction = Window::defaultDisplayMethod;
        this->reshapeFunction = Window::defaultReshapeMethod;
        this->keyboardFunction = Window::defaultKeyboardMethod;
        this->mouseFunction = Window::defaultMouseMethod;
        this->motionFunction = Window::defaultMotionMethod;
        this->passiveMotionFunction = Window::defaultPassiveMotionMethod;
        this->entryFunction = Window::defaultEntryMethod;
        this->visibilityFunction = Window::defaultVisibilityMethod;

        Window::minimumTimeBetweenDraw = milliseconds(10);
        Window::maximumTimeBetweenDraw = milliseconds(20);

    }

    Window::~Window() {

    }

    int Window::getNumberOfWindows() const {
        return Window::numberOfWindows;
    }

    bool Window::isFullscreen() const {
        return fullscreen;
    }

    void Window::setFullscreen(bool fullscreen) {
        this->fullscreen = fullscreen;
        if (fullscreen) {
            glutFullScreen();
        } else {
            glutReshapeWindow(this->width, this->height);
        }
    }

    int Window::getHeight() const {
        return height;
    }

    void Window::setHeight(int height) {
        this->height = height;
    }

    const std::string& Window::getTitle() const {
        return title;
    }

    void Window::setTitle(const std::string& title) {
        this->title = title;
    }

    int Window::getWidth() const {
        return width;
    }

    void Window::setWidth(int width) {
        this->width = width;
    }

    void Window::close() {
        glutDestroyWindow(this->windowNumber);
    }

    int Window::getWindowNumber() const {
        return windowNumber;
    }

    void* Window::runMainLoop(void* args) {
        glutMainLoop();
    }

    void Window::create() {
        this->windowNumber = glutCreateWindow(this->title.c_str());
        ++Window::numberOfWindows;

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

//        pthread_attr_t attr;
//        pthread_t posixThreadID;
//        int returnVal;
//
//        returnVal = pthread_attr_init(&attr);
//        assert(!returnVal);
//        returnVal = pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
//        assert(!returnVal);
//
//        int threadError = pthread_create(&posixThreadID, &attr,
//                &runMainLoop, NULL);
//
//        returnVal = pthread_attr_destroy(&attr);
//        assert(!returnVal);
//        if (threadError != 0) {
//            // Report an error.
//        }
//
//        pthread_t mainLoopThread;
//        glutMainLoop();
    }

    void Window::initOpenGL() {

    }

    void Window::reshape() {
        gluPerspective(45.0f, (GLfloat) width / (GLfloat) height, 0.1f, 100.0f);
    }

    void Window::defaultIdleMethod() {
        if (Window::lastDraw.getElapsedTime()
                > Window::maximumTimeBetweenDraw) {
            Window::defaultDisplayMethod();
        } else {
            if (Window::idleFunction != Window::defaultIdleMethod) {
                Window::idleFunction();
            }

        }

    }

    void Window::defaultDisplayMethod() {
        if(Window::defaultDisplayMethod != Window::displayFunction){
            Window::displayFunction();
        }


        Window::lastDraw.restart();
        ++Window::frameCount;
        if (Window::fpsClock.getElapsedTime().asSeconds() >= 1) {
            std::cout << Window::frameCount << std::endl;
            Window::currentFPS = Window::frameCount;
            Window::frameCount = 0;
            Window::fpsClock.restart();
        }
    }

    void Window::defaultReshapeMethod(int width, int height) {
        std::cout << "Default reshape method " << " \twidth:" << width
                << " \theight:" << height << std::endl;
    }

    void Window::defaultKeyboardMethod(unsigned char key, int x, int y) {
        std::cout << "default keyboard method - Key:" << key << " Ki:"
                << int(key) << " \tX:" << x << " \tY:" << y << std::endl;

        if (key == 27) {
            glutDestroyWindow(Window::numberOfWindows);
            --Window::numberOfWindows;
            /* exit the program...normal termination. */
            exit(0);
        }
    }

    void Window::defaultMouseMethod(int button, int state, int x, int y) {
        std::cout << "Default mouse method - Button:" << button << " \tX:" << x
                << " \tY:" << y << std::endl;
    }

    void Window::defaultMotionMethod(int x, int y) {
        std::cout << "Default motion method " << " \tX:" << x << " \tY:" << y
                << std::endl;
    }

    void Window::defaultPassiveMotionMethod(int x, int y) {
        std::cout << "Default passive method " << " \tX:" << x << " \tY:" << y
                << std::endl;
    }

    void Window::defaultEntryMethod(int state) {
        std::cout << "Default entry method - state: " << state << std::endl;
    }

    DisplayFunction Window::getDisplayFunction() const {
        return displayFunction;
    }

    void Window::setDisplayFunction(DisplayFunction displayFunction) {
        this->displayFunction = displayFunction;
    }

    EntryFunction Window::getEntryFunction() const {
        return entryFunction;
    }

    void Window::setEntryFunction(EntryFunction entryFunction) {
        this->entryFunction = entryFunction;
    }

    IdleFunction Window::getIdleFunction() const {
        return idleFunction;
    }

    void Window::setIdleFunction(IdleFunction idleFunction) {
        this->idleFunction = idleFunction;
    }

    KeyboardFunction Window::getKeyboardFunction() const {
        return keyboardFunction;
    }

    void Window::setKeyboardFunction(KeyboardFunction keyboardFunction) {
        this->keyboardFunction = keyboardFunction;
    }

    MotionFunction Window::getMotionFunction() const {
        return motionFunction;
    }

    void Window::setMotionFunction(MotionFunction motionFunction) {
        this->motionFunction = motionFunction;
    }

    MouseFunction Window::getMouseFunction() const {
        return mouseFunction;
    }

    void Window::setMouseFunction(MouseFunction mouseFunction) {
        this->mouseFunction = mouseFunction;
    }

    PassiveMotionFunction Window::getPassiveMotionFunction() const {
        return passiveMotionFunction;
    }

    void Window::setPassiveMotionFunction(
            PassiveMotionFunction passiveMotionFunction) {
        this->passiveMotionFunction = passiveMotionFunction;
    }

    ReshapeFunction Window::getReshapeFunction() const {
        return reshapeFunction;
    }

    void Window::setReshapeFunction(ReshapeFunction reshapeFunction) {
        this->reshapeFunction = reshapeFunction;
    }

    VisibilityFunction Window::getVisibilityFunction() const {
        return visibilityFunction;
    }

    void Window::setVisibilityFunction(VisibilityFunction visibilityFunction) {
        this->visibilityFunction = visibilityFunction;
    }

    int Window::getCurrentFps() const {
        return currentFPS;
    }

    void Window::setCurrentFps(int currentFps) {
        currentFPS = currentFps;
    }

    void Window::defaultVisibilityMethod(int state) {
    }

} /* namespace gal */
