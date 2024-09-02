#pragma once

#if defined(PHSX2D_PLATFORM_WINDOWS)

    #if defined(_MSC_VER) // MSBuild
        #if defined(PHSX2D_BUILD_SHARED_LIB)
            #define PHYSX2D_API __declspec(dllexport)
        #else
            #define PHYSX2D_API __declspec(dllimport)
        #endif

    #elif defined(__MINGW32__) || defined(__MINGW64__) // MinGW
        #if defined(PHSX2D_BUILD_SHARED_LIB)
            #define PHYSX2D_API __attribute__((dllexport))
        #else
            #define PHYSX2D_API __attribute__((dllimport))
        #endif

    #else 
        #define PHYSX2D_API 
    #endif

#elif defined(PHSX2D_PLATFORM_LINUX) 

    #if defined(__GNUC__) // GCC 
        #if !defined(PHSX2D_BUILD_SHARED_LIB)
            #define PHYSX2D_API __attribute__((visibility("default")))
        #else
            #define PHYSX2D_API 
        #endif

    #elif defined(__clang__) // Clang
        #if defined(PHSX2D_BUILD_SHARED_LIB)
            #define PHYSX2D_API __attribute__((visibility("default")))
        #else
            #define PHYSX2D_API 
        #endif

    #else 
        #define PHYSX2D_API 
    #endif

#elif defined(PHSX2D_PLATFORM_APPLE)

    #if defined(__clang__) // Clang
        #if !defined(PHSX2D_BUILD_SHARED_LIB)
            #define PHYSX2D_API __attribute__((visibility("default")))
        #else
            #define PHYSX2D_API 
        #endif

    #else 
        #define PHYSX2D_API 
    #endif

#else 
    #define PHYSX2D_API 
#endif

