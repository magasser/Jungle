#include "jnglpch.h"
#include "App.h"

#include <glad/glad.h>

#include "Jungle/Core/Verification.h"
#include "Jungle/Core/Input.h"
#include "Jungle/Rendering/Renderer.h"

namespace Jungle
{
	App* App::s_Instance = nullptr;

	App::App()
	{
		JNGL_PROFILE_FUNCTION();

		JNGL_CORE_ASSERT(!s_Instance, "App already exists.");

		s_Instance = this;

		m_Window = Window::Create();
		m_Window->SetEventCallback(JNGL_BIND_EVENT_FN(App::OnEvent));

		Renderer::Init();

		m_ImGuiLayer = new ImGuiLayer();
		PushOverlay(m_ImGuiLayer);
	}

	App::~App()
	{
		JNGL_PROFILE_FUNCTION();

		Renderer::Shutdown();
	}

	void App::Run()
	{
		JNGL_PROFILE_FUNCTION();

		while (m_Running)
		{
			JNGL_PROFILE_SCOPE("App Run Loop");

			float time = Timestep::GetTime();
			Timestep timestep = time - m_LastFrameTime;
			m_LastFrameTime = time;

			if (!m_Minimized)
			{
				{
					JNGL_PROFILE_SCOPE("App Layers OnUpdate");

					for (Layer* layer : m_LayerStack)
					{
						layer->OnUpdate(timestep);
					}

				}
			}

			m_ImGuiLayer->Begin();
			{
				JNGL_PROFILE_SCOPE("App Layers OnImGuiRender");

				for (Layer* layer : m_LayerStack)
				{
					layer->OnImGuiRender();
				}
			}
			m_ImGuiLayer->End();

			m_Window->OnUpdate();
		}
	}

	void App::OnEvent(Event& e)
	{
		JNGL_PROFILE_FUNCTION();

		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(JNGL_BIND_EVENT_FN(App::OnWindowClose));
		dispatcher.Dispatch<WindowResizeEvent>(JNGL_BIND_EVENT_FN(App::OnWindowResize));

		auto [x, y] = Input::GetMousePosition();

		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin(); )
		{
			(*--it)->OnEvent(e);
			if (e.Handled)
			{
				break;
			}
		}
	}

	void App::PushLayer(Layer* layer)
	{
		JNGL_PROFILE_FUNCTION();

		m_LayerStack.PushLayer(layer);
		layer->OnAttach();
	}

	void App::PushOverlay(Layer* overlay)
	{
		JNGL_PROFILE_FUNCTION();

		m_LayerStack.PushOverlay(overlay);
		overlay->OnAttach();
	}

	bool App::OnWindowClose(WindowCloseEvent& e)
	{
		m_Running = false;
		return true;
	}

	bool App::OnWindowResize(WindowResizeEvent& e)
	{
		JNGL_PROFILE_FUNCTION();

		m_Minimized = !(e.GetWidth() | e.GetHeight());

		if (m_Minimized)
		{
			return false;
		}

		Renderer::OnWindowResize(e.GetWidth(), e.GetHeight());

		return false;
	}
}
