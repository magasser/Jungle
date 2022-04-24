#pragma once

#include "Jungle/Core/Layer.h"
#include "Jungle/Events/KeyEvent.h"
#include "Jungle/Events/MouseEvent.h"
#include "Jungle/Events/AppEvent.h"

namespace Jungle
{
	class JUNGLE_API ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();

		void OnAttach();
		void OnDetach();
		void OnUpdate();
		void OnEvent(Event& e);

	private:
		bool OnMouseButtonPressedEvent(MouseButtonPressedEvent& e);
		bool OnMouseButtonReleasedEvent(MouseButtonReleasedEvent& e);
		bool OnMouseMovedEvent(MouseMovedEvent& e);
		bool OnMouseScrollEvent(MouseScrolledEvent& e);
		
		bool OnKeyPressedEvent(KeyPressedEvent& e);
		bool OnKeyReleasedEvent(KeyReleasedEvent& e);
		bool OnKeyTypedEvent(KeyTypedEvent& e);
		
		bool OnWindowResizedEvent(WindowResizeEvent& e);
		bool OnWindowClosedEvent(WindowCloseEvent& e);

	private:
		float m_Time = 0.0f;
	};
}

