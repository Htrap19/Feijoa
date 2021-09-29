#include "fjpch.h"
#include "PerspectiveCameraController.h"
#include "Feijoa/Core/Input.h"

namespace Feijoa
{

	PerspectiveCameraController::PerspectiveCameraController(const glm::vec3& position, float aspectRatio)
		: m_Camera(position, aspectRatio)
	{
	}

	void PerspectiveCameraController::OnUpdate(Timestep ts)
	{
		FJ_PROFILE_FUNCTION();

		if (Input::IsKeyPressed(FJ_KEY_A))
			m_Camera.UpdateDir(PerspectiveCamera::Direction::Left, ts);
		if (Input::IsKeyPressed(FJ_KEY_D))
			m_Camera.UpdateDir(PerspectiveCamera::Direction::Right, ts);
		if (Input::IsKeyPressed(FJ_KEY_W))
			m_Camera.UpdateDir(PerspectiveCamera::Direction::Forward, ts);
		if (Input::IsKeyPressed(FJ_KEY_S))
			m_Camera.UpdateDir(PerspectiveCamera::Direction::Backward, ts);
		if (Input::IsKeyPressed(FJ_KEY_SPACE))
			m_Camera.UpdateDir(PerspectiveCamera::Direction::Top, ts);
		if (Input::IsKeyPressed(FJ_KEY_LEFT_SHIFT))
			m_Camera.UpdateDir(PerspectiveCamera::Direction::Bottom, ts);

		auto [x, y] = Input::GetMousePosition();
		float dx = x - m_LastX;
		float dy = m_LastY - y;
		m_LastX = x;
		m_LastY = y;
		if (dx != 0 || dy != 0)
			m_Camera.UpdatePosition(dx, dy);
	}

	void PerspectiveCameraController::OnEvent(Event& e)
	{
		FJ_PROFILE_FUNCTION();

		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowResizeEvent>(FJ_BIND_EVENT_FN(PerspectiveCameraController::OnWindowResize));
	}

	bool PerspectiveCameraController::OnWindowResize(WindowResizeEvent& e)
	{
		FJ_PROFILE_FUNCTION();

		m_Camera.SetAspectRatio((float)e.GetWidth() / (float)e.GetHeight());

		return false;
	}

}