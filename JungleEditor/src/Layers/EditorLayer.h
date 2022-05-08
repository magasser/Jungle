#pragma once

#include <Jungle.h>

namespace Jungle
{
	class EditorLayer : public Layer
	{
	public:
		EditorLayer();
		~EditorLayer();

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnUpdate(Timestep timestep) override;
		virtual void OnEvent(Event & e) override;
		virtual void OnImGuiRender() override;

	private:
		Ref<Texture2D> m_LogoTexture, m_CheckerboardTexture;
		Ref<Framebuffer> m_Framebuffer;

		OrthographicCameraController m_CameraController;

		glm::vec2 m_ViewportSize = { 0.0f, 0.0f };
		bool m_ViewportFocused = false, m_ViewportHovered = false;

		glm::vec3 m_SquareColor = { 0.2f, 0.8f, 0.3f };
	};
}

