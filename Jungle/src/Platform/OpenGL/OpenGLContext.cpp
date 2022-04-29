#include "jnglpch.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Jungle/Core/Verification.h"

#include "OpenGLContext.h"

namespace Jungle
{
	OpenGLContext::OpenGLContext(GLFWwindow* windowHandle)
		: m_WindowHandle(windowHandle)
	{
		JNGL_CORE_ASSERT(windowHandle, "Window handle is null.");
	}

	void OpenGLContext::Init()
	{
		glfwMakeContextCurrent(m_WindowHandle);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		JNGL_CORE_ASSERT(status, "Failed to initialize GLAD.");
	}

	void OpenGLContext::SwapBuffers()
	{
		glfwSwapBuffers(m_WindowHandle);
	}
}
