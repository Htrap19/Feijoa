#pragma once

#include <glm/glm.hpp>
#include "Feijoa/Scene/SceneCamera.h"
#include "Feijoa/Scene/ScriptableEntity.h"
#include "Feijoa/Scene/AssimpEntity.h"
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
		glm::mat4 Transform{ 1.0f };

		TransformComponent() = default;
		TransformComponent(const TransformComponent&) = default;
		TransformComponent(const glm::mat4& transform)
			: Transform(transform) {}

		operator glm::mat4& () { return Transform; }
		operator const glm::mat4& () const { return Transform; }
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
		AssimpEntity Model;

		MeshComponent(const MeshComponent&) = default;
		MeshComponent(const std::string& path)
			: Model(path) {}
	};
}