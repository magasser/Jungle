#pragma once

#include "Jungle/Core/Core.h"
#include "Jungle/Rendering/RenderCommand.h"
#include "Jungle/Rendering/Camera.h"
#include "Jungle/Rendering/Shader.h"

namespace Jungle
{
	class JUNGLE_API Renderer
	{
	public:
		static void Init();
		static void Shutdown();

		static void BeginScene(Camera2& camera);
		static void EndScene();

		static void Submit(const Ref<Shader>& shader, const Ref<VertexArray>& vertexArray, const glm::mat4& transform = glm::mat4(1.0f));

		static void OnWindowResize(uint32_t width, uint32_t height);

		inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }

	private:
		struct SceneData
		{
			glm::mat4 ViewProjectionMatrix;
		};

		static SceneData* m_SceneData;
	};
}

