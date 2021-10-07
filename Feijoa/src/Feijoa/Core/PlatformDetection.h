#pragma once

#ifdef _WIN32
#ifdef _WIN64
#define FJ_PLATFORM_WINDOWS
#else
#error "x86 builds not supported"
#endif // _WIN64
#elif defined(__APPLE__) || defined(__MACH__)
#include "<TargetConditionals.h>"
#if TARGET_IPHONE_SIMULATOR == 1
#error "IOS simulator is not supported!"
#elif TARGET_OS_IPHONE == 1
#define FJ_PLATFORM_IOS
#error "IOS is not supported!"
#elif TARGET_OS_MAC == 1
#define FJ_PLATFORM_MACOS
#error "MacOS not supported!"
#else
#error "Unknown Apple platform!"
#endif
#elif defined(__ANDROID__)
#ifdef FJ_PLATFORM_ANDROID
#define FJ_PLATFORM_ANDROID
#endif
#error "Android is not supported!"
#elif defined(__linux__)
#ifdef FJ_PLATFORM_LINUX
#define FJ_PLATFORM_LINUX
#endif
#error "Linux is not supported!"
#else
#error "Unknown platform!"
#endif