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

	// Render
	{
		FJ_PROFILE_SCOPE("Renderer Prep");
		Feijoa::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
		Feijoa::RenderCommand::Clear();
	}

	Feijoa::Renderer2D::ResetStats();
	{
		static float rotation = 0.0f;
		rotation += ts * 50.0f;

		FJ_PROFILE_SCOPE("Renderer Draw");
		Feijoa::Renderer2D::BeginScene(m_CameraController.GetCamera());
		Feijoa::Renderer2D::DrawRotatedQuad({ 1.0f,  0.0f }, { 0.8f, 0.8f }, -45.0f, { 0.8f, 0.2f, 0.3f, 1.0f });
		Feijoa::Renderer2D::DrawQuad({ -1.0f,  0.0f }, { 0.8f, 0.8f }, { 0.8f, 0.2f, 0.3f, 1.0f });
		Feijoa::Renderer2D::DrawQuad({  0.5f, -0.5f }, { 0.5f, 0.75f }, { 0.2f, 0.3f, 0.8f, 1.0f });
		Feijoa::Renderer2D::DrawQuad({ 0.0f,  0.0f, -0.1f }, { 20.0f, 20.0f }, m_CheckerBoardTexture, 10.0f);
		Feijoa::Renderer2D::DrawRotatedQuad({ -2.0f,  0.0f, -0.0f }, { 1.0f, 1.0f }, rotation, m_CheckerBoardTexture, 20.0f);
		Feijoa::Renderer2D::EndScene();

		Feijoa::Renderer2D::BeginScene(m_CameraController.GetCamera());
		for (float y = -5.0f; y < 5.0f; y += 0.5f)
		{
			for (float x = -5.0f; x < 5.0f; x += 0.5f)
			{
				glm::vec4 color = { (x + 5.0f) / 10.0f, 0.4f, (y + 5.0f) / 10.0f, 0.7f };

				Feijoa::Renderer2D::DrawQuad({ x, y }, { 0.45f, 0.45f }, color);
			}
		}
		Feijoa::Renderer2D::EndScene();
	}
}

void Sandbox2D::OnImGuiRender()
{
	FJ_PROFILE_FUNCTION();

	ImGui::Begin("Settings");

	auto stats = Feijoa::Renderer2D::GetStats();
	ImGui::Text("Renderer2D Stats:");
	ImGui::Text("Draw calls: %d", stats.DrawCalls);
	ImGui::Text("Quad: %d", stats.QuadCount);
	ImGui::Text("Vertices: %d", stats.GetTotalVertexCount());
	ImGui::Text("Indices: %d", stats.GetTotalIndexCount());

	ImGui::ColorEdit4("Square Color", glm::value_ptr(m_SquareColor));

	ImGui::End();
}

void Sandbox2D::OnEvent(Feijoa::Event& e)
{
	m_CameraController.OnEvent(e);
}
