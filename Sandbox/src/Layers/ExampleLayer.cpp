#include "ExampleLayer.h"

#include <imgui.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Platform/OpenGL/OpenGLShader.h"

namespace Sandbox
{
	ExampleLayer::ExampleLayer()
		: Layer("ExampleLayer"),
		m_CameraController(1280.0f / 720.0f, true)
	{
	}

	ExampleLayer::~ExampleLayer()
	{
	}

	void ExampleLayer::OnAttach()
	{
		JNGL_PROFILE_FUNCTION();

		m_CheckerboardTexture = Jungle::Texture2D::Create("assets/textures/Checkerboard.png");
		m_LogoTexture = Jungle::Texture2D::Create("assets/textures/Logo.png");

		m_CameraController.SetZoomLevel(10.0f);
	}

	void ExampleLayer::OnDetach()
	{
		JNGL_PROFILE_FUNCTION();
	}

	void ExampleLayer::OnUpdate(Jungle::Timestep timestep)
	{
		m_CameraController.OnUpdate(timestep);

		Jungle::RenderCommand::Clear({ 0.2f, 0.5f, 0.2f, 1 });

		Jungle::Renderer2D::ResetStatistics();

		Jungle::Renderer2D::BeginScene(m_CameraController.GetCamera());

		static float rotationAngle = 0.0f;
		rotationAngle += timestep * 15.0f;

		Jungle::Renderer2D::DrawQuad({ 0.0f, 0.0f }, { 1.0f, 1.0f }, { 0.7f, 0.2f, 0.3f, 1.0f });
		Jungle::Renderer2D::DrawRotatedQuad({ 0.5f, -0.5f }, { 0.5f, 0.75f }, glm::radians(-20.0f), { 0.3f, 0.2f, 0.7f, 1.0f });
		Jungle::Renderer2D::DrawQuad({ 0.0f, 0.0f, -0.2f }, { 20.0f, 20.0f }, m_CheckerboardTexture, 2.0f, { 0.7f, 1.0f, 0.8f, 1.0f });
		Jungle::Renderer2D::DrawRotatedQuad({ 0.0f, 0.0f, -0.1f }, { 5.0f, 5.0f }, glm::radians(-rotationAngle), m_CheckerboardTexture, 4.0f, { 0.7f, 0.8f, 1.0f, 1.0f });
		Jungle::Renderer2D::DrawRotatedQuad({ 0.0f, 0.0f, 0.0f }, { 1.0f, 1.0f }, glm::radians(rotationAngle), m_CheckerboardTexture, 8.0f, { 1.0f, 0.7f, 0.8f, 1.0f });

		for (float y = -5.0f; y <= 5.0f; y += 0.1f)
		{
			for (float x = -5.0f; x <= 5.0f; x += 0.1f)
			{
				glm::vec4 color((x + 5.0f) / 10.0f, (y + 5.0f) / 10.0f, (x + y) / 15.0f, 0.7f);
				Jungle::Renderer2D::DrawRotatedQuad({ x, y }, { 0.07f, 0.07f }, glm::radians(rotationAngle), color);
			}
		}
		Jungle::Renderer2D::EndScene();

		m_Framebuffer->Unbind();
	}

	void ExampleLayer::OnEvent(Jungle::Event& e)
	{
		JNGL_PROFILE_FUNCTION();

		m_CameraController.OnEvent(e);
	}

	void ExampleLayer::OnImGuiRender()
	{
		ImGui::Begin("Settings");

		auto& stats = Jungle::Renderer2D::GetStatistics();

		ImGui::Text("Renderer2D Stats:");
		ImGui::Text("	Draw Calls: %d", stats.DrawCalls);
		ImGui::Text("	Quads: %d", stats.QuadCount);
		ImGui::Text("	Vertices: %d", stats.GetVertexCount());
		ImGui::Text("	Indices: %d", stats.GetIndexCount());

		ImGui::ColorEdit4("Square Color", glm::value_ptr(m_SquareColor));

		ImGui::End();
	}
}
