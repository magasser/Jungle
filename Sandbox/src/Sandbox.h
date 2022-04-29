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
		std::shared_ptr<Jungle::Shader> m_Shader;
		std::shared_ptr<Jungle::VertexArray> m_VertexArray;

		std::shared_ptr<Jungle::Shader> m_SquareShader;
		std::shared_ptr<Jungle::VertexArray> m_SquareVA;

		Jungle::OrthographicCamera m_Camera;
		float m_CameraSpeed = 0.05f;

		glm::vec3 m_SquarePosition;
		float m_SquareSpeed = 3.0f;
	};
}