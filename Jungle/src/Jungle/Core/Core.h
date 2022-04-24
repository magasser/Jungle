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

#ifdef JNGL_ENABLE_ASSERTS
	#define JNGL_ASSERT(x, ...) { if(!(x)) { JNGL_LOG_ERROR("Assertion Failed: {0}.", __VA_ARGS__); __debugbreak(); } }
	#define JNGL_CORE_ASSERT(x, ...) { if(!(x)) { JNGL_CORE_LOG_ERROR("Assertion Failed: {0}.", __VA_ARGS__); __debugbreak(); } }
#else
	#define JNGL_ASSERT(x, ...)
	#define JNGL_CORE_ASSERT(x, ...)
#endif

#define BIT(x) (1 << (x))

#define JNGL_BIND_EVENT_FN(x) std::bind(&x, this, std::placeholders::_1)