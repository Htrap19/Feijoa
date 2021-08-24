#include <Fejioa.h>

#include "imgui/imgui.h"

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

		std::shared_ptr<Fejioa::VertexBuffer> vertexBuffer;
		vertexBuffer.reset(Fejioa::VertexBuffer::Create(vertices, sizeof(vertices)));
		vertexBuffer->SetLayout({
			{ Fejioa::ShaderDataType::Float3, "a_Position" },
			{ Fejioa::ShaderDataType::Float4, "a_Color" },
			});
		m_VertexArray->AddVertexBuffer(vertexBuffer);

		unsigned int indices[] = { 0, 1, 2 };
		std::shared_ptr<Fejioa::IndexBuffer> indexBuffer;
		indexBuffer.reset(Fejioa::IndexBuffer::Create(indices, sizeof(indices) / sizeof(indices[0])));
		m_VertexArray->SetIndexBuffer(indexBuffer);

		m_SquareVA.reset(Fejioa::VertexArray::Create());
		float squarevertices[3 * 4] =
		{
			-0.75f, -0.75f, 0.0f,
			 0.75f, -0.75f, 0.0f,
			 0.75f,  0.75f, 0.0f,
			-0.75f,  0.75f, 0.0f,
		};

		std::shared_ptr<Fejioa::VertexBuffer> squareVB;
		squareVB.reset(Fejioa::VertexBuffer::Create(squarevertices, sizeof(squarevertices)));
		squareVB->SetLayout({
			{ Fejioa::ShaderDataType::Float3, "a_Position" }
			});
		m_SquareVA->AddVertexBuffer(squareVB);

		unsigned int squareIndices[] = { 0, 1, 2, 2, 3, 0 };
		std::shared_ptr<Fejioa::IndexBuffer> squereIB;
		squereIB.reset(Fejioa::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(squareIndices[0])));
		m_SquareVA->SetIndexBuffer(squereIB);

		std::string vertexSource = R"(
			#version 330 core

			layout (location = 0) in vec3 a_Position;
			layout (location = 1) in vec4 a_Color;

			uniform mat4 u_ViewProjection;

			out vec3 v_Position;
			out vec4 v_Color;

			void main()
			{
				gl_Position = u_ViewProjection * vec4(a_Position, 1.0);
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
		m_Shader.reset(new Fejioa::Shader(vertexSource, fragmentSource));

		std::string blueShaderVertexSource = R"(
			#version 330 core

			layout (location = 0) in vec3 a_Position;

			uniform mat4 u_ViewProjection;

			void main()
			{
				gl_Position = u_ViewProjection * vec4(a_Position, 1.0);
			}
		)";

		std::string blueShaderFragmentSource = R"(
			#version 330 core

			layout (location = 0) out vec4 color;
			
			void main()
			{
				color = vec4(0.2, 0.3, 0.8, 1.0);
			}
		)";

		m_BlueShader.reset(new Fejioa::Shader(blueShaderVertexSource, blueShaderFragmentSource));
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

		Fejioa::Renderer::Submit(m_BlueShader, m_SquareVA);
		Fejioa::Renderer::Submit(m_Shader, m_VertexArray);

		Fejioa::Renderer::EndScene();
	}

	virtual void OnImGuiRender() override
	{
	}

	virtual void OnEvent(Fejioa::Event& e) override
	{
	}

	private:
		std::shared_ptr<Fejioa::Shader> m_Shader;
		std::shared_ptr<Fejioa::VertexArray> m_VertexArray;

		std::shared_ptr<Fejioa::Shader> m_BlueShader;
		std::shared_ptr<Fejioa::VertexArray> m_SquareVA;

		Fejioa::OrthographicCamera m_Camera;
		glm::vec3 m_CameraPosition;
		float m_CameraMoveSpeed = 1.0f;

		float m_CameraRotation = 0.0f;
		float m_CameraRatationSpeed = 180.0f;
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