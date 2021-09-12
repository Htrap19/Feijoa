#include "Sandbox2D.h"

#include "Platform/OpenGL/OpenGLShader.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <imgui/imgui.h>

Sandbox2D::Sandbox2D()
	: Layer("Sandbox2D"), m_CameraController(1280.0f / 720.0f)
{
}

void Sandbox2D::OnAttach()
{
	m_CheckerBoardTexture = Fejioa::Texture2D::Create("assets/textures/Checkerboard.png");
}

void Sandbox2D::OnDetach()
{
}

void Sandbox2D::OnUpdate(Fejioa::Timestep ts)
{
	FJ_PROFILE_FUNCTION();

	// Update
	{
		FJ_PROFILE_SCOPE("CameraController::OnUpdate");
		m_CameraController.OnUpdate(ts);
	}

	// Render
	{
		FJ_PROFILE_SCOPE("Renderer Prep");
		Fejioa::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
		Fejioa::RenderCommand::Clear();
	}

	{
		FJ_PROFILE_SCOPE("Renderer Draw");
		Fejioa::Renderer2D::BeginScene(m_CameraController.GetCamera());
		Fejioa::Renderer2D::DrawQuad({ -1.0f,  0.0f }, { 0.8f, 0.8f }, { 0.8f, 0.2f, 0.3f, 1.0f });
		Fejioa::Renderer2D::DrawQuad({ 0.5f, -0.5f }, { 0.5f, 0.75f }, { 0.2f, 0.3f, 0.8f, 1.0f });
		Fejioa::Renderer2D::DrawQuad({ 0.0f,  0.0f, -0.1f }, { 10.0f, 10.0f }, m_CheckerBoardTexture);
		Fejioa::Renderer2D::EndScene();
	}
}

void Sandbox2D::OnImGuiRender()
{
	FJ_PROFILE_FUNCTION();

	ImGui::Begin("Settings");
	ImGui::ColorEdit3("Square Color", glm::value_ptr(m_SquareColor));

	ImGui::End();
}

void Sandbox2D::OnEvent(Fejioa::Event& e)
{
	m_CameraController.OnEvent(e);
}
