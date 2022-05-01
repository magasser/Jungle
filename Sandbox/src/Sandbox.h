#pragma once

#include <Jungle.h>

namespace Sandbox
{
	class SandboxApp : public Jungle::App
	{
	public:
		SandboxApp();

		~SandboxApp() = default;
	};
	
	class ExampleLayer : public Jungle::Layer
	{
	public:
		ExampleLayer();
		~ExampleLayer();

		virtual void OnUpdate(Jungle::Timestep timestep) override;
		virtual void OnImGuiRender() override;
		virtual void OnEvent(Jungle::Event& e) override;

	private:
		bool OnKeyPressedEvent(Jungle::KeyPressedEvent& e);

	private:
		Jungle::ShaderLibrary m_ShaderLibrary;
		Jungle::Ref<Jungle::VertexArray> m_VertexArray;

		Jungle::Ref<Jungle::Texture2D> m_Texture, m_LogoTexture;
		Jungle::Ref<Jungle::VertexArray> m_SquareVA;

		Jungle::OrthographicCamera m_Camera;
		float m_CameraSpeed = 0.1f;

		glm::vec3 m_SquareColor = { 0.2f, 0.8f, 0.3f };
	};
}