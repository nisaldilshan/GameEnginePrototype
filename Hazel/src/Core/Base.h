#pragma once

#include "PlatformDetection.h"

#ifdef HZ_PLATFORM_WINDOWS
	#if HZ_DYNAMIC_LINK
		#ifdef HZ_BUILD_DLL
			#define HAZEL_API __declspec(dllexport)
		#else
			#define HAZEL_API __declspec(dllimport)
		#endif
	#else
		#define HAZEL_API
	#endif
#else
	#error Hazel only supports Windows!
#endif

#ifdef HZ_DEBUG
	#if defined(HZ_PLATFORM_WINDOWS)
		#define HZ_DEBUGBREAK() __debugbreak()
	#elif defined(HZ_PLATFORM_LINUX)
		#include <signal.h>
		#define HZ_DEBUGBREAK() raise(SIGTRAP)
	#else
		#error "Platform doesn't support debugbreak yet!"
	#endif
	#define HZ_ENABLE_ASSERTS
#else
	#define HZ_DEBUGBREAK()
#endif

#define BIT(x) (1 << x) 

#define HZ_BIND_EVENT_FN(fn) [this](auto&&... args) -> decltype(auto) { \
	return this->fn(std::forward<decltype(args)>(args)...); \
}

#include "src/Core/Log.h"
#include "src/Core/Assert.h"