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
		m_OrthographicsSize = size;
		m_OrthographicNear = nearClip;
		m_OrthographicFar = farClip;

		RecalculateProjection();
	}

	void SceneCamera::SetViewportSize(uint32_t width, uint32_t height)
	{
		m_AspectRatio = (float)width / (float)height;
		RecalculateProjection();
	}

	void SceneCamera::RecalculateProjection()
	{
		float ortholeft = -m_OrthographicsSize * m_AspectRatio * 0.5f;
		float orthoright = m_OrthographicsSize * m_AspectRatio * 0.5f;
		float orthobottom = -m_OrthographicsSize * 0.5f;
		float orthotop = m_OrthographicsSize * 0.5f;

		m_Projection = glm::ortho(ortholeft, orthoright, orthobottom, orthotop, m_OrthographicNear, m_OrthographicFar);
	}

}