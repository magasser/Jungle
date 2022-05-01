#include "jnglpch.h"
#include "Window.h"

#ifdef JNGL_PLATFORM_WINDOWS
#include "Platform/Windows/WindowsWindow.h"
#endif

namespace Jungle
{
	Scope<Window> Window::Create(const WindowProps& props)
	{
#ifdef JNGL_PLATFORM_WINDOWS
		return CreateScope<WindowsWindow>(props);
#else
		JNGL_CORE_ASSERT(false, "Unsupported platform.");
		retun nullptr;
#endif
	}
}