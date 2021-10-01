#pragma once

#include <entt.hpp>
#include "Feijoa/Core/Timestep.h"

namespace Feijoa
{
	class Scene
	{
	public:
		Scene();
		~Scene();

		entt::entity CreateEntity();

		// Temp
		entt::registry& GetRegistry() { return m_Registry; }

		void OnUpdate(Timestep ts);

	private:
		entt::registry m_Registry;
	};
}