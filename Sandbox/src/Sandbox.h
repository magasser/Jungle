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
		Jungle::ShaderRef m_Shader;
		Jungle::VertexArrayRef m_VertexArray;

		Jungle::ShaderRef m_SquareShader, m_TexShader;
		Jungle::VertexArrayRef m_SquareVA;

		Jungle::OrthographicCamera m_Camera;
		float m_CameraSpeed = 0.1f;

		glm::vec3 m_SquareColor = { 0.2f, 0.8f, 0.3f };
	};
}