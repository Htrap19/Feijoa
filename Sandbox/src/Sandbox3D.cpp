#include "Sandbox3D.h"

#include <imgui/imgui.h>
#include <glm/gtc/type_ptr.hpp>

Sandbox3D::Sandbox3D()
	: Layer("Sandbox3D"), m_CameraController({ 0.0f, 0.0f, 0.0f }, 1280.0f / 720.0f)
{
}

void Sandbox3D::OnAttach()
{
	m_CheckerboardTexture = Feijoa::Texture2D::Create("assets/textures/Checkerboard.png");
}

void Sandbox3D::OnDetach()
{
}

void Sandbox3D::OnUpdate(Feijoa::Timestep ts)
{
	m_CameraController.OnUpdate(ts);

	Feijoa::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
	Feijoa::RenderCommand::Clear();

	Feijoa::Renderer3D::ResetStats();
	Feijoa::Renderer3D::BeginScene(m_CameraController.GetCamera());
	Feijoa::Renderer3D::DrawQuad(glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(1.0f), glm::vec4(0.8f, 0.2f, 0.3f, 1.0f));
	Feijoa::Renderer3D::DrawQuad(glm::vec3(3.0f, 1.0f, 3.0f), glm::vec3(1.0f), m_CheckerboardTexture);
	Feijoa::Renderer3D::DrawRotatedQuad(glm::vec3(5.0f), glm::vec3(0.5f), 45.0f, glm::vec3(1.0f), m_SquareColor);
	Feijoa::Renderer3D::EndScene();
}

void Sandbox3D::OnEvent(Feijoa::Event& e)
{
	m_CameraController.OnEvent(e);
}

void Sandbox3D::OnImGuiRender()
{
	auto& camera = m_CameraController.GetCamera();
	ImGui::Begin("Camera control");
	ImGui::DragFloat("FOV", &m_FOV, 1.0f, camera.GetMinFOV(), camera.GetMaxFOV());
	ImGui::ColorEdit4("Square Color", glm::value_ptr(m_SquareColor));
	auto stats = Feijoa::Renderer3D::GetStats();
	ImGui::Text("Renderer 3D Stats:");
	ImGui::Text("Draw calls: %d", stats.DrawCalls);
	ImGui::Text("Quad count: %d", stats.QuadCount);
	ImGui::Text("Vertices: %d", stats.GetTotalVertexCount());
	ImGui::Text("Indices: %d", stats.GetTotalIndexCount());
	ImGui::End();
	camera.SetFOV(m_FOV);
}
