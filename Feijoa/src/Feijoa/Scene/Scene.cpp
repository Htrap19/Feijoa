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

	void Scene::DestroyEntity(Entity entity)
	{
		m_Registry.destroy(entity);
	}

	void Scene::OnUpdateRuntime(Timestep ts)
	{
		// Update scripts
		{
			m_Registry.view<NativeScriptComponent>().each([=](auto entity, auto& ncs)
				{
					if (!ncs.Instance)
					{
						ncs.Instance = ncs.InstantiateScript();
						ncs.Instance->m_Entity = Entity{ entity, this };
						ncs.Instance->OnCreate();
					}

					ncs.Instance->OnUpdate(ts);
				});
		}

		Camera* mainCamera = nullptr;
		glm::mat4 cameraTransform;

		{
			auto view = m_Registry.view<TransformComponent, CameraComponent>();
			for (auto entity : view)
			{
				auto [transform, camera] = view.get<TransformComponent, CameraComponent>(entity);
				if (camera.Primary)
				{
					mainCamera = &camera.Camera;
					cameraTransform = transform.GetTransform();
					break;
				}
			}
		}

		if (mainCamera)
		{
			Renderer2D::BeginScene(mainCamera->GetProjection(), cameraTransform);
			auto group = m_Registry.group<TransformComponent>(entt::get<SpriteRendererComponent>);

			for (auto entity : group)
			{
				auto [transform, sprite] = group.get<TransformComponent, SpriteRendererComponent>(entity);
				Renderer2D::DrawSprite(transform.GetTransform(), sprite.Color, (int)entity);
			}

			Renderer2D::EndScene();
		}

		Camera* mainPerspectiveCamera = nullptr;
		const glm::mat4* mainView = nullptr;

		{
			auto view = m_Registry.view<PerspectiveCameraComponent>();

			for (auto entity : view)
			{
				auto& camera = view.get<PerspectiveCameraComponent>(entity);
				if (camera.Primary)
				{
					mainPerspectiveCamera = &camera.Camera;
					mainView = &camera.Camera.GetView();
					break;
				}
			}
		}

		if (mainPerspectiveCamera)
		{
			Renderer3D::BeginScene(*mainPerspectiveCamera, *mainView);
			auto group = m_Registry.group<TransformComponent, MeshComponent>();
			for (auto entity : group)
			{
				auto& [transform, meshComponent] = group.get<TransformComponent, MeshComponent>(entity);
				for (auto& mesh : meshComponent.Model.GetMeshes())
				{
					if (m_Registry.any_of<SpriteRendererComponent>(entity))
					{
						auto& src = m_Registry.get<SpriteRendererComponent>(entity);
						Renderer3D::DrawMesh(transform.Transform, mesh, src.Color);
					}
					else
						Renderer3D::DrawMesh(transform.Transform, mesh);
				}
			}
			Renderer3D::EndScene();
		}
	}

	void Scene::OnUpdateEditor(Timestep ts, EditorCamera& camera)
	{
		Renderer2D::BeginScene(camera);

		auto group = m_Registry.group<TransformComponent>(entt::get<SpriteRendererComponent>);
		for (auto entity : group)
		{
			auto [transform, sprite] = group.get<TransformComponent, SpriteRendererComponent>(entity);
			Renderer2D::DrawSprite(transform.GetTransform(), sprite.Color, (int)entity);
		}

		Renderer2D::EndScene();
	}

	void Scene::OnViewportResize(uint32_t width, uint32_t height)
	{
		m_ViewportWidth = width, m_ViewportHeight = height;

		{
			auto& view = m_Registry.view<CameraComponent>();

			for (auto entity : view)
			{
				auto& cameraComponent = view.get<CameraComponent>(entity);
				if (!cameraComponent.FixedAspectRatio)
					cameraComponent.Camera.SetViewportSize(width, height);

			}
		}
		{
			auto& view = m_Registry.view<PerspectiveCameraComponent>();

			for (auto entity : view)
			{
				auto& cameraComponent = view.get<PerspectiveCameraComponent>(entity);
				if (!cameraComponent.FixedAspectRatio)
					cameraComponent.Camera.SetViewportSize(width, height);

			}
		}
		
	}

	Entity Scene::GetPrimaryCameraEntity()
	{
		auto view = m_Registry.view<CameraComponent>();
		for (auto entity : view)
		{
			const auto& camera = view.get<CameraComponent>(entity);
			if (camera.Primary)
				return { entity, this };
		}

		return { entt::null, this };
	}

	template <typename T>
	void Scene::OnComponentAdded(Entity entity, T& component)
	{
		static_assert(false);
	}

	template <>
	void Scene::OnComponentAdded(Entity entity, TransformComponent& component)
	{
	}

	template <>
	void Scene::OnComponentAdded(Entity entity, CameraComponent& component)
	{
		component.Camera.SetViewportSize(m_ViewportWidth, m_ViewportHeight);
	}

	template <>
	void Scene::OnComponentAdded(Entity entity, SpriteRendererComponent& component)
	{
	}

	template <>
	void Scene::OnComponentAdded(Entity entity, TagComponent& component)
	{
	}

	template <>
	void Scene::OnComponentAdded(Entity entity, NativeScriptComponent& component)
	{
	}
}