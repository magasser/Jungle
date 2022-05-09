#include "jnglpch.h"
#include "SceneCamera.h"

#include <glm/gtc/matrix_transform.hpp>

namespace Jungle
{
	SceneCamera::SceneCamera()
	{
		JNGL_PROFILE_FUNCTION();
	}

	void SceneCamera::SetOrthographic(float size, float nearClip, float farClip)
	{
		JNGL_PROFILE_FUNCTION();

		m_OrthographicSize = size;
		m_OrthographicNear = nearClip;
		m_OrthographicFar = farClip;
		RecalculateProjection();
	}

	void SceneCamera::SetViewportSize(uint32_t width, uint32_t height)
	{
		JNGL_PROFILE_FUNCTION();

		m_AspectRatio = (float)width / (float)height;
		RecalculateProjection();
	}

	void SceneCamera::RecalculateProjection()
	{
		const float orthoLeft = -m_OrthographicSize * m_AspectRatio * 0.5f;
		const float orthoRight = m_OrthographicSize * m_AspectRatio * 0.5f;
		const float orthoBottom = -m_OrthographicSize * 0.5f;
		const float orthoTop = m_OrthographicSize * 0.5f;

		m_Projection = glm::ortho(orthoLeft, orthoRight, orthoRight, orthoTop, m_OrthographicNear, m_OrthographicFar);
	}
}
