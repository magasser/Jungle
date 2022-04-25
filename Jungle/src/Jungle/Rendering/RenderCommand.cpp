#include "jnglpch.h"
#include "RenderCommand.h"

#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace Jungle
{
	RendererAPI* RenderCommand::s_RendererAPI = new OpenGLRendererAPI();
}