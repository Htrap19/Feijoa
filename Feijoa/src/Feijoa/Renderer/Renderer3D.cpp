#include "fjpch.h"
#include "Renderer3D.h"
#include "Feijoa/Renderer/VertexArray.h"
#include "Feijoa/Renderer/Shader.h"
#include "Feijoa/Renderer/RenderCommand.h"
#include "Feijoa/Scene/Components.h"

namespace Feijoa
{
	struct Renderer3DData
	{
		static const uint32_t MaxTextureSlots = 32;
		Ref<Texture2D> WhiteTexture;

		std::array<Ref<Texture2D>, MaxTextureSlots> TextureSlots;
		uint32_t TextureSlotIndex = 0; // 0 = White texture

		glm::vec4 CubePositions[8];

		// Model - Model loading using Assimp
		static const uint32_t ModelMaxVertices = 268435455; // Equals to UINT32_MAX/4
		static const uint32_t ModelMaxIndices = 268435455 / sizeof(uint32_t);

		Ref<VertexArray> ModelVertexArray;
		Ref<VertexBuffer> ModelVertexBuffer;
		Ref<IndexBuffer> ModelIndexBuffer;
		Ref<Shader> ModelShader;
		uint32_t ModelIndexOffset = 0;
		uint32_t ModelIndexCount = 0;

		std::vector<ModelVertex> ModelVertices;
		std::vector<uint32_t> ModelIndices;

		Renderer3D::Statistics Stats;
	};

	static Renderer3DData s_Data3D;

	void Renderer3D::Init()
	{
		FJ_PROFILE_FUNCTION();

		s_Data3D.WhiteTexture = Texture2D::Create(1, 1);
		uint32_t whiteTexture = 0xffffffff;
		s_Data3D.WhiteTexture->SetData(&whiteTexture, sizeof(uint32_t));

		int32_t samplers[s_Data3D.MaxTextureSlots];
		for (int32_t i = 0; i < s_Data3D.MaxTextureSlots; i++)
			samplers[i] = i;

		s_Data3D.TextureSlots[0] = s_Data3D.WhiteTexture;

		// Front
		s_Data3D.CubePositions[0] = { -0.5f, -0.5f,  0.5f, 1.0f };
		s_Data3D.CubePositions[1] = {  0.5f, -0.5f,  0.5f, 1.0f };
		s_Data3D.CubePositions[2] = {  0.5f,  0.5f,  0.5f, 1.0f };
		s_Data3D.CubePositions[3] = { -0.5f,  0.5f,  0.5f, 1.0f };

		// Back
		s_Data3D.CubePositions[4] = { -0.5f, -0.5f, -0.5f, 1.0f };
		s_Data3D.CubePositions[5] = {  0.5f, -0.5f, -0.5f, 1.0f };
		s_Data3D.CubePositions[6] = {  0.5f,  0.5f, -0.5f, 1.0f };
		s_Data3D.CubePositions[7] = { -0.5f,  0.5f, -0.5f, 1.0f };

		// Model init
		s_Data3D.ModelShader = Shader::Create("assets/shaders/Model3D.glsl");
		s_Data3D.ModelShader->Bind();
		s_Data3D.ModelShader->SetIntArray("u_Textures", samplers, s_Data3D.MaxTextureSlots);
		s_Data3D.ModelVertexArray = VertexArray::Create();
		s_Data3D.ModelVertexBuffer = VertexBuffer::Create(s_Data3D.ModelMaxVertices);
		s_Data3D.ModelVertexBuffer->SetLayout({
			{ ShaderDataType::Float3, "a_Position" },
			{ ShaderDataType::Mat4, "a_Model" },
			{ ShaderDataType::Float4, "a_Color" },
			{ ShaderDataType::Float2, "a_TexCoord" },
			{ ShaderDataType::Float, "a_TexIndex" }
			});
		s_Data3D.ModelIndexBuffer = IndexBuffer::Create(s_Data3D.ModelMaxIndices);

		s_Data3D.ModelVertexArray->AddVertexBuffer(s_Data3D.ModelVertexBuffer);
		s_Data3D.ModelVertexArray->SetIndexBuffer(s_Data3D.ModelIndexBuffer);
	}

	void Renderer3D::Shutdown()
	{
		FJ_PROFILE_FUNCTION();
	}

	void Renderer3D::ResetStats()
	{
		memset(&s_Data3D.Stats, 0, sizeof(Statistics));
	}

	Renderer3D::Statistics Renderer3D::GetStats()
	{
		return s_Data3D.Stats;
	}

	void Renderer3D::BeginScene(PerspectiveCamera& camera)
	{
		FJ_PROFILE_FUNCTION();
		s_Data3D.ModelShader->Bind();
		s_Data3D.ModelShader->SetMat4("u_Projection", camera.GetProjectionMatrix());
		s_Data3D.ModelShader->SetMat4("u_View", camera.GetViewMatrix());

		s_Data3D.TextureSlotIndex = 1;
		s_Data3D.ModelIndexOffset = 0;
		s_Data3D.ModelIndexCount = 0;

		s_Data3D.ModelVertices.clear();
		s_Data3D.ModelIndices.clear();
	}

	void Renderer3D::BeginScene(const Camera& camera, const glm::mat4& view)
	{
		FJ_PROFILE_FUNCTION();

		s_Data3D.ModelShader->Bind();
		s_Data3D.ModelShader->SetMat4("u_Projection", camera.GetProjection());
		s_Data3D.ModelShader->SetMat4("u_View", view);

		s_Data3D.TextureSlotIndex = 1;
		s_Data3D.ModelIndexOffset = 0;
		s_Data3D.ModelIndexCount = 0;

		s_Data3D.ModelVertices.clear();
		s_Data3D.ModelIndices.clear();
	}

	void Renderer3D::EndScene()
	{
		FJ_PROFILE_FUNCTION();

		s_Data3D.ModelVertexBuffer->SetData(s_Data3D.ModelVertices.data(), (uint32_t)s_Data3D.ModelVertices.size() * sizeof(ModelVertex));
		s_Data3D.ModelIndexBuffer->SetData(s_Data3D.ModelIndices.data(), (uint32_t)s_Data3D.ModelIndices.size());

		Flush();
	}

	void Renderer3D::Flush()
	{
		if (s_Data3D.ModelIndexCount == 0)
			return; // Nothing to draw

		for (uint32_t i = 0; i < s_Data3D.TextureSlotIndex; i++)
			s_Data3D.TextureSlots[i]->Bind(i);

		s_Data3D.ModelShader->Bind();
		RenderCommand::DrawIndexed(s_Data3D.ModelVertexArray, s_Data3D.ModelIndexCount);

		s_Data3D.Stats.DrawCalls++;
	}

	void Renderer3D::FlushAndReset()
	{
		EndScene();

		s_Data3D.TextureSlotIndex = 1;
		s_Data3D.ModelIndexOffset = 0;
		s_Data3D.ModelIndexCount = 0;

		s_Data3D.ModelVertices.clear();
		s_Data3D.ModelIndices.clear();
	}

	void Renderer3D::DrawMesh(const glm::mat4& model, const RenderMesh& mesh, const glm::vec4& color /* = glm::vec4(1.0f)*/)
	{
		FJ_PROFILE_FUNCTION();

		uint32_t numVertices = (uint32_t)mesh.Vertices.size();
		uint32_t numIndices = (uint32_t)mesh.Indices.size();

		if (s_Data3D.ModelIndexCount >= s_Data3D.ModelMaxIndices ||
			(s_Data3D.ModelIndexOffset * sizeof(ModelVertex)) >= s_Data3D.ModelMaxVertices)
			FlushAndReset();

		float textureIndex = 0.0f; // White texture
		for (uint32_t i = 0; i < s_Data3D.TextureSlotIndex; i++)
		{
			for (auto& texture : mesh.Textures)
			{
				if (*s_Data3D.TextureSlots[i] == *texture)
				{
					textureIndex = (float)i;
					break;
				}
			}
		}

		if (textureIndex == 0.0f && mesh.HasTexture())
		{
			textureIndex = (float)s_Data3D.TextureSlotIndex;
			s_Data3D.TextureSlots[s_Data3D.TextureSlotIndex] = mesh.Textures[0];
			s_Data3D.TextureSlotIndex++;
		}

		auto tempMesh = mesh;
		for (auto& vertex : tempMesh.Vertices)
			vertex.Model = model, vertex.TexIndex = textureIndex, vertex.Color = color == glm::vec4(1.0f) ? vertex.Color : color;

		for (auto& index : tempMesh.Indices)
			index = s_Data3D.ModelIndexOffset + index;

		s_Data3D.ModelVertices.insert(s_Data3D.ModelVertices.end(), tempMesh.Vertices.begin(), tempMesh.Vertices.end());
		s_Data3D.ModelIndices.insert(s_Data3D.ModelIndices.end(), tempMesh.Indices.begin(), tempMesh.Indices.end());

		s_Data3D.ModelIndexOffset += numVertices;
		s_Data3D.ModelIndexCount += numIndices;

		s_Data3D.Stats.MeshCount++;
		s_Data3D.Stats.ModelTotalVertexCount += numVertices;
		s_Data3D.Stats.ModelTotalIndexCount += numIndices;
	}

	void Renderer3D::DrawMesh(const glm::vec3& position, const glm::vec3& size, const RenderMesh& mesh)
	{
		glm::mat4 model = glm::translate(glm::mat4(1.0f), position)
			* glm::scale(glm::mat4(1.0f), size);

		DrawMesh(model, mesh);
	}

}