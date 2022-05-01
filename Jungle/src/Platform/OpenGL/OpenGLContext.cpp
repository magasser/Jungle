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
		JNGL_PROFILE_FUNCTION();

		glfwMakeContextCurrent(m_WindowHandle);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		JNGL_CORE_ASSERT(status, "Failed to initialize GLAD.");

		JNGL_CORE_LOG_INFO("OpenGL Info:");
		JNGL_CORE_LOG_INFO("	Vendor: {0}", glGetString(GL_VENDOR));
		JNGL_CORE_LOG_INFO("	Renderer: {0}", glGetString(GL_RENDERER));
		JNGL_CORE_LOG_INFO("	Version: {0}", glGetString(GL_VERSION));
	}

	void OpenGLContext::SwapBuffers()
	{
		JNGL_PROFILE_FUNCTION();

		glfwSwapBuffers(m_WindowHandle);
	}
}
