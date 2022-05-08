#include "EditorLayer.h"

#include <imgui.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace Jungle
{
	EditorLayer::EditorLayer()
		: Layer("ExampleLayer"),
		m_CameraController(1280.0f / 720.0f, true)
	{
	}

	EditorLayer::~EditorLayer()
	{
	}

	void EditorLayer::OnAttach()
	{
		JNGL_PROFILE_FUNCTION();

		m_CheckerboardTexture = Texture2D::Create("assets/textures/Checkerboard.png");
		m_LogoTexture = Texture2D::Create("assets/textures/Logo.png");

		m_CameraController.SetZoomLevel(10.0f);

		FramebufferSpecification fbSpec =
		{
			.Width = 1280,
			.Height = 720,
		};

		m_Framebuffer = Framebuffer::Create(fbSpec);
	}

	void EditorLayer::OnDetach()
	{
		JNGL_PROFILE_FUNCTION();
	}

	void EditorLayer::OnUpdate(Timestep timestep)
	{
		if (m_ViewportFocused)
		{
			m_CameraController.OnUpdate(timestep);
		}

		m_Framebuffer->Bind();

		RenderCommand::Clear({ 0.2f, 0.5f, 0.2f, 1 });

		Renderer2D::ResetStatistics();

		Renderer2D::BeginScene(m_CameraController.GetCamera());

		static float rotationAngle = 0.0f;
		rotationAngle += timestep * 15.0f;

		Renderer2D::DrawQuad({ 0.0f, 0.0f }, { 1.0f, 1.0f }, { 0.7f, 0.2f, 0.3f, 1.0f });
		Renderer2D::DrawRotatedQuad({ 0.5f, -0.5f }, { 0.5f, 0.75f }, glm::radians(-20.0f), { 0.3f, 0.2f, 0.7f, 1.0f });
		Renderer2D::DrawQuad({ 0.0f, 0.0f, -0.2f }, { 20.0f, 20.0f }, m_CheckerboardTexture, 2.0f, { 0.7f, 1.0f, 0.8f, 1.0f });
		Renderer2D::DrawRotatedQuad({ 0.0f, 0.0f, -0.1f }, { 5.0f, 5.0f }, glm::radians(-rotationAngle), m_CheckerboardTexture, 4.0f, { 0.7f, 0.8f, 1.0f, 1.0f });
		Renderer2D::DrawRotatedQuad({ 0.0f, 0.0f, 0.0f }, { 1.0f, 1.0f }, glm::radians(rotationAngle), m_CheckerboardTexture, 8.0f, { 1.0f, 0.7f, 0.8f, 1.0f });

		for (float y = -5.0f; y <= 5.0f; y += 0.1f)
		{
			for (float x = -5.0f; x <= 5.0f; x += 0.1f)
			{
				glm::vec4 color((x + 5.0f) / 10.0f, (y + 5.0f) / 10.0f, (x + y) / 15.0f, 0.7f);
				Renderer2D::DrawRotatedQuad({ x, y }, { 0.07f, 0.07f }, glm::radians(rotationAngle), color);
			}
		}
		Renderer2D::EndScene();

		m_Framebuffer->Unbind();
	}

	void EditorLayer::OnEvent(Event& e)
	{
		JNGL_PROFILE_FUNCTION();

		m_CameraController.OnEvent(e);
	}

	void EditorLayer::OnImGuiRender()
	{
		static bool dockspaceOpen = true;
		static bool opt_fullscreen = true;
		static bool opt_padding = false;
		static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

		// We are using the ImGuiWindowFlags_NoDocking flag to make the parent window not dockable into,
		// because it would be confusing to have two docking targets within each others.
		ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
		if (opt_fullscreen)
		{
			const ImGuiViewport* viewport = ImGui::GetMainViewport();
			ImGui::SetNextWindowPos(viewport->WorkPos);
			ImGui::SetNextWindowSize(viewport->WorkSize);
			ImGui::SetNextWindowViewport(viewport->ID);
			ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
			ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
			window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
			window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
		}
		else
		{
			dockspace_flags &= ~ImGuiDockNodeFlags_PassthruCentralNode;
		}

		// When using ImGuiDockNodeFlags_PassthruCentralNode, DockSpace() will render our background
		// and handle the pass-thru hole, so we ask Begin() to not render a background.
		if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
			window_flags |= ImGuiWindowFlags_NoBackground;

		// Important: note that we proceed even if Begin() returns false (aka window is collapsed).
		// This is because we want to keep our DockSpace() active. If a DockSpace() is inactive,
		// all active windows docked into it will lose their parent and become undocked.
		// We cannot preserve the docking relationship between an active window and an inactive docking, otherwise
		// any change of dockspace/settings would lead to windows being stuck in limbo and never being visible.
		if (!opt_padding)
			ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
		ImGui::Begin("DockSpace Demo", &dockspaceOpen, window_flags);
		if (!opt_padding)
			ImGui::PopStyleVar();

		if (opt_fullscreen)
			ImGui::PopStyleVar(2);

		// Submit the DockSpace
		ImGuiIO& io = ImGui::GetIO();
		if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
		{
			ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
			ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
		}

		if (ImGui::BeginMenuBar())
		{
			if (ImGui::BeginMenu("File"))
			{
				if (ImGui::MenuItem("Exit"))
				{
					App::Get().Close();
				}

				ImGui::EndMenu();
			}

			ImGui::EndMenuBar();
		}

		ImGui::Begin("Settings");

		auto& stats = Renderer2D::GetStatistics();

		ImGui::Text("Renderer2D Stats:");
		ImGui::Text("	Draw Calls: %d", stats.DrawCalls);
		ImGui::Text("	Quads: %d", stats.QuadCount);
		ImGui::Text("	Vertices: %d", stats.GetVertexCount());
		ImGui::Text("	Indices: %d", stats.GetIndexCount());

		ImGui::ColorEdit4("Square Color", glm::value_ptr(m_SquareColor));

		ImGui::End();

		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2{ 0, 0 });
		ImGui::Begin("Viewport");

		m_ViewportFocused = ImGui::IsWindowFocused();
		m_ViewportHovered = ImGui::IsWindowHovered();
		App::Get().GetImGuiLayer()->BlockEvents(!m_ViewportFocused || !m_ViewportHovered);

		ImVec2 viewportSize = ImGui::GetContentRegionAvail();

		if (m_ViewportSize != glm::vec2(viewportSize.x, viewportSize.y))
		{
			m_ViewportSize = { viewportSize.x, viewportSize.y };
			m_Framebuffer->Resize((uint32_t)m_ViewportSize.x, (uint32_t)m_ViewportSize.y);
			m_CameraController.Resize(m_ViewportSize.x, m_ViewportSize.y);
		}

		uint32_t textureID = m_Framebuffer->GetColorAttachmentRendererID();
		ImGui::Image((void*)textureID, ImVec2{ 1280.0f, 720.0f }, ImVec2{ 0, 1 }, ImVec2{ 1, 0 });

		ImGui::End();
		ImGui::PopStyleVar();

		ImGui::End();
	}
}
