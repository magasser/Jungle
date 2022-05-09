#pragma once

#include <entt/entt.hpp>

#include "Jungle/Scene/Scene.h"

namespace Jungle
{
	class Entity
	{
	public:
		Entity() = default;
		Entity(entt::entity handle, Scene* scene) : m_EntityHandle(handle), m_Scene(scene) { JNGL_PROFILE_FUNCTION(); }
		Entity(const Entity& other) = default;

		template<typename T>
		bool HasComponent()
		{
			JNGL_PROFILE_FUNCTION();
			return m_Scene->m_Registry.any_of<T>(m_EntityHandle);
		}

		template<typename T>
		T& GetComponent()
		{
			JNGL_PROFILE_FUNCTION();
			JNGL_CORE_ASSERT(HasComponent<T>(), "Entity does not have component.");
			return m_Scene->m_Registry.get<T>(m_EntityHandle);
		}

		template<typename T, typename... Args>
		T& AddComponent(Args&&... args)
		{
			JNGL_PROFILE_FUNCTION();
			//JNGL_CORE_ASSERT(!HasComponent<T>(), "Entity already has component.");
			return m_Scene->m_Registry.emplace<T>(m_EntityHandle, std::forward<Args>(args)...);
		}

		template<typename T>
		void RemoveComponent()
		{
			JNGL_PROFILE_FUNCTION();
			JNGL_CORE_ASSERT(HasComponent<T>(), "Entity does not have component.");
			m_Scene->m_Registry.remove<T>(m_EntityHandle);
		}

		operator bool() const { return m_EntityHandle != entt::null; }
	private:
		entt::entity m_EntityHandle{ entt::null };
		Scene* m_Scene = nullptr;
	};
}

