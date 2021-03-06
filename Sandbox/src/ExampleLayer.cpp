#include "ExampleLayer.h"

ExampleLayer::ExampleLayer()
	: Layer("Example"), m_CameraController(1280.0f / 720.0f)
{
	m_VertexArray = Feijoa::VertexArray::Create();

	float vertices[3 * 7] = {
		-0.5f, -0.5f, 0.0f,		0.8f, 0.2f, 0.8f, 1.0f,
		 0.5f, -0.5f, 0.0f,		0.2f, 0.3f, 0.8f, 1.0f,
		 0.0f,  0.5f, 0.0f,		0.8f, 0.8f, 0.2f, 1.0f
	};

	Feijoa::Ref<Feijoa::VertexBuffer> vertexBuffer;
	vertexBuffer = Feijoa::VertexBuffer::Create(vertices, sizeof(vertices));
	vertexBuffer->SetLayout({
		{ Feijoa::ShaderDataType::Float3, "a_Position" },
		{ Feijoa::ShaderDataType::Float4, "a_Color" },
		});
	m_VertexArray->AddVertexBuffer(vertexBuffer);

	uint32_t indices[] = { 0, 1, 2 };
	Feijoa::Ref<Feijoa::IndexBuffer> indexBuffer;
	indexBuffer = Feijoa::IndexBuffer::Create(indices, sizeof(indices) / sizeof(indices[0]));
	m_VertexArray->SetIndexBuffer(indexBuffer);

	m_SquareVA = Feijoa::VertexArray::Create();
	float squarevertices[5 * 4] =
	{
		-0.5f, -0.5f, 0.0f,		0.0f, 0.0f,
		 0.5f, -0.5f, 0.0f,		1.0f, 0.0f,
		 0.5f,  0.5f, 0.0f,		1.0f, 1.0f,
		-0.5f,  0.5f, 0.0f,		0.0f, 1.0f
	};

	Feijoa::Ref<Feijoa::VertexBuffer> squareVB;
	squareVB = Feijoa::VertexBuffer::Create(squarevertices, sizeof(squarevertices));
	squareVB->SetLayout({
		{ Feijoa::ShaderDataType::Float3, "a_Position" },
		{ Feijoa::ShaderDataType::Float2, "a_TexCoord" }
		});
	m_SquareVA->AddVertexBuffer(squareVB);

	uint32_t squareIndices[] = { 0, 1, 2, 2, 3, 0 };
	Feijoa::Ref<Feijoa::IndexBuffer> squereIB;
	squereIB = Feijoa::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(squareIndices[0]));
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
	m_Shader = Feijoa::Shader::Create("VertexPosColor", vertexSource, fragmentSource);

	m_FlatColorShader = Feijoa::Shader::Create("assets/shaders/FlatColor.glsl");

	auto textureShader = m_ShaderLibrary.Load("assets/shaders/Texture.glsl");

	m_Texture = Feijoa::Texture2D::Create("assets/textures/Checkerboard.png");
	m_FejioaLogoTexture = Feijoa::Texture2D::Create("assets/textures/FejioaLogo.png");

	std::dynamic_pointer_cast<Feijoa::OpenGLShader>(textureShader)->Bind();
	std::dynamic_pointer_cast<Feijoa::OpenGLShader>(textureShader)->UploadUniformInt("u_Texture", 0);
}

void ExampleLayer::OnUpdate(Feijoa::Timestep ts)
{
	m_CameraController.OnUpdate(ts);

	Feijoa::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
	Feijoa::RenderCommand::Clear();

	Feijoa::Renderer::BeginScene(m_CameraController.GetCamera());

	glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));

	std::dynamic_pointer_cast<Feijoa::OpenGLShader>(m_FlatColorShader)->Bind();
	std::dynamic_pointer_cast<Feijoa::OpenGLShader>(m_FlatColorShader)->UploadUniformFloat3("u_Color", m_SquareColor);

	for (int y = 0; y < 20; y++)
	{
		for (int x = 0; x < 20; x++)
		{
			glm::vec3 pos(x * 0.11f, y * 0.11f, 0.0f);
			glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * scale;
			Feijoa::Renderer::Submit(m_FlatColorShader, m_SquareVA, transform);
		}
	}

	auto textureShader = m_ShaderLibrary.Get("Texture");

	m_Texture->Bind();
	Feijoa::Renderer::Submit(textureShader, m_SquareVA, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));

	m_FejioaLogoTexture->Bind();
	Feijoa::Renderer::Submit(textureShader, m_SquareVA, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));

	Feijoa::Renderer::EndScene();
}

void ExampleLayer::OnImGuiRender()
{
	ImGui::Begin("Settings");
	ImGui::ColorEdit3("Square Color", glm::value_ptr(m_SquareColor));
	ImGui::End();
}

void ExampleLayer::OnEvent(Feijoa::Event& e)
{
	m_CameraController.OnEvent(e);
}

