#pragma once

#include "Feijoa/Renderer/Camera.h"
#include "Feijoa/Core/Timestep.h"

namespace Feijoa
{
	class SceneCamera : public Camera
	{
	public:
		enum class ProjectionType { Perspective = 0, Orthographic = 1 };
	public:
		SceneCamera();
		virtual ~SceneCamera() = default;

		void SetOthographic(float size, float nearClip, float farClip);
		void SetPerspective(float verticalFOV, float nearClip, float farClip);

		void SetViewportSize(uint32_t width, uint32_t height);

		inline float GetPerspectiveVerticalFOV() const { return m_PerspectiveFOV; }
		inline void SetPerspectiveVerticalFOV(float verticalFOV) { m_PerspectiveFOV = verticalFOV; RecalculateProjection(); }

		inline float GetPerspectiveNearClip() const { return m_PerspectiveNear; }
		inline void SetPerspectiveNearClip(float nearClip) { m_PerspectiveNear = nearClip; RecalculateProjection(); }

		inline float GetPerspectiveFarClip() const { return m_PerspectiveFar; }
		inline void SetPerspectiveFarClip(float farClip) { m_PerspectiveFar = farClip; RecalculateProjection(); }

		inline float GetOrthographicSize() const { return m_OrthographicsSize; }
		inline void SetOrthographicSize(float size) { m_OrthographicsSize = size; RecalculateProjection(); }

		inline float GetOrthographicNearClip() const { return m_OrthographicNear; }
		inline void SetOrthographicNearClip(float nearClip) { m_OrthographicNear = nearClip; RecalculateProjection(); }

		inline float GetOrthographicFarClip() const { return m_OrthographicFar; }
		inline void SetOrthographicFarClip(float farClip) { m_OrthographicFar = farClip; RecalculateProjection(); }

		inline ProjectionType GetProjectionType() const { return m_ProjectionType; }
		inline void SetProjectionType(ProjectionType type) { m_ProjectionType = type; RecalculateProjection(); }
		
	private:
		void RecalculateProjection();

	private:
		ProjectionType m_ProjectionType = ProjectionType::Orthographic;

		float m_PerspectiveFOV = glm::radians(45.0f);
		float m_PerspectiveNear = 0.01f, m_PerspectiveFar = 1000.0f;
		
		float m_OrthographicsSize = 10.0f;
		float m_OrthographicNear = -1.0f, m_OrthographicFar = 1.0f;
		
		float m_AspectRatio = 0.0f;
	};

	class PerspectiveSceneCamera : public Camera
	{
	public:
		enum class Direction
		{
			None = -1,
			Forward, Backward,
			Left, Right,
			Top, Bottom
		};

	public:
		PerspectiveSceneCamera(const glm::vec3& position, float aspectRatio, float fov = 45.0f, float nearClip = 1.0f, float farClip = 100.0f);
		PerspectiveSceneCamera(const glm::vec3& position, uint32_t width, uint32_t height);
		virtual ~PerspectiveSceneCamera() = default;

		void SetViewportSize(uint32_t width, uint32_t height);

		// Note: UpdatePosition function requires delta(change in) 'x' or 'y',
		// not mouse 'x' or 'y' positions
		// E.g
		//		...
		//		float lastX, lastY;
		//		...
		// 
		// ...
		// void OnUpdate(TimeStep ts)
		// {
		//		...
		//		auto& [x, y] = Input::GetMousePosition();
		//		float dx = x - lastX; // This is the value will be passed the update function
		//		// Note: Y is inverted here
		//		float dy = lastY - y; // This is the value will be passed the update function
		//		lastX = x;
		//		lastY = y;
		//		UpdateDirection(dx, dy); // Like so
		//		...
		// }
		// ...
		void UpdatePosition(float dx, float dy);
		void UpdateDirection(Direction dir, Timestep ts);

		inline const glm::mat4& GetView() const { return m_View; }
		inline const float GetFOV() const { return m_FOV; }
		inline void SetFOV(float fov) { m_FOV = fov; }
		inline const float GetSpeed() const { return m_Speed; }
		inline void SetSpeed(float speed) { m_Speed = speed; }
		inline void SetFarClip(float farClip) { m_FarClip = farClip; }
		inline const float GetFarClip() const { return m_FarClip; }
		inline void SetNearClip(float nearClip) { m_NearClip = nearClip; }
		inline const float GetNearClip() const { return m_NearClip; }

	private:
		void RecalculateView();

	private:
		glm::vec3 m_Position = { 0.0f, 0.0f, 0.0f };

		glm::vec3 m_CameraFront, m_CameraUp, m_CameraRight;
		glm::vec3 m_WorldUp = { 0.0f, 1.0f, 0.0f };

		glm::mat4 m_View = glm::mat4(1.0f);

		float m_FOV, m_Speed = 2.5f, m_AspectRatio;
		float m_Yaw = -90.0f, m_Pitch = 0.0f;
		float m_NearClip, m_FarClip;
	};
}