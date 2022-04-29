#pragma once

#include "../../GLM/glm/glm.hpp"

#include "Jungle/Core/Core.h"

namespace Jungle
{
	class JUNGLE_API Camera
	{
	public:
		const glm::mat4& GetProjectionMatrix() const { return m_ProjectionMatrix; }
		const glm::mat4& GetViewMatrix() const { return m_ViewMatrix; }
		const glm::mat4& GetViewProjectionMatrix() const { return m_ViewProjectionMatrix; }

		const glm::vec3& GetPosition() const { return m_Position; }
		void SetPosition(const glm::vec3& position) { m_Position = position; RecalculateViewMatrix(); }

	protected:
		Camera(glm::mat4 projectionMatrix, glm::mat4 viewMatrix);

		virtual void RecalculateViewMatrix() = 0;

	protected:
		glm::mat4 m_ProjectionMatrix;
		glm::mat4 m_ViewMatrix;
		glm::mat4 m_ViewProjectionMatrix;

		glm::vec3 m_Position = {0.0f, 0.0f, 0.0f};
	};

	class JUNGLE_API OrthographicCamera : public Camera
	{
	public:
		OrthographicCamera(float left, float right, float bottom, float top);

		const float GetRotation() const { return m_Rotation; }
		void SetRotation(float rotation) { m_Rotation = rotation; RecalculateViewMatrix(); }

	protected:
		virtual void RecalculateViewMatrix() override;

	private:
		float m_Rotation = 0.0f;
	};
}

