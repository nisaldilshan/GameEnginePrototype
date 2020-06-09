#pragma once

#ifdef _WIN32
	#ifdef _WIN64
		#define HZ_PLATFORM_WINDOWS
		#ifdef HZ_BUILD_DLL
			#define HAZEL_API __declspec(dllexport)
		#else
			#define HAZEL_API __declspec(dllimport)
		#endif
	#else
		#error Hazel only supports 64bit!
	#endif
#else
	#error Hazel only supports Windows!
#endif