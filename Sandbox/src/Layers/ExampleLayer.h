#pragma once

#include <Jungle.h>

namespace Sandbox
{
	class ExampleLayer : public Jungle::Layer
	{
	public:
		ExampleLayer();
		~ExampleLayer();

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnUpdate(Jungle::Timestep timestep) override;
		virtual void OnEvent(Jungle::Event& e) override;
		virtual void OnImGuiRender() override;

	private:
		Jungle::Ref<Jungle::Texture2D> m_LogoTexture, m_CheckerboardTexture;

		Jungle::OrthographicCameraController m_CameraController;

		glm::vec3 m_SquareColor = { 0.2f, 0.8f, 0.3f };
	};
}
