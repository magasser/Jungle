#include "jnglpch.h"
#include "Timestep.h"

#ifdef JNGL_PLATFORM_WINDOWS
#include <profileapi.h>
#include "Jungle/Core/Verification.h"
#else
#include <GLFW/glfw3.h>
#endif

namespace Jungle
{
#ifdef JNGL_PLATFORM_WINDOWS
	inline float Timestep::GetTime()
	{
		LARGE_INTEGER frequency;
		LARGE_INTEGER ticks;
		JNGL_CORE_VERIFY(QueryPerformanceFrequency(&frequency), "Failed to query performance frequency.");
		JNGL_CORE_VERIFY(QueryPerformanceCounter(&ticks), "Failed to query performance counter.");

		return (float)ticks.LowPart / frequency.LowPart;
	}
#else
	inline float Timestep::GetTime()
	{
		return glfwGetTime();
	}
#endif
}