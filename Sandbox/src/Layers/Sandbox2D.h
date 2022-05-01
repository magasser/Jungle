#pragma once

#include <Jungle.h>

namespace Sandbox
{
	class Sandbox2D : public Jungle::Layer
	{
	public:
		Sandbox2D();
		virtual ~Sandbox2D() = default;

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnUpdate(Jungle::Timestep timestep) override;
		virtual void OnEvent(Jungle::Event& e) override;
		virtual void OnImGuiRender() override;

	private:
		Jungle::OrthographicCameraController m_CameraController;

		Jungle::Ref<Jungle::VertexArray> m_SquareVA;
		Jungle::Ref<Jungle::Shader> m_FlatColorShader;

		glm::vec4 m_SquareColor = { 0.2f, 0.8f, 0.3f, 1.0f };
	};
}

