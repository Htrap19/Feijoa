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
		void* Vertices = nullptr;
		uint32_t NumVertices = 0;
		uint32_t* Indices = nullptr;
		uint32_t NumIndices = 0;

		MeshComponent(const MeshComponent&) = default;
		MeshComponent(void* vertices, uint32_t numVertices, uint32_t* indices, uint32_t numIndices)
			: Vertices(vertices), NumVertices(numVertices), Indices(indices), NumIndices(numIndices) {}
	};

	struct NewMeshComponent
	{
		Ref<VertexArray> VertexArray;

		NewMeshComponent(const NewMeshComponent&) = default;
		NewMeshComponent(const Ref<Feijoa::VertexArray>& vertexArray)
			: VertexArray(vertexArray) {}
	};

	struct ModelComponent
	{
		ModelEntity Model;

		ModelComponent(const ModelComponent&) = default;
		ModelComponent(Entity* entity, const std::string& path, const glm::vec3& position, const glm::vec3& size)
			: Model(entity, path, position, size) {}
	};
}