#include "fjpch.h"
#include "Scene.h"

#include "Feijoa/Scene/Components.h"
#include "Feijoa/Scene/Entity.h"
#include "Feijoa/Renderer/Renderer2D.h"
#include "Feijoa/Renderer/Renderer3D.h"

namespace Feijoa
{

	Scene::Scene()
	{
	}

	Scene::~Scene()
	{
	}

	Entity Scene::CreateEntity(const std::string& name)
	{
		Entity entity = { m_Registry.create(), this };
		entity.AddComponent<TransformComponent>();
		auto & tag = entity.AddComponent<TagComponent>();
		tag.Tag = name.empty() ? "Entity" : name;
		return entity;
	}

	void Scene::OnUpdate(Timestep ts)
	{
		// Update scripts
		{
			m_Registry.view<NativeScriptComponent>().each([=](auto entity, auto& ncs)
				{
					if (!ncs.Instance)
					{
						ncs.InstantiateFunction();
						ncs.Instance->m_Entity = Entity{ entity, this };

						if (ncs.OnCreateFunction)
							ncs.OnCreateFunction(ncs.Instance);
					}

					if (ncs.OnUpdateFunction)
						ncs.OnUpdateFunction(ncs.Instance, ts);
				});
		}

#ifdef FJ_2DSCENE
		Camera* mainCamera = nullptr;
		glm::mat4* cameraTransform = nullptr;

		{
			auto view = m_Registry.view<TransformComponent, CameraComponent>();
			for (auto entity : view)
			{
				auto& [transform, camera] = view.get<TransformComponent, CameraComponent>(entity);
				if (camera.Primary)
				{
					mainCamera = &camera.Camera;
					cameraTransform = &transform.Transform;
					break;
				}
			}
		}

		if (mainCamera)
		{
			Renderer2D::BeginScene(mainCamera->GetProjection(), *cameraTransform);
			auto group = m_Registry.group<TransformComponent>(entt::get<SpriteRendererComponent>);

			for (auto entity : group)
			{
				auto& [transform, sprite] = group.get<TransformComponent, SpriteRendererComponent>(entity);
				Renderer2D::DrawQuad(transform, sprite.Color);
			}

			Renderer2D::EndScene();
		}
#endif
		{
			
			auto view = m_Registry.view<MeshComponent>();

			for (auto entity : view)
			{
				auto& vertexArray = view.get<MeshComponent>(entity).VertexArray;
				Renderer3D::DrawModel(vertexArray);
			}
		}
	}

	void Scene::OnViewportResize(uint32_t width, uint32_t height)
	{
		m_ViewportWidth = width, m_ViewportHeight = height;

		auto& view = m_Registry.view<CameraComponent>();

		for (auto entity : view)
		{
			auto& cameraComponent = view.get<CameraComponent>(entity);
			if (!cameraComponent.FixedAspectRatio)
				cameraComponent.Camera.SetViewportSize(width, height);
		}
	}

}