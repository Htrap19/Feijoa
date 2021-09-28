#include "fjpch.h"
#include "PerspectiveCamera.h"

namespace Feijoa
{

	PerspectiveCamera::PerspectiveCamera(const glm::vec3& position, float aspectRatio)
		: m_Position(position), m_AspectRatio(aspectRatio)
	{
		UpdateCamera();
	}

	void PerspectiveCamera::UpdatePosition(float dx, float dy)
	{
		m_Yaw += dx;
		m_Pitch += dy;

		if (m_Pitch >= 89.0f)
			m_Pitch = 89.0f;
		else if (m_Pitch <= -89.0f)
			m_Pitch = -89.0f;

		UpdateCamera();
	}

	void PerspectiveCamera::UpdateDir(Direction dir, Timestep ts)
	{
		float velocity = ts * m_Speed;

		switch (dir)
		{
		case Feijoa::PerspectiveCamera::Direction::None:
			break;
		case Feijoa::PerspectiveCamera::Direction::Forward:
			m_Position += m_CameraFront * velocity;
			break;
		case Feijoa::PerspectiveCamera::Direction::Backward:
			m_Position -= m_CameraFront * velocity;
			break;
		case Feijoa::PerspectiveCamera::Direction::Top:
			m_Position += m_CameraUp * velocity;
			break;
		case Feijoa::PerspectiveCamera::Direction::Bottom:
			m_Position -= m_CameraUp * velocity;
			break;
		case Feijoa::PerspectiveCamera::Direction::Left:
			m_Position -= m_CameraRight * velocity;
			break;
		case Feijoa::PerspectiveCamera::Direction::Right:
			m_Position += m_CameraRight * velocity;
			break;

		default:
			break;
		}
	}

	void PerspectiveCamera::UpdateFOV(float fov)
	{
		if (m_FOV >= m_MinFOV && m_FOV <= m_MaxFOV)
			m_FOV -= fov;
		else if (m_FOV < m_MinFOV)
			m_FOV = m_MinFOV;
		else
			m_FOV = m_MaxFOV;
	}

	void PerspectiveCamera::UpdateCamera()
	{
		glm::vec3 direction;
		direction.x = cos(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));
		direction.y = sin(glm::radians(m_Pitch));
		direction.z = sin(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));

		m_CameraFront = glm::normalize(direction);
		m_CameraRight = glm::normalize(glm::cross(m_CameraFront, m_WorldUp));
		m_CameraUp = glm::normalize(glm::cross(m_CameraRight, m_CameraFront));
	}

}