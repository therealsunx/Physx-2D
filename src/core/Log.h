#pragma once
/*
	Logging and Assertions are defined. During debugging mode, debug logs are enabled.
	INFO are printed as green texts, Yellow for warnings and Red for errors. Debug logs
	are all disabled in any other mode.
	Assertions are enabled if PHSX_ASSERT_ENABLE is defined.
*/
#include "pch.h"

#define __VA_ARGS0__(x, ...) x
#define __VA_ARGSN0__(x, ...) __VA_ARGS__

#ifdef PHSX2D_DEBUG

    #define LOG_INFO(form, ...) printf("\033[1;32m" form "\033[1;0m", ##__VA_ARGS__)
    #define LOG_WARN(form, ...) printf("\033[1;33m" form "\033[1;0m", ##__VA_ARGS__)
    #define LOG_ERROR(form, ...) printf("\033[1;31m" form "\033[1;0m", ##__VA_ARGS__)
    #define PHSX2D_DBG_EXP(EXP__) EXP__
#else

    #define LOG_INFO(form, ...)
    #define LOG_WARN(form, ...)
    #define LOG_ERROR(form, ...)
    #define PHSX2D_DBG_EXP(x) 

#endif

#if defined(PHSX2D_PLATFORM_WINDOWS)
	#define dbgbrk() __debugbreak()
#elif defined(PHSX2D_PLATFORM_LINUX) 
	#define dbgbrk() __builtin_trap()
#elif defined(PHSX2D_PLATFORM_APPLE)
    #define dbgbrk() __builtin_debugtrap()
#else
    #error "Unsupported OS"
#endif

#ifdef PHSX2D_ASSERT_ENABLE
    #define PHSX2D_HARD_ASSERT(x, ...) if(!(x)) {LOG_ERROR("ASSERTION FAILED : " __VA_ARGS__); dbgbrk(); }
#else
    #define PHSX2D_HARD_ASSERT(x, ...)
#endif
