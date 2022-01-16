#pragma once

#include "Feijoa/Core/Base.h"
#include "Feijoa/Core/Log.h"
#include "Feijoa/Scene/Scene.h"
#include "Feijoa/Scene/Entity.h"

namespace Feijoa
{
	class SceneHierarchyPanel
	{
	public:
		SceneHierarchyPanel() = default;
		SceneHierarchyPanel(const Ref<Scene>& context);

		void SetContext(const Ref<Scene>& context);
		
		void OnImGuiRender();

		inline Entity GetSelectedEntity() const { return m_SelectionContext; }

	private:
		void DrawEntityNode(Entity entity);
		void DrawComponents(Entity entity);

	private:
		Ref<Scene> m_Context;
		Entity m_SelectionContext;
	};
}