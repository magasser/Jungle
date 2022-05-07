#include "Sandbox2D.h"

#include <chrono>

#include <imgui.h>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Platform/OpenGL/OpenGLShader.h"

namespace Sandbox
{
	static const uint32_t s_MapWidth = 30;
	static const char* s_MapTiles =
		"WWWWWWWWWWWWWWWWWWWWWWWWWWWWWW"
		"WWWWWWWWWWWWWWWWWWWWWWWWWWWWWW"
		"WWWWWWWWWWWWDDDWWWDDDWWWWWWWWW"
		"WWWWWWWWWDDDDDDDDDDDDDDWWWWWWW"
		"WWWWWWWWDDDDDDDDDDDDDDDDWWWWWW"
		"WWWWWWWDDDDDDDDDDDDDDDDWWWWWWW"
		"WWWWWWWDDDWWWDDDDDDDDWWWWWWWWW"
		"WWWWWWDDDWWWDDDDDDDDWWWWWWWWWW"
		"WWWWWWDDDDWWWDDDDDDDDWWWWWWWWW"
		"WWWWWWDDDDDDDDDDDDDDDDWWWWWWWW"
		"WWWWWWWDDDDDDDDDDDDDDDWWWWWWWW"
		"WWWWWWWWDDDDDDDDDDDDDWWWWWWWWW"
		"WWWWWWWWDDDDDDDDDDDDWWWWWWWWWW"
		"WWWWWWWWWDDDDDDDDDDWWWWWWWWWWW"
		"WWWWWWWWWWWDDDWWDWWWWWWWWWWWWW"
		"WWWWWWWWWWWWWWWWWWWWWWWWWWWWWW"
		"WWWWWWWWWWWWWWWWWWWWWWWWWWWWWW"
		;

	Sandbox2D::Sandbox2D()
		: Layer("Sandbox2D"),
		m_CameraController(1280.0f / 720.0f)
	{

	}

	void Sandbox2D::OnAttach()
	{
		JNGL_PROFILE_FUNCTION();

		m_CheckerboardTexture = Jungle::Texture2D::Create("assets/textures/Checkerboard.png");
		m_TextureAtlas = Jungle::TextureAtlas2D::Create("assets/game/textures/RPGpack_sheet_2X.png", { 128, 128 });
		m_TextureStairs = m_TextureAtlas->GetSubTexture({ 7, 6 });
		m_TextureTree = m_TextureAtlas->GetSubTexture({ 0, 1 }, { 1, 2 });

		m_MapWidth = s_MapWidth;
		m_MapHeight = strlen(s_MapTiles) / s_MapWidth;
		m_TextureMap['D'] = m_TextureAtlas->GetSubTexture({ 6, 11 });
		m_TextureMap['W'] = m_TextureAtlas->GetSubTexture({ 11, 11 });

		m_CameraController.SetZoomLevel(10.0f);
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

			Jungle::Renderer2D::ResetStatistics();

#if 0
			Jungle::Renderer2D::BeginScene(m_CameraController.GetCamera());

			static float rotationAngle = 0.0f;
			rotationAngle += timestep * 15.0f;

			Jungle::Renderer2D::DrawQuad({ 0.0f, 0.0f }, { 1.0f, 1.0f }, { 0.7f, 0.2f, 0.3f, 1.0f });
			Jungle::Renderer2D::DrawRotatedQuad({ 0.5f, -0.5f }, { 0.5f, 0.75f }, glm::radians(-20.0f), {0.3f, 0.2f, 0.7f, 1.0f});
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


			Jungle::Renderer2D::BeginScene(m_CameraController.GetCamera());
			Jungle::Renderer2D::DrawQuad({ 0.0f, 0.0f }, { 1.0f, 1.0f }, m_TextureStairs);
			Jungle::Renderer2D::DrawQuad({ -1.0f, 0.0f }, { 1.0f, 2.0f }, m_TextureTree);
			Jungle::Renderer2D::EndScene();
#endif
			Jungle::Renderer2D::BeginScene(m_CameraController.GetCamera());
			for (uint32_t y = 0; y < m_MapHeight; y++)
			{
				for (uint32_t x = 0; x < m_MapWidth; x++)
				{
					char tileType = s_MapTiles[x + y * m_MapWidth];

					Jungle::Ref<Jungle::SubTexture2D> texture;

					if (m_TextureMap.find(tileType) != m_TextureMap.end())
					{
						texture = m_TextureMap[tileType];
					}
					else
					{
						texture = m_TextureStairs;
					}

					Jungle::Renderer2D::DrawQuad({ x - m_MapWidth / 2.0f , y - m_MapHeight / 2.0f }, { 1.0f, 1.0f }, texture);
				}
			}
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
