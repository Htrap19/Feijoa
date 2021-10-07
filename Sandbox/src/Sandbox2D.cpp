#include "Sandbox2D.h"

#include "Platform/OpenGL/OpenGLShader.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <imgui/imgui.h>

Sandbox2D::Sandbox2D()
	: Layer("Sandbox2D"), m_CameraController(1280.0f / 720.0f),
	m_ParticleSystem(10000)
{
	m_ParticleProps.Position = { 0.0f, 0.0f };
	m_ParticleProps.Velocity = { -2.0f, 0.0f }, m_ParticleProps.VelocityVariation = { 3.0f, 1.0f };
	m_ParticleProps.SizeBegin = 0.5f, m_ParticleProps.SizeEnd = 0.0f, m_ParticleProps.SizeVariation = 0.3f;
	m_ParticleProps.ColorBegin = m_SquareColor;
	m_ParticleProps.ColorEnd = { 254 / 255.0f, 212 / 255.0f, 123 / 255.0f, 1.0f };
	m_ParticleProps.LifeTime = 1.0f;
}

void Sandbox2D::OnAttach()
{
	FJ_PROFILE_FUNCTION();

	m_CheckerBoardTexture = Feijoa::Texture2D::Create("assets/textures/Checkerboard.png");
}

void Sandbox2D::OnDetach()
{
	FJ_PROFILE_FUNCTION();
}

void Sandbox2D::OnUpdate(Feijoa::Timestep ts)
{
	FJ_PROFILE_FUNCTION();

	// Update
	m_CameraController.OnUpdate(ts);
	m_ParticleSystem.OnUpdate(ts);

	// Render
	{
		FJ_PROFILE_SCOPE("Renderer Prep");
		Feijoa::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
		Feijoa::RenderCommand::Clear();
	}

	{
		FJ_PROFILE_SCOPE("Renderer Draw");
		Feijoa::Renderer2D::BeginScene(m_CameraController.GetCamera());
		m_ParticleSystem.OnRender();
		Feijoa::Renderer2D::DrawRotatedQuad({ -1.0f,  0.0f }, { 0.8f, 0.8f }, glm::radians(-45.0f), { 0.8f, 0.2f, 0.3f, 1.0f });
		Feijoa::Renderer2D::DrawQuad({ 0.5f, -0.5f }, { 0.5f, 0.75f }, { 0.2f, 0.3f, 0.8f, 1.0f });
		Feijoa::Renderer2D::DrawQuad({ 0.0f,  0.0f, -0.1f }, { 10.0f, 10.0f }, m_CheckerBoardTexture);
		Feijoa::Renderer2D::EndScene();
	}

	if (Feijoa::Input::IsMouseButtonPressed(Feijoa::Mouse::ButtonLeft))
	{
		auto cursor = Feijoa::Input::GetMousePosition();
		float x = cursor.x, y = cursor.y;
		auto width = Feijoa::Application::Get().GetWindow().GetWidth();
		auto height = Feijoa::Application::Get().GetWindow().GetHeight();

		auto bounds = m_CameraController.GetBounds();
		auto pos = m_CameraController.GetCamera().GetPosition();
		x = (x / width) * bounds.GetWidth() - bounds.GetWidth() * 0.5f;
		y = bounds.GetHeight() * 0.5f - (y / height) * bounds.GetHeight();
		m_ParticleProps.Position = { x + pos.x, y + pos.y };
		m_ParticleProps.ColorBegin = m_SquareColor;
		for (uint8_t i = 0; i < 5; i++)
			m_ParticleSystem.Emit(m_ParticleProps);
	}
}

void Sandbox2D::OnImGuiRender()
{
	FJ_PROFILE_FUNCTION();

	ImGui::Begin("Settings");
	ImGui::ColorEdit3("Square Color", glm::value_ptr(m_SquareColor));
	ImGui::End();
}

void Sandbox2D::OnEvent(Feijoa::Event& e)
{
	m_CameraController.OnEvent(e);
}
