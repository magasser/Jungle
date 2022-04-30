#pragma once

#include "Jungle/Core/Core.h"
#include "RenderCommand.h"
#include "Camera.h"
#include "Shader.h"

namespace Jungle
{

	class JUNGLE_API Renderer
	{
	public:
		static void BeginScene(Camera& camera);
		static void EndScene();

		static void Submit(const ShaderRef& shader, const VertexArrayRef& vertexArray, const glm::mat4& transform = glm::mat4(1.0f));

		inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }

	private:
		struct SceneData
		{
			glm::mat4 ViewProjectionMatrix;
		};

		static SceneData* m_SceneData;
	};
}

