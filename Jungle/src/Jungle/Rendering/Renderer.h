#pragma once

#include "Jungle/Core/Core.h"

namespace Jungle
{
	enum class RendererAPI
	{
		None = 0,
		OpenGL = 1
	};

	class JUNGLE_API Renderer
	{
	public:
		inline static RendererAPI GetAPI() { return s_RendererAPI; }
		inline static void SetAPI(RendererAPI rendererAPI) { s_RendererAPI = rendererAPI; }

	private:
		static RendererAPI s_RendererAPI;
	};
}

