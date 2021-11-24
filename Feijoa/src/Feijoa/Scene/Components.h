#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/quaternion.hpp>

#include "Feijoa/Scene/SceneCamera.h"
#include "Feijoa/Scene/ScriptableEntity.h"
#include "Feijoa/Scene/ModelEntity.h"
#include "Feijoa/Renderer/VertexArray.h"

namespace Feijoa
{
	struct ModelVertex;

	struct TagComponent
	{
		std::string Tag;

		TagComponent() = default;
		TagComponent(const TagComponent&) = default;
		TagComponent(const std::string& tag)
			: Tag(tag) {}
	};

	struct CameraComponent
	{
		SceneCamera Camera;
		bool Primary = true;
		bool FixedAspectRatio = false;

		CameraComponent() = default;
		CameraComponent(const CameraComponent&) = default;
	};

	struct PerspectiveCameraComponent
	{
		PerspectiveSceneCamera Camera;
		bool Primary = true;
		bool FixedAspectRatio = false;

		PerspectiveCameraComponent(const PerspectiveCameraComponent&) = default;
		PerspectiveCameraComponent(const glm::vec3& position, float aspectRatio)
			: Camera(position, aspectRatio) {}
	};

	struct NativeScriptComponent
	{
		ScriptableEntity* Instance = nullptr;

		ScriptableEntity* (*InstantiateScript)();
		void (*DestroyScript)(NativeScriptComponent*);

		template <typename T>
		void Bind()
		{
			InstantiateScript = []() { return static_cast<ScriptableEntity*>(new T()); };
			DestroyScript = [](NativeScriptComponent* ncs) { delete ncs->Instance; ncs->Instance = nullptr; };
		}
	};

	struct TransformComponent
	{
		glm::vec3 Translation = { 0.0f, 0.0f, 0.0f };
		glm::vec3 Rotation = { 0.0f, 0.0f, 0.0f };
		glm::vec3 Scale = { 1.0f, 1.0f, 1.0f };

		TransformComponent() = default;
		TransformComponent(const TransformComponent&) = default;
		TransformComponent(const glm::vec3& translation)
			: Translation(translation) {}

		inline glm::mat4 GetTransform() const
		{
			glm::mat4 rotation = glm::toMat4(glm::quat(Rotation));

			return glm::translate(glm::mat4(1.0f), Translation)
				* rotation
				* glm::scale(glm::mat4(1.0f), Scale);
		}
	};

	struct SpriteRendererComponent
	{
		glm::vec4 Color{ 1.0f, 1.0f, 1.0f, 1.0f };

		SpriteRendererComponent() = default;
		SpriteRendererComponent(const SpriteRendererComponent&) = default;
		SpriteRendererComponent(const glm::vec4& color)
			: Color(color) {}
	};

	struct MeshComponent
	{
		std::vector<ModelVertex> Vertices;
		std::vector<uint32_t> Indices;
		std::vector<Ref<Texture2D>> Textures;

		MeshComponent(const MeshComponent&) = default;
		MeshComponent(const std::vector<ModelVertex>& vertices, const std::vector<uint32_t>& indices, const std::vector<Ref<Texture2D>>& textures = {})
			: Vertices(vertices), Indices(indices), Textures(textures) {}

		inline bool HasTexture() const { return !Textures.empty(); }
	};

	struct MeshContainerComponent
	{
		std::vector<MeshComponent> Meshes;

		MeshContainerComponent() = default;
		MeshContainerComponent(const MeshContainerComponent&) = default;
		MeshContainerComponent(const std::vector<MeshComponent>& meshes)
			: Meshes(meshes) {}

		inline void AddMesh(const MeshComponent& mesh) { Meshes.push_back(mesh); }
	};

	struct ModelComponent
	{
		ModelEntity Model;

		ModelComponent(const ModelComponent&) = default;
		ModelComponent(Entity* entity, const std::string& path, const glm::vec3& position, const glm::vec3& size)
			: Model(entity, path, position, size) {}
	};
}