#include "fjpch.h"
#include "SceneCamera.h"

#include <glm/gtc/matrix_transform.hpp>

namespace Feijoa
{

	SceneCamera::SceneCamera()
	{
		RecalculateProjection();
	}

	void SceneCamera::SetOthographic(float size, float nearClip, float farClip)
	{
		m_ProjectionType = ProjectionType::Orthographic;

		m_OrthographicsSize = size;
		m_OrthographicNear = nearClip;
		m_OrthographicFar = farClip;

		RecalculateProjection();
	}

	void SceneCamera::SetPerspective(float verticalFOV, float nearClip, float farClip)
	{
		m_ProjectionType = ProjectionType::Perspective;
		m_PerspectiveFOV = verticalFOV;
		m_PerspectiveNear = nearClip;
		m_PerspectiveFar = farClip;

		RecalculateProjection();
	}

	void SceneCamera::SetViewportSize(uint32_t width, uint32_t height)
	{
		m_AspectRatio = (float)width / (float)height;
		RecalculateProjection();
	}

	void SceneCamera::RecalculateProjection()
	{
		if (m_ProjectionType == ProjectionType::Perspective)
			m_Projection = glm::perspective(m_PerspectiveFOV, m_AspectRatio, m_PerspectiveNear, m_PerspectiveFar);
		else
		{
			float ortholeft = -m_OrthographicsSize * m_AspectRatio * 0.5f;
			float orthoright = m_OrthographicsSize * m_AspectRatio * 0.5f;
			float orthobottom = -m_OrthographicsSize * 0.5f;
			float orthotop = m_OrthographicsSize * 0.5f;

			m_Projection = glm::ortho(ortholeft, orthoright, orthobottom, orthotop, m_OrthographicNear, m_OrthographicFar);
		}
	}

	// =========================================================================================
	// Perspective Scene Camera ================================================================
	// =========================================================================================

	PerspectiveSceneCamera::PerspectiveSceneCamera(const glm::vec3& position, float aspectRatio)
		: Camera(glm::perspective(glm::radians(m_FOV), aspectRatio, 1.0f, 100.0f)), m_Position(position), m_AspectRatio(aspectRatio)
	{
		RecalculateView();
	}

	PerspectiveSceneCamera::PerspectiveSceneCamera(const glm::vec3& position, uint32_t width, uint32_t height)
		: PerspectiveSceneCamera(position, ((float)width/(float)height))
	{
	}

	PerspectiveSceneCamera::PerspectiveSceneCamera()
		: PerspectiveSceneCamera(glm::vec3(0.0f, 0.0f, 0.0f), 0)
	{
	}

	void PerspectiveSceneCamera::SetViewportSize(uint32_t width, uint32_t height)
	{
		m_AspectRatio = (float)width / (float)height;
		m_Projection = glm::perspective(glm::radians(m_FOV), m_AspectRatio, 1.0f, 100.0f);
	}

	void PerspectiveSceneCamera::UpdatePosition(float dx, float dy)
	{
		m_Yaw += dx;
		m_Pitch += dy;

		if (m_Pitch >= 89.0f)
			m_Pitch = 89.0f;
		else if (m_Pitch <= -89.0f)
			m_Pitch = -89.0f;

		RecalculateView();
	}

	void PerspectiveSceneCamera::UpdateDirection(Direction dir, Timestep ts)
	{
		float velocity = ts * m_Speed;

		switch (dir)
		{
		case Feijoa::PerspectiveSceneCamera::Direction::None:
			break;

		case Feijoa::PerspectiveSceneCamera::Direction::Forward:
			m_Position += m_CameraFront * velocity;
			break;
		case Feijoa::PerspectiveSceneCamera::Direction::Backward:
			m_Position -= m_CameraFront * velocity;
			break;
		case Feijoa::PerspectiveSceneCamera::Direction::Left:
			m_Position -= m_CameraRight * velocity;
			break;
		case Feijoa::PerspectiveSceneCamera::Direction::Right:
			m_Position += m_CameraRight * velocity;
			break;
		case Feijoa::PerspectiveSceneCamera::Direction::Top:
			m_Position += m_CameraUp * velocity;
			break;
		case Feijoa::PerspectiveSceneCamera::Direction::Bottom:
			m_Position -= m_CameraUp * velocity;
			break;

		default:
			break;
		}

		RecalculateView();
	}

	void PerspectiveSceneCamera::RecalculateView()
	{
		glm::vec3 direction;
		direction.x = cos(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));
		direction.y = sin(glm::radians(m_Pitch));
		direction.z = sin(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));

		m_CameraFront = glm::normalize(direction);
		m_CameraRight = glm::normalize(glm::cross(m_CameraFront, m_WorldUp));
		m_CameraUp = glm::normalize(glm::cross(m_CameraRight, m_CameraFront));

		m_View = glm::lookAt(m_Position, m_Position + m_CameraFront, m_CameraUp);
	}

}