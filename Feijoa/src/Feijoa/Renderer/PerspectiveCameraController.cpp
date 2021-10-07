#include "fjpch.h"
#include "PerspectiveCameraController.h"
#include "Feijoa/Core/Input.h"
#include "Feijoa/Core/KeyCodes.h"

namespace Feijoa
{

	PerspectiveCameraController::PerspectiveCameraController(const glm::vec3& position, float aspectRatio)
		: m_Camera(position, aspectRatio)
	{
	}

	void PerspectiveCameraController::OnUpdate(Timestep ts)
	{
		FJ_PROFILE_FUNCTION();

		if (Input::IsKeyPressed(Key::A))
			m_Camera.UpdateDir(PerspectiveCamera::Direction::Left, ts);
		if (Input::IsKeyPressed(Key::D))
			m_Camera.UpdateDir(PerspectiveCamera::Direction::Right, ts);
		if (Input::IsKeyPressed(Key::W))
			m_Camera.UpdateDir(PerspectiveCamera::Direction::Forward, ts);
		if (Input::IsKeyPressed(Key::S))
			m_Camera.UpdateDir(PerspectiveCamera::Direction::Backward, ts);
		if (Input::IsKeyPressed(Key::Space))
			m_Camera.UpdateDir(PerspectiveCamera::Direction::Top, ts);
		if (Input::IsKeyPressed(Key::LeftShift))
			m_Camera.UpdateDir(PerspectiveCamera::Direction::Bottom, ts);

		auto cursor = Input::GetMousePosition();
		float dx = cursor.x - m_LastX;
		float dy = m_LastY - cursor.y;
		m_LastX = cursor.x;
		m_LastY = cursor.y;
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