#pragma once

#include "PerspectiveCamera.h"
#include "Feijoa/Events/Event.h"
#include "Feijoa/Events/ApplicationEvent.h"
#include "Feijoa/Events/MouseEvent.h"

namespace Feijoa
{
	class PerspectiveCameraController
	{
	public:
		PerspectiveCameraController(const glm::vec3& position, float aspectRatio);

		void OnUpdate(Timestep ts);
		void OnEvent(Event& e);

		inline PerspectiveCamera& GetCamera() { return m_Camera; }
		inline const PerspectiveCamera& GetCamera() const { return m_Camera; }

	private:
		bool OnWindowResize(WindowResizeEvent& e);

	private:
		PerspectiveCamera m_Camera;

		float m_LastX = 0.0f , m_LastY = 0.0f;
	};
}