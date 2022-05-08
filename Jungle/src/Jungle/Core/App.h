#pragma once

#include "Jungle/Core/Core.h"
#include "Jungle/Core/Window.h"
#include "Jungle/Core/LayerStack.h"
#include "Jungle/Core/Timestep.h"

#include "Jungle/Events/AppEvent.h"
#include "Jungle/ImGui/ImGuiLayer.h"

namespace Jungle 
{
	class JUNGLE_API App
	{
	public:
		App(const std::string& name = "Jungle Engine");
		virtual ~App();

		void Run();

		void Close();

		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);

		ImGuiLayer* GetImGuiLayer() { return m_ImGuiLayer; }

		inline Window& GetWindow() { return *m_Window; }

		inline static App& Get() { return *s_Instance; }

	private:
		bool OnWindowClose(WindowCloseEvent& e);
		bool OnWindowResize(WindowResizeEvent& e);

	private:
		Scope<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running = true;
		bool m_Minimized = false;
		LayerStack m_LayerStack;
		float m_LastFrameTime = 0.0f;

		static App* s_Instance;
	};

	App* CreateApp();
}

