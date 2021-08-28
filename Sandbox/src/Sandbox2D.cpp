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
	m_SquareVA = Fejioa::VertexArray::Create();

	float squarevertices[5 * 4] =
	{
		-0.5f, -0.5f, 0.0f,		0.0f, 0.0f,
		 0.5f, -0.5f, 0.0f,		1.0f, 0.0f,
		 0.5f,  0.5f, 0.0f,		1.0f, 1.0f,
		-0.5f,  0.5f, 0.0f,		0.0f, 1.0f
	};

	Fejioa::Ref<Fejioa::VertexBuffer> squareVB;
	squareVB = Fejioa::VertexBuffer::Create(squarevertices, sizeof(squarevertices));
	squareVB->SetLayout({
		{ Fejioa::ShaderDataType::Float3, "a_Position" },
		{ Fejioa::ShaderDataType::Float2, "a_TexCoord" }
		});
	m_SquareVA->AddVertexBuffer(squareVB);

	unsigned int squareIndices[] = { 0, 1, 2, 2, 3, 0 };
	Fejioa::Ref<Fejioa::IndexBuffer> squereIB;
	squereIB = Fejioa::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(squareIndices[0]));
	m_SquareVA->SetIndexBuffer(squereIB);

	m_FlatColorShader = Fejioa::Shader::Create("assets/shaders/FlatColor.glsl");
}

void Sandbox2D::OnDetach()
{
}

void Sandbox2D::OnUpdate(Fejioa::Timestep ts)
{
	// Update
	m_CameraController.OnUpdate(ts);

	// Render
	Fejioa::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
	Fejioa::RenderCommand::Clear();

	Fejioa::Renderer::BeginScene(m_CameraController.GetCamera());

	std::dynamic_pointer_cast<Fejioa::OpenGLShader>(m_FlatColorShader)->Bind();
	std::dynamic_pointer_cast<Fejioa::OpenGLShader>(m_FlatColorShader)->UploadUniformFloat3("u_Color", m_SquareColor);

	Fejioa::Renderer::Submit(m_FlatColorShader, m_SquareVA, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));

	Fejioa::Renderer::EndScene();
}

void Sandbox2D::OnImGuiRender()
{
	ImGui::Begin("Settings");
	ImGui::ColorEdit3("Square Color", glm::value_ptr(m_SquareColor));
	ImGui::End();
}

void Sandbox2D::OnEvent(Fejioa::Event& e)
{
	m_CameraController.OnEvent(e);
}
