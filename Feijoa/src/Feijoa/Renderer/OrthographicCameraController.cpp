#include "fjpch.h"
#include "OrthographicCameraController.h"

#include "Feijoa/Core/Input.h"
#include "Feijoa/Core/KeyCodes.h"

namespace Feijoa
{

	OrthographicCameraController::OrthographicCameraController(float aspectRatio, bool rotation /*= false*/)
		: m_AspectRatio(aspectRatio), 
		m_Bounds{ -m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, m_ZoomLevel, -m_ZoomLevel },
		m_Camera(m_Bounds.Left, m_Bounds.Right, m_Bounds.Bottom, m_Bounds.Top),
		m_Rotation(rotation)
	{
	}

	void OrthographicCameraController::OnUpdate(Timestep ts)
	{
		FJ_PROFILE_FUNCTION();

		if (Feijoa::Input::IsKeyPressed(FJ_KEY_A))
			m_CameraPosition.x -= m_CameraTranslationSpeed * ts;
		else if (Feijoa::Input::IsKeyPressed(FJ_KEY_D))
			m_CameraPosition.x += m_CameraTranslationSpeed * ts;

		if (Feijoa::Input::IsKeyPressed(FJ_KEY_W))
			m_CameraPosition.y += m_CameraTranslationSpeed * ts;
		else if (Feijoa::Input::IsKeyPressed(FJ_KEY_S))
			m_CameraPosition.y -= m_CameraTranslationSpeed * ts;

		if (m_Rotation)
		{
			if (Feijoa::Input::IsKeyPressed(FJ_KEY_Q))
				m_CameraRotation += m_CameraRotationSpeed * ts;
			if (Feijoa::Input::IsKeyPressed(FJ_KEY_E))
				m_CameraRotation -= m_CameraRotationSpeed * ts;

			m_Camera.SetRotation(m_CameraRotation);
		}

		m_Camera.SetPosition(m_CameraPosition);

		m_CameraTranslationSpeed = m_ZoomLevel;
	}

	void OrthographicCameraController::OnEvent(Event& e)
	{
		FJ_PROFILE_FUNCTION();

		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<MouseScrolledEvent>(FJ_BIND_EVENT_FN(OrthographicCameraController::OnMouseScrolled));
		dispatcher.Dispatch<WindowResizeEvent>(FJ_BIND_EVENT_FN(OrthographicCameraController::OnWindowResized));
	}

	void OrthographicCameraController::OnResize(float width, float height)
	{
		FJ_PROFILE_FUNCTION();

		m_AspectRatio = width / height;
		m_Bounds = { -m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, m_ZoomLevel, -m_ZoomLevel };
		m_Camera.SetProjection(m_Bounds.Left, m_Bounds.Right, m_Bounds.Bottom, m_Bounds.Top);
	}

	bool OrthographicCameraController::OnMouseScrolled(MouseScrolledEvent& e)
	{
		FJ_PROFILE_FUNCTION();

		m_ZoomLevel -= e.GetYOffset() * 0.25f;
		m_ZoomLevel = std::max(m_ZoomLevel, 0.25f);
		m_Bounds = { -m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, m_ZoomLevel, -m_ZoomLevel };
		m_Camera.SetProjection(m_Bounds.Left, m_Bounds.Right, m_Bounds.Bottom, m_Bounds.Top);
		return false;
	}

	bool OrthographicCameraController::OnWindowResized(WindowResizeEvent& e)
	{
		FJ_PROFILE_FUNCTION();

		OnResize((float)e.GetWidth(), (float)e.GetHeight());
		return false;
	}

}