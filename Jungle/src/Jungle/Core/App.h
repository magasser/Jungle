#pragma once

#include "Core.h"
#include "Window.h"
#include "Jungle/Events/AppEvent.h"
#include "LayerStack.h"

namespace Jungle 
{
	class JUNGLE_API App
	{
	public:
		App();
		virtual ~App();

		void Run();

		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);

	private:
		bool OnWindowClose(WindowCloseEvent& e);

		std::unique_ptr<Window> m_Window;
		bool m_Running = true;
		LayerStack m_LayerStack;
	};

	App* CreateApp();
}

