#pragma once

#include "Jungle/Core/Core.h"
#include "Jungle/Core/Timestep.h"
#include "Jungle/Events/AppEvent.h"
#include "Jungle/Events/MouseEvent.h"
#include "Jungle/Rendering/Camera.h"

namespace Jungle
{
	class JUNGLE_API CameraController
	{
	public:
		virtual void OnUpdate(Timestep timestep) { }
		virtual void OnEvent(Event& e) { }

		virtual Camera& GetCamera() = 0;
		virtual const Camera& GetCamera() const = 0;

		void SetPosition(const glm::vec3& position) { m_Position = position; GetCamera().SetPosition(position); }
		const glm::vec3& GetPosition() { return m_Position; }

		void SetTranslationSpeed(float speed) { m_TranslationSpeed = speed; }
		float GetTranslationSpeed() const { return m_TranslationSpeed; }

		void SetRotationSpeed(float speed) { m_RotationSpeed = speed; }
		float GetTranslationSpeed() { return m_TranslationSpeed; }

		void SetZoomLevel(float zoomLevel) { m_ZoomLevel = std::clamp(zoomLevel, m_MinZoomLevel, m_MaxZoomLevel); CalculateView(); SetTranslationSpeed(m_ZoomLevel); }
		void SetZoomSpeed(float zoomSpeed) { m_ZoomSpeed = zoomSpeed; }
		void SetMinZoomLevel(float zoomLevel) { m_MinZoomLevel = zoomLevel; }
		void SetMaxZoomLevel(float zoomLevel) { m_MaxZoomLevel = zoomLevel; }
		float GetZoomLevel() { return m_ZoomLevel; }
		float GetZoomSpeed() { return m_ZoomSpeed; }
		float GetMinZoomLevel() { return m_MinZoomLevel; }
		float GetMaxZoomLevel() { return m_MaxZoomLevel; }

	protected:
		virtual void CalculateView() = 0;

	protected:
		glm::vec3 m_Position = { 0.0f, 0.0f, 0.0f };
		float m_TranslationSpeed = 3.0f;
		float m_RotationSpeed = 180.0f;

		float m_ZoomLevel = 1.0f;
		float m_ZoomSpeed = 0.25f;
		float m_MinZoomLevel = 0.25f;
		float m_MaxZoomLevel = 10.0f;
	};

	class JUNGLE_API OrthographicCameraController : public CameraController
	{
	public:
		OrthographicCameraController(float apectRatio, bool canRotate = false);

		virtual OrthographicCamera& GetCamera() override;
		virtual const OrthographicCamera& GetCamera() const override;

		void OnUpdate(Timestep timestep);
		void OnEvent(Event& e);

	protected:
		virtual void CalculateView() override;

	private:
		bool OnMouseScrolled(MouseScrolledEvent& e);
		bool OnWindowResized(WindowResizeEvent& e);

	private:
		float m_AspectRatio;
		OrthographicCamera m_Camera;

		bool m_CanRotate;
		float m_Rotation = 0.0f;
	};
}
