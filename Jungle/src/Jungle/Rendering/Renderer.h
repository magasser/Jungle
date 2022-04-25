#pragma once

#include "Jungle/Core/Core.h"
#include "RenderCommand.h"

namespace Jungle
{

	class JUNGLE_API Renderer
	{
	public:
		static void BeginScene();
		static void EndScene();

		static void Submit(const std::shared_ptr<VertexArray>& vertexArray);

		inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }
	};
}

