#pragma once

#include "Jungle/Rendering/RendererAPI.h"

namespace Jungle
{
	class OpenGLRendererAPI : public RendererAPI
	{
	public:
		virtual void Clear(const glm::vec4& color) override;

		virtual void DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray) override;
	};
}

