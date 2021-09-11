#include "Sandbox2D.h"

#include "Platform/OpenGL/OpenGLShader.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <imgui/imgui.h>

#include <chrono>

template <typename Fn>
class Timer
{
public:
	Timer(const char* name, Fn&& fn)
		: m_Name(name), m_Func(fn), m_Stopped(false)
	{
		m_StartTimePoint = std::chrono::high_resolution_clock::now();
	}

	~Timer()
	{
		if (!m_Stopped)
			Stop();
	}

	void Stop()
	{
		auto endTimePoint = std::chrono::high_resolution_clock::now();

		long long start = std::chrono::time_point_cast<std::chrono::microseconds>(m_StartTimePoint).time_since_epoch().count();
		long long end = std::chrono::time_point_cast<std::chrono::microseconds>(endTimePoint).time_since_epoch().count();

		m_Stopped = true;

		float duration = (end - start) * 0.001f;
		m_Func({ m_Name, duration });
	}

private:
	const char* m_Name;
	bool m_Stopped;
	Fn m_Func;
	std::chrono::time_point<std::chrono::steady_clock> m_StartTimePoint;
};

#define PROFILE_SCOPE(name) Timer timer##__LINE__(name, [&](ProfileResult profileResult) { m_ProfileResult.push_back(profileResult); })

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
	PROFILE_SCOPE("Sandbox2D::OnUpdate");

	// Update
	{
		PROFILE_SCOPE("CameraController::OnUpdate");
		m_CameraController.OnUpdate(ts);
	}

	// Render
	{
		PROFILE_SCOPE("Renderer Prep");
		Fejioa::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
		Fejioa::RenderCommand::Clear();
	}

	{
		PROFILE_SCOPE("Renderer Draw");
		Fejioa::Renderer2D::BeginScene(m_CameraController.GetCamera());
		Fejioa::Renderer2D::DrawQuad({ -1.0f,  0.0f }, { 0.8f, 0.8f }, { 0.8f, 0.2f, 0.3f, 1.0f });
		Fejioa::Renderer2D::DrawQuad({ 0.5f, -0.5f }, { 0.5f, 0.75f }, { 0.2f, 0.3f, 0.8f, 1.0f });
		Fejioa::Renderer2D::DrawQuad({ 0.0f,  0.0f, -0.1f }, { 10.0f, 10.0f }, m_CheckerBoardTexture);
		Fejioa::Renderer2D::EndScene();
	}
}

void Sandbox2D::OnImGuiRender()
{
	ImGui::Begin("Settings");
	ImGui::ColorEdit3("Square Color", glm::value_ptr(m_SquareColor));

	for (auto& result : m_ProfileResult)
	{
		char label[50];
		strcpy(label, result.Name);
		strcat(label, "  %.3fms");
		ImGui::Text(label, result.Time);
	}
	m_ProfileResult.clear();

	ImGui::End();
}

void Sandbox2D::OnEvent(Fejioa::Event& e)
{
	m_CameraController.OnEvent(e);
}
