#include "Sandbox3D.h"

#include <imgui/imgui.h>
#include <glm/gtc/type_ptr.hpp>

Sandbox3D::Sandbox3D()
	: Layer("Sandbox3D"), m_CameraController({ 0.0f, 0.0f, 0.0f }, 1280.0f / 720.0f)
{
}

void Sandbox3D::OnAttach()
{
	FJ_PROFILE_FUNCTION();

	m_CheckerboardTexture = Feijoa::Texture2D::Create("assets/textures/Checkerboard.png");

	m_ActiveScene = Feijoa::CreateRef<Feijoa::Scene>();
	m_Camera = m_ActiveScene->CreateEntity("Perspective Camera");
	m_Camera.AddComponent<Feijoa::PerspectiveCameraComponent>(glm::vec3(0.0f, 0.0f, 0.0f), 1280.0f/720.0f);

	class CameraController : public Feijoa::ScriptableEntity
	{
	public:
		void OnCreate()
		{
		}

		void OnDestroy()
		{
		}

		void OnUpdate(Feijoa::Timestep ts)
		{
			auto& camera = GetComponent<Feijoa::PerspectiveCameraComponent>().Camera;

			if (Feijoa::Input::IsKeyPressed(Feijoa::Key::W))
				camera.UpdateDirection(Feijoa::PerspectiveSceneCamera::Direction::Forward, ts);
			if (Feijoa::Input::IsKeyPressed(Feijoa::Key::S))
				camera.UpdateDirection(Feijoa::PerspectiveSceneCamera::Direction::Backward, ts);
			if (Feijoa::Input::IsKeyPressed(Feijoa::Key::A))
				camera.UpdateDirection(Feijoa::PerspectiveSceneCamera::Direction::Left, ts);
			if (Feijoa::Input::IsKeyPressed(Feijoa::Key::D))
				camera.UpdateDirection(Feijoa::PerspectiveSceneCamera::Direction::Right, ts);
			if (Feijoa::Input::IsKeyPressed(Feijoa::Key::Space))
				camera.UpdateDirection(Feijoa::PerspectiveSceneCamera::Direction::Top, ts);
			if (Feijoa::Input::IsKeyPressed(Feijoa::Key::LeftShift))
				camera.UpdateDirection(Feijoa::PerspectiveSceneCamera::Direction::Bottom, ts);

			auto cursor = Feijoa::Input::GetMousePosition();
			float dx = cursor.x - m_LastX;
			float dy = m_LastY - cursor.y; // Because y is inverted
			m_LastX = cursor.x;
			m_LastY = cursor.y;
			camera.UpdatePosition(dx, dy);
		}

	private:
		float m_LastX = 0, m_LastY = 0;
	};
	m_Camera.AddComponent<Feijoa::NativeScriptComponent>().Bind<CameraController>();

	m_SphereModel = m_ActiveScene->CreateEntity("Sphere Model");
	m_SphereModel.AddComponent<Feijoa::ModelComponent>(&m_SphereModel, "assets/models/stylized_treasure_chest/scene.gltf", glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.025f));
}

void Sandbox3D::OnDetach()
{
	FJ_PROFILE_FUNCTION();
}

void Sandbox3D::OnUpdate(Feijoa::Timestep ts)
{
	FJ_PROFILE_FUNCTION();

	m_CameraController.OnUpdate(ts);

	Feijoa::RenderCommand::SetClearColor({ 0.2f, 0.2f, 0.3f, 1.0f });
	Feijoa::RenderCommand::Clear();
	Feijoa::Renderer3D::ResetStats();

	m_ActiveScene->OnUpdate(ts);
}

void Sandbox3D::OnEvent(Feijoa::Event& e)
{
	m_CameraController.OnEvent(e);

	Feijoa::EventDispatcher dispatcher(e);
	dispatcher.Dispatch<Feijoa::WindowResizeEvent>(FJ_BIND_EVENT_FN(Sandbox3D::OnWindowResize));
}

void Sandbox3D::OnImGuiRender()
{
	FJ_PROFILE_FUNCTION();

	auto& camera = m_Camera.GetComponent<Feijoa::PerspectiveCameraComponent>().Camera;
	ImGui::Begin("Camera control");
	auto stats = Feijoa::Renderer3D::GetStats();
	ImGui::Text("Renderer 3D Stats:");
	ImGui::Text("Draw calls: %d", stats.DrawCalls);
	ImGui::Text("Mesh count: %d", stats.MeshCount);
	ImGui::Text("Vertices: %d", stats.ModelTotalVertexCount);
	ImGui::Text("Indices: %d", stats.ModelTotalIndexCount);
	ImGui::ColorEdit4("Square Color", glm::value_ptr(m_SquareColor));

	ImGui::DragFloat("FOV", &m_FOV, 1.0f);
	ImGui::DragFloat("Speed", &m_Speed, 1.0f);
	auto io = ImGui::GetIO();
	ImGui::Text("%.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
	ImGui::End();
	camera.SetFOV(m_FOV);
	camera.SetSpeed(m_Speed);
}

bool Sandbox3D::OnWindowResize(Feijoa::WindowResizeEvent& e)
{
	m_ActiveScene->OnViewportResize(e.GetWidth(), e.GetHeight());

	return false;
}
