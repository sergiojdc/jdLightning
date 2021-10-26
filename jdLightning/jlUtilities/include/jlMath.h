#pragma once
#include "jlPlatformMath.h"

#if  JL_PLATFORM == JL_PLATFORM_WIN32
# include "jlWindowsMath.h"
#elif JL_PLATFORM == JL_PLATFORM_LINUX //LINUX
//# include "jdLinuxMath.h"
//  using Math = LinuxMath;
#else
//  using Math = PlatformMath;
#endif //  JL_PLATFORM ==JL_PLATFORM_WIN32

#if  JL_PLATFORM == JL_PLATFORM_WIN32
using Math = jlUtilitiesSDK::WindowsMath;
#elif JL_PLATFORM == JL_PLATFORM_LINUX //LINUX
//# include "jdLinuxMath.h"
//  using Math = LinuxMath;
#else
//  using Math = PlatformMath;
#endif //  JL_PLATFORM ==JL_PLATFORM_WIN32
