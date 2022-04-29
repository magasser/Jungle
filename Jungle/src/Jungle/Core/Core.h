#pragma once

#ifdef JNGL_PLATFORM_WINDOWS
	#ifdef JNGL_BUILD_DLL
		#define JUNGLE_API __declspec(dllexport)
	#else 
		#define JUNGLE_API __declspec(dllimport)
	#endif
#else
	#error Jungle Engine is only supported on Windows
#endif

#define BIT(x) (1 << (x))

#define JNGL_BIND_EVENT_FN(x) std::bind(&x, this, std::placeholders::_1)