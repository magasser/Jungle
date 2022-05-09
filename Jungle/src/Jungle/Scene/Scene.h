#pragma once

#include <entt/entt.hpp>

#include "Jungle/Core/Core.h"
#include "Jungle/Core/Timestep.h"

namespace Jungle
{
	class Entity;

	class JUNGLE_API Scene
	{
	public:
		Scene();
		~Scene();

		void OnUpdate(Timestep timestep);
		void OnViewportResize(uint32_t width, uint32_t height);

		Entity CreateEntity(const std::string& name = std::string());

	private:
		entt::registry m_Registry;
		uint32_t m_ViewportWidth = 0, m_ViewportHeight = 0;

		friend class Entity;
	};
}

