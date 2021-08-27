#include <Fejioa.h>

#include "Platform/OpenGL/OpenGLShader.h"

#include "imgui/imgui.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class ExampleLayer : public Fejioa::Layer
{
public:
	ExampleLayer()
		: Layer("Example"), m_Camera(-1.6f, 1.6f, -0.9f, 0.9f),
		m_CameraPosition(0.0f)
	{
		m_VertexArray.reset(Fejioa::VertexArray::Create());

		float vertices[3 * 7] = {
			-0.5f, -0.5f, 0.0f,		0.8f, 0.2f, 0.8f, 1.0f,
			 0.5f, -0.5f, 0.0f,		0.2f, 0.3f, 0.8f, 1.0f,
			 0.0f,  0.5f, 0.0f,		0.8f, 0.8f, 0.2f, 1.0f
		};

		Fejioa::Ref<Fejioa::VertexBuffer> vertexBuffer;
		vertexBuffer.reset(Fejioa::VertexBuffer::Create(vertices, sizeof(vertices)));
		vertexBuffer->SetLayout({
			{ Fejioa::ShaderDataType::Float3, "a_Position" },
			{ Fejioa::ShaderDataType::Float4, "a_Color" },
			});
		m_VertexArray->AddVertexBuffer(vertexBuffer);

		unsigned int indices[] = { 0, 1, 2 };
		Fejioa::Ref<Fejioa::IndexBuffer> indexBuffer;
		indexBuffer.reset(Fejioa::IndexBuffer::Create(indices, sizeof(indices) / sizeof(indices[0])));
		m_VertexArray->SetIndexBuffer(indexBuffer);

		m_SquareVA.reset(Fejioa::VertexArray::Create());
		float squarevertices[5 * 4] =
		{
			-0.5f, -0.5f, 0.0f,		0.0f, 0.0f,
			 0.5f, -0.5f, 0.0f,		1.0f, 0.0f,
			 0.5f,  0.5f, 0.0f,		1.0f, 1.0f,
			-0.5f,  0.5f, 0.0f,		0.0f, 1.0f
		};

		Fejioa::Ref<Fejioa::VertexBuffer> squareVB;
		squareVB.reset(Fejioa::VertexBuffer::Create(squarevertices, sizeof(squarevertices)));
		squareVB->SetLayout({
			{ Fejioa::ShaderDataType::Float3, "a_Position" },
			{ Fejioa::ShaderDataType::Float2, "a_TexCoord" }
			});
		m_SquareVA->AddVertexBuffer(squareVB);

		unsigned int squareIndices[] = { 0, 1, 2, 2, 3, 0 };
		Fejioa::Ref<Fejioa::IndexBuffer> squereIB;
		squereIB.reset(Fejioa::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(squareIndices[0])));
		m_SquareVA->SetIndexBuffer(squereIB);

		std::string vertexSource = R"(
			#version 330 core

			layout (location = 0) in vec3 a_Position;
			layout (location = 1) in vec4 a_Color;

			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;

			out vec3 v_Position;
			out vec4 v_Color;

			void main()
			{
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
				v_Position = a_Position;
				v_Color = a_Color;
			}
		)";

		std::string fragmentSource = R"(
			#version 330 core

			layout (location = 0) out vec4 color;
			
			in vec3 v_Position;
			in vec4 v_Color;

			void main()
			{
				color = vec4(v_Position * 0.5 + 0.5, 1.0);
				color = v_Color;
			}
		)";
		m_Shader.reset(Fejioa::Shader::Create(vertexSource, fragmentSource));

		std::string flatColorShaderVertexSrc = R"(
			#version 330 core

			layout (location = 0) in vec3 a_Position;

			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;

			void main()
			{
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
			}
		)";

		std::string flatColorShaderFragmentSrc = R"(
			#version 330 core

			layout (location = 0) out vec4 color;

			uniform vec3 u_Color;
			
			void main()
			{
				color = vec4(u_Color, 1.0);
			}
		)";

		m_FlatColorShader.reset(Fejioa::Shader::Create(flatColorShaderVertexSrc, flatColorShaderFragmentSrc));

		m_TextureShader.reset(Fejioa::Shader::Create("assets/shaders/Texture.glsl"));

		m_Texture = Fejioa::Texture2D::Create("assets/textures/Checkerboard.png");
		m_FejioaLogoTexture = Fejioa::Texture2D::Create("assets/textures/FejioaLogo.png");

		std::dynamic_pointer_cast<Fejioa::OpenGLShader>(m_TextureShader)->Bind();
		std::dynamic_pointer_cast<Fejioa::OpenGLShader>(m_TextureShader)->UploadUniformInt("u_Texture", 0);
	}

	virtual void OnUpdate(Fejioa::Timestep ts) override
	{
		if (Fejioa::Input::IsKeyPressed(FJ_KEY_LEFT))
			m_CameraPosition.x -= m_CameraMoveSpeed * ts;
		if (Fejioa::Input::IsKeyPressed(FJ_KEY_RIGHT))
			m_CameraPosition.x += m_CameraMoveSpeed * ts;

		if (Fejioa::Input::IsKeyPressed(FJ_KEY_UP))
			m_CameraPosition.y += m_CameraMoveSpeed * ts;
		if (Fejioa::Input::IsKeyPressed(FJ_KEY_DOWN))
			m_CameraPosition.y -= m_CameraMoveSpeed * ts;

		if (Fejioa::Input::IsKeyPressed(FJ_KEY_A))
			m_CameraRotation += m_CameraRatationSpeed * ts;
		if (Fejioa::Input::IsKeyPressed(FJ_KEY_D))
			m_CameraRotation -= m_CameraRatationSpeed * ts;

		Fejioa::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
		Fejioa::RenderCommand::Clear();

		m_Camera.SetPosition(m_CameraPosition);
		m_Camera.SetRotation(m_CameraRotation);

		Fejioa::Renderer::BeginScene(m_Camera);

		glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));

		std::dynamic_pointer_cast<Fejioa::OpenGLShader>(m_FlatColorShader)->Bind();
		std::dynamic_pointer_cast<Fejioa::OpenGLShader>(m_FlatColorShader)->UploadUniformFloat3("u_Color", m_SquareColor);

		for (int y = 0; y < 20; y++)
		{
			for (int x = 0; x < 20; x++)
			{
				glm::vec3 pos(x * 0.11f, y * 0.11f, 0.0f);
				glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * scale;
				Fejioa::Renderer::Submit(m_FlatColorShader, m_SquareVA, transform);
			}
		}

		m_Texture->Bind();
		Fejioa::Renderer::Submit(m_TextureShader, m_SquareVA, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));

		m_FejioaLogoTexture->Bind();
		Fejioa::Renderer::Submit(m_TextureShader, m_SquareVA, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));

		Fejioa::Renderer::EndScene();
	}

	virtual void OnImGuiRender() override
	{
		ImGui::Begin("Settings");
		ImGui::ColorEdit3("Square Color", glm::value_ptr(m_SquareColor));
		ImGui::End();
	}

	virtual void OnEvent(Fejioa::Event& e) override
	{
	}

	private:
		Fejioa::Ref<Fejioa::Shader> m_Shader;
		Fejioa::Ref<Fejioa::VertexArray> m_VertexArray;

		Fejioa::Ref<Fejioa::Shader> m_FlatColorShader, m_TextureShader;
		Fejioa::Ref<Fejioa::VertexArray> m_SquareVA;

		Fejioa::Ref<Fejioa::Texture2D> m_Texture, m_FejioaLogoTexture;

		Fejioa::OrthographicCamera m_Camera;
		glm::vec3 m_CameraPosition;
		float m_CameraMoveSpeed = 1.0f;

		float m_CameraRotation = 0.0f;
		float m_CameraRatationSpeed = 180.0f;

		glm::vec3 m_SquareColor = { 0.2f, 0.3f, 0.8f };
};

class SandboxApp : public Fejioa::Application
{
public:
	SandboxApp()
	{
		PushLayer(new ExampleLayer());
	}

	~SandboxApp()
	{
	}
};

Fejioa::Application* Fejioa::CreateApplication()
{
	return new SandboxApp();
}