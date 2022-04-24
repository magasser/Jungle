#include "jnglpch.h"
#include "App.h"

#include <glad/glad.h>

#include "Log.h"
#include "Input.h"

namespace Jungle
{
	App* App::s_Instance = nullptr;

	App::App()
	{
		JNGL_CORE_ASSERT(!s_Instance, "App already exists.");

		s_Instance = this;

		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(JNGL_BIND_EVENT_FN(App::OnEvent));
	}

	App::~App()
	{
	}

	void App::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(JNGL_BIND_EVENT_FN(App::OnWindowClose));

		auto [x, y] = Input::GetMousePosition();
		JNGL_CORE_LOG_TRACE("{0}, {1}", x, y);

		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin(); )
		{
			(*--it)->OnEvent(e);
			if (e.Handled)
			{
				break;
			}
		}
	}

	void App::Run()
	{
		while (m_Running)
		{
			glClearColor(0, 1, 0, 1);
			glClear(GL_COLOR_BUFFER_BIT);

			for (Layer* layer : m_LayerStack)
			{
				layer->OnUpdate();
			}

			m_Window->OnUpdate();
		}
	}

	void App::PushLayer(Layer* layer)
	{
		m_LayerStack.PushLayer(layer);
	}

	void App::PushOverlay(Layer* overlay)
	{
		m_LayerStack.PushOverlay(overlay);
	}

	bool App::OnWindowClose(WindowCloseEvent& e)
	{
		m_Running = false;
		return true;
	}
}
