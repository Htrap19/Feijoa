#pragma once

#include "Feijoa/Renderer/Camera.h"

namespace Feijoa
{
	class SceneCamera : public Camera
	{
	public:
		SceneCamera();
		virtual ~SceneCamera() = default;

		void SetOthographic(float size, float nearClip, float farClip);
		void SetViewportSize(uint32_t width, uint32_t height);

		inline float GetOrthographicSize() const { return m_OrthographicsSize; }
		inline void SetOrthographicSize(float size) { m_OrthographicsSize = size; RecalculateProjection(); }
		
	private:
		void RecalculateProjection();

	private:
		float m_OrthographicsSize = 10.0f;
		float m_OrthographicNear = -1.0f, m_OrthographicFar = 1.0f;

		float m_AspectRatio = 0.0f;
	};
}