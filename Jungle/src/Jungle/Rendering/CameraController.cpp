#include "jnglpch.h"
#include "CameraController.h"

#include "Jungle/Core/Input.h"
#include "Jungle/Core/KeyCodes.h"

namespace Jungle
{
	OrthographicCameraController::OrthographicCameraController(float apectRatio, bool canRotate)
		: m_CanRotate(canRotate),
		m_AspectRatio(apectRatio), 
		m_Camera(-m_AspectRatio * m_ZoomLevel, m_AspectRatio* m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel)
	{
	}

	OrthographicCamera& OrthographicCameraController::GetCamera()
	{
		return m_Camera;
	}

	const OrthographicCamera& OrthographicCameraController::GetCamera() const
	{
		return m_Camera;
	}

	void OrthographicCameraController::OnUpdate(Timestep timestep)
	{
		JNGL_PROFILE_FUNCTION();

		if (Input::IsKeyPressed(JNGL_KEY_A))
		{
			m_Position.x -= m_TranslationSpeed * timestep;
		}
		else if (Input::IsKeyPressed(JNGL_KEY_D))
		{
			m_Position.x += m_TranslationSpeed * timestep;
		}
		if (Input::IsKeyPressed(JNGL_KEY_W))
		{
			m_Position.y += m_TranslationSpeed * timestep;
		}
		else if (Input::IsKeyPressed(JNGL_KEY_S))
		{
			m_Position.y -= m_TranslationSpeed * timestep;
		}

		if (m_CanRotate)
		{
			if (Input::IsKeyPressed(JNGL_KEY_Q))
			{
				m_Rotation += m_RotationSpeed * timestep;
			}
			else if (Input::IsKeyPressed(JNGL_KEY_E))
			{
				m_Rotation -= m_RotationSpeed * timestep;
			}

			m_Camera.SetRotation(m_Rotation);
		}

		m_Camera.SetPosition(m_Position);
	}

	void OrthographicCameraController::OnEvent(Event& e)
	{
		JNGL_PROFILE_FUNCTION();

		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<MouseScrolledEvent>(JNGL_BIND_EVENT_FN(OrthographicCameraController::OnMouseScrolled));
		dispatcher.Dispatch<WindowResizeEvent>(JNGL_BIND_EVENT_FN(OrthographicCameraController::OnWindowResized));
	}

	bool OrthographicCameraController::OnMouseScrolled(MouseScrolledEvent& e)
	{
		JNGL_PROFILE_FUNCTION();

		SetZoomLevel(m_ZoomLevel - e.GetYOffest() * m_ZoomSpeed);
		m_Camera.SetProjectionMatrix(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);

		return false;
	}

	bool OrthographicCameraController::OnWindowResized(WindowResizeEvent& e)
	{
		JNGL_PROFILE_FUNCTION();

		m_AspectRatio = (float)e.GetWidth() / (float)e.GetHeight();
		m_Camera.SetProjectionMatrix(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);

		return false;
	}
}
