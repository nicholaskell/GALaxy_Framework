/*
 * Config.h
 *
 *  Created on: Jul 10, 2013
 *      Author: nicholaskell
 */

#ifndef CONFIG_H_
#define CONFIG_H_


////////////////////////////////////////////////////////////
// ID the OS
#define GAL_SYSTEM_ID_LINUX     1
#define GAL_SYSTEM_ID_OSX       2
#define GAL_SYSTEM_ID_UNIX      3
#define GAL_SYSTEM_ID_FREEBSD   4
#define GAL_SYSTEM_ID_WIN       5

#if defined(_WIN32) || defined(__WIN32__)

    #define GAL_SYSTEM_WINDOWS
    #ifndef NOMINMAX
        #define NOMINMAX
    #endif
    #define GAL_SYSTEM GAL_SYSTEM_ID_WIN

#elif defined(linux) || defined(__linux)

    #define GAL_SYSTEM_LINUX
    #define GAL_SYSTEM GAL_SYSTEM_ID_LINUX


#elif defined(__APPLE__) || defined(MACOSX) || defined(macintosh) || defined(Macintosh)

    #define GAL_SYSTEM_MACOS
    #define GAL_SYSTEM GAL_SYSTEM_ID_OSX


#elif defined(__FreeBSD__) || defined(__FreeBSD_kernel__)
    #define GAL_SYSTEM_FREEBSD
    #define GAL_SYSTEM GAL_SYSTEM_ID_FREEBSD

#else
    #error OS Unknown...
#endif






namespace gal {

// 8 bits integer types
    typedef signed char Int8;
    typedef unsigned char Uint8;

// 16 bits integer types
    typedef signed short Int16;
    typedef unsigned short Uint16;

// 32 bits integer types
    typedef signed int Int32;
    typedef unsigned int Uint32;

// 64 bits integer types
#if defined(_MSC_VER)
    typedef signed __int64 Int64;
    typedef unsigned __int64 Uint64;
#else
    typedef signed long long Int64;
    typedef unsigned long long Uint64;
#endif
}
#endif /* CONFIG_H_ */
