/*
 * Audio.cpp
 *
 *  Created on: Jun 18, 2013
 *      Author: nicholas
 */

#include <stddef.h>
#include <iostream>

#include "Audio.h"

namespace gal {

    ALCdevice* Audio::device = alcOpenDevice(
            alcGetString(NULL, ALC_DEFAULT_DEVICE_SPECIFIER));
    ALCcontext* Audio::context = alcCreateContext(device, NULL);

    Audio::Audio() {

    }

    Audio::~Audio() {

    }

    void Audio::initilize() {
        if (Audio::device) {
            alcCloseDevice(Audio::device);
        }
        if (Audio::context) {
            alcDestroyContext(Audio::context);
        }

        const ALCchar *defaultDeviceName = alcGetString(NULL, ALC_DEFAULT_DEVICE_SPECIFIER);
        Audio::device = alcOpenDevice(defaultDeviceName);
        if (Audio::device) {
            std::cout << "Created audio device:" << defaultDeviceName << "." << std::endl;
        }
        std::cout << "Device: " << alcGetString(device, ALC_DEVICE_SPECIFIER)
                    << std::endl;
        alGetError();

        Audio::context = alcCreateContext(Audio::device, NULL);
        if (Audio::context) {
            std::cout << "Created audio context." << std::endl;
        }

        if (!alcMakeContextCurrent(Audio::context)) {
            std::cerr << "Failed to make default audio context current." << std::endl;
        } else {
            std::cout << "Created context as current" << std::endl;
        }

        ALfloat listenerOri[] = { 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f };
        /* set orientation */
            alListener3f(AL_POSITION, 0, 0, 1.0f);
            alListener3f(AL_VELOCITY, 0, 0, 0);
            alListenerfv(AL_ORIENTATION, listenerOri);



    }

} /* namespace nk */
