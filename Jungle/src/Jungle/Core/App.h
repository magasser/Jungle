#pragma once

#include "Core.h"
#include "Window.h"
#include "LayerStack.h"
#include "Jungle/Events/AppEvent.h"
#include "Jungle/ImGui/ImGuiLayer.h"
#include "Jungle/Rendering/Shader.h"
#include "Jungle/Rendering/Buffer.h"
#include "Jungle/Rendering/VertexArray.h"

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

		inline Window& GetWindow() { return *m_Window; }

		inline static App& Get() { return *s_Instance; }

	private:
		bool OnWindowClose(WindowCloseEvent& e);

		std::unique_ptr<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running = true;
		LayerStack m_LayerStack;

	private:
		static App* s_Instance;
	};

	App* CreateApp();
}

