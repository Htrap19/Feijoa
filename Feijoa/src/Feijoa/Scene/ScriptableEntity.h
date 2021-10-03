#pragma once

#include "Feijoa/Scene/Entity.h"

namespace Feijoa
{
	class ScriptableEntity
	{
	public:
		template <typename T>
		T& GetComponent()
		{
			return m_Entity.GetComponent<T>();
		}

	private:
		Entity m_Entity;
		friend class Scene;
	};
}