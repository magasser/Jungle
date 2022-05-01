#include "Sandbox2D.h"

#include <chrono>

#include <imgui.h>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Platform/OpenGL/OpenGLShader.h"

namespace Sandbox
{

	Sandbox2D::Sandbox2D()
		: Layer("Sandbox2D"),
		m_CameraController(1280.0f / 720.0f)
	{

	}

	void Sandbox2D::OnAttach()
	{
		JNGL_PROFILE_FUNCTION();

		m_CheckerboardTexture = Jungle::Texture2D::Create("assets/textures/Checkerboard.png");
	}

	void Sandbox2D::OnDetach()
	{
		JNGL_PROFILE_FUNCTION();
	}

	void Sandbox2D::OnUpdate(Jungle::Timestep timestep)
	{
		JNGL_PROFILE_FUNCTION();

		m_CameraController.OnUpdate(timestep);

		Jungle::RenderCommand::Clear({ 0.1f, 0.1f, 0.1f, 1 });

		{
			JNGL_PROFILE_SCOPE("Sandbox2D Rendering");
			Jungle::Renderer2D::BeginScene(m_CameraController.GetCamera());

			Jungle::Renderer2D::DrawQuad({ -1.0f, 0.0f }, { 0.8f, 0.8f }, { 0.7f, 0.2f, 0.3f, 1.0f });
			Jungle::Renderer2D::DrawQuad({ 0.5f, -0.5f }, { 0.5f, 0.75f }, { 0.3f, 0.2f, 0.7f, 1.0f });
			Jungle::Renderer2D::DrawQuad({ 0.2f, 0.5f, -0.1f }, { 10.0f, 10.0f }, m_CheckerboardTexture);

			Jungle::Renderer2D::EndScene();
		}
	}

	void Sandbox2D::OnEvent(Jungle::Event& e)
	{
		JNGL_PROFILE_FUNCTION();

		m_CameraController.OnEvent(e);
	}

	void Sandbox2D::OnImGuiRender()
	{
		JNGL_PROFILE_FUNCTION();

		ImGui::Begin("Settings");
		ImGui::ColorEdit4("Square Color", glm::value_ptr(m_SquareColor));
		ImGui::End();
	}
}
