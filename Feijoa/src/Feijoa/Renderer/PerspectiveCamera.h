#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Feijoa/Core/Timestep.h"

namespace Feijoa
{
	class PerspectiveCamera
	{
	public:
		enum class Direction
		{
			None = -1,
			Forward,
			Backward,
			Top,
			Bottom,
			Left,
			Right
		};

	public:
		PerspectiveCamera(const glm::vec3& position, float aspectRatio);

		inline void SetPosition(const glm::vec3& position) { m_Position = position; UpdatePosition(position.x, position.y); }
		inline const glm::vec3& GetPosition() const { return m_Position; }

		inline void SetAspectRatio(float aspectRatio) { m_AspectRatio = aspectRatio; }
		inline void SetFOV(float fov, float minFov = 1.0f, float maxFov = 180.0f) { m_FOV = fov, m_MinFOV = minFov, m_MaxFOV = maxFov; }
		inline const float GetFOV() const { return m_FOV; }
		inline const float GetMinFOV() const { return m_MinFOV; }
		inline const float GetMaxFOV() const { return m_MaxFOV; }

		void UpdatePosition(float dx, float dy);
		void UpdateDir(Direction dir, Timestep ts);
		void UpdateFOV(float fov);

		inline glm::mat4 GetViewMatrix() const { return glm::lookAt(m_Position, m_Position + m_CameraFront, m_CameraUp); }
		inline glm::mat4 GetProjectionMatrix() const { return glm::perspective(glm::radians(m_FOV), m_AspectRatio, 1.0f, 100.0f); }
		inline glm::mat4 GetViewProjectionMatrix() const { return GetProjectionMatrix() * GetViewMatrix(); }

	private:
		void UpdateCamera();

	private:
		glm::vec3 m_Position;

		glm::vec3 m_CameraFront = { 0.0f, 0.0f, -1.0f };
		glm::vec3 m_CameraUp;
		glm::vec3 m_CameraRight;

		glm::vec3 m_WorldUp = { 0.0f, 1.0f, 0.0f };

		float m_FOV = 45.0f, m_MinFOV = 1.0f, m_MaxFOV = 180.0f;
		float m_Yaw = -90.0f, m_Pitch = 0.0f, m_Speed = 2.5f, m_AspectRatio;
	};
}