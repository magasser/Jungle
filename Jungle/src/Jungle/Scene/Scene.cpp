#include "jnglpch.h"
#include "Scene.h"

#include <glm/glm.hpp>

#include "Jungle/Rendering/Renderer2D.h"
#include "Jungle/Scene/Components.h"
#include "Jungle/Scene/Entity.h"

namespace Jungle
{
	Scene::Scene()
	{
		JNGL_PROFILE_FUNCTION();
	}

	Scene::~Scene()
	{
		JNGL_PROFILE_FUNCTION();
	}

	void Scene::OnUpdate(Timestep timestep)
	{
		JNGL_PROFILE_FUNCTION();

		Camera* mainCamera = nullptr;
		glm::mat4* cameraTransform = nullptr;
		auto view = m_Registry.view<CameraComponent, TransformComponent>();
		for (auto entity : view)
		{
			auto [camera, transform] = view.get<CameraComponent, TransformComponent>(entity);

			if (camera.Primary)
			{
				mainCamera = &camera.Camera;
				cameraTransform = &transform.Transform;
				break;
			}
		}

		if (mainCamera)
		{
			Renderer2D::BeginScene(*mainCamera, *cameraTransform);
			auto view = m_Registry.view<TransformComponent, SpriteRendererComponent>();
			for (auto entity : view)
			{
				auto [transform, sprite] = view.get<TransformComponent, SpriteRendererComponent>(entity);

				Renderer2D::DrawQuad(transform, sprite.Color);
			}
			Renderer2D::EndScene();
		}
	}

	void Scene::OnViewportResize(uint32_t width, uint32_t height)
	{
		JNGL_PROFILE_FUNCTION();

		m_ViewportWidth = width;
		m_ViewportHeight = height;

		auto view = m_Registry.view<CameraComponent>();
		for (auto entity : view)
		{
			auto& cameraComponent = view.get<CameraComponent>(entity);

			if (!cameraComponent.FixedAspectRatio)
			{
				cameraComponent.Camera.SetViewportSize(m_ViewportWidth, m_ViewportHeight);
			}
		}
	}

	Entity Scene::CreateEntity(const std::string& name)
	{
		JNGL_PROFILE_FUNCTION();

		Entity entity = { m_Registry.create(), this };
		entity.AddComponent<TransformComponent>();

		TagComponent& tag = entity.AddComponent<TagComponent>();
		tag.Tag = name.empty() ? "Entity" : name;

		return entity;
	}
}
