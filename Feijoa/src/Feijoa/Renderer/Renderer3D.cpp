#include "fjpch.h"
#include "Renderer3D.h"

#include "Feijoa/Renderer/VertexArray.h"
#include "Feijoa/Renderer/Shader.h"
#include "Feijoa/Renderer/RenderCommand.h"

namespace Feijoa
{
	struct CubeVertex
	{
		glm::vec3 Position;
		glm::vec4 Color;
		glm::vec2 TexCoord;
		float TexIndex;
		float TilingFactor;
	};

	struct Renderer3DData
	{
		static const uint32_t MaxCube = 200;
		static const uint32_t MaxVertices = MaxCube * 8;
		static const uint32_t MaxIndices = MaxCube * 36;
		static const uint32_t MaxTextureSlots = 32;

		Ref<VertexArray> CubeVertexArray;
		Ref<VertexBuffer> CubeVertexBuffer;
		Ref<Texture2D> WhiteTexture;
		Ref<Shader> Renderer3DShader;

		uint32_t CubeIndexCount = 0;
		CubeVertex* CubeVertexBufferBase = nullptr;
		CubeVertex* CubeVertexBufferPtr = nullptr;

		std::array<Ref<Texture2D>, MaxTextureSlots> TextureSlots;
		uint32_t TextureSlotIndex = 0; // 0 = White texture

		glm::vec4 CubePositions[8];

		Renderer3D::Statistics Stats;
	};

	static Renderer3DData s_Data3D;

	void Renderer3D::Init()
	{
		s_Data3D.CubeVertexArray = VertexArray::Create();

		s_Data3D.CubeVertexBuffer = VertexBuffer::Create(sizeof(CubeVertex) * Renderer3DData::MaxCube);
		s_Data3D.CubeVertexBuffer->SetLayout({
			{ ShaderDataType::Float3, "a_Position" },
			{ ShaderDataType::Float4, "a_Color" },
			{ ShaderDataType::Float2, "a_TexCoord" },
			{ ShaderDataType::Float, "a_TexIndex" },
			{ ShaderDataType::Float, "a_TilingFactor" }
			});
		s_Data3D.CubeVertexArray->AddVertexBuffer(s_Data3D.CubeVertexBuffer);

		s_Data3D.CubeVertexBufferBase = new CubeVertex[s_Data3D.MaxVertices];

		uint32_t* cubeIndices = new uint32_t[s_Data3D.MaxIndices];
		
		uint32_t offset = 0;
		for (uint32_t i = 0; i < s_Data3D.MaxIndices; i += 36)
		{
			// Front
			cubeIndices[i + 0] = offset + 0;
			cubeIndices[i + 1] = offset + 1;
			cubeIndices[i + 2] = offset + 2;
			cubeIndices[i + 3] = offset + 2;
			cubeIndices[i + 4] = offset + 3;
			cubeIndices[i + 5] = offset + 0;

			// Right
			cubeIndices[i + 6] = offset + 1;
			cubeIndices[i + 7] = offset + 5;
			cubeIndices[i + 8] = offset + 6;
			cubeIndices[i + 9] = offset + 6;
			cubeIndices[i + 10] = offset + 2;
			cubeIndices[i + 11] = offset + 1;

			// Back
			cubeIndices[i + 12] = offset + 7;
			cubeIndices[i + 13] = offset + 6;
			cubeIndices[i + 14] = offset + 5;
			cubeIndices[i + 15] = offset + 5;
			cubeIndices[i + 16] = offset + 4;
			cubeIndices[i + 17] = offset + 7;

			// Left
			cubeIndices[i + 18] = offset + 4;
			cubeIndices[i + 19] = offset + 0;
			cubeIndices[i + 20] = offset + 3;
			cubeIndices[i + 21] = offset + 3;
			cubeIndices[i + 22] = offset + 7;
			cubeIndices[i + 23] = offset + 4;

			// Bottom
			cubeIndices[i + 24] = offset + 4;
			cubeIndices[i + 25] = offset + 5;
			cubeIndices[i + 26] = offset + 1;
			cubeIndices[i + 27] = offset + 1;
			cubeIndices[i + 28] = offset + 0;
			cubeIndices[i + 29] = offset + 4;

			// Top
			cubeIndices[i + 30] = offset + 3;
			cubeIndices[i + 31] = offset + 2;
			cubeIndices[i + 32] = offset + 6;
			cubeIndices[i + 33] = offset + 6;
			cubeIndices[i + 34] = offset + 7;
			cubeIndices[i + 35] = offset + 3;

			offset += 8;
		}

		Ref<IndexBuffer> cubeIb = IndexBuffer::Create(cubeIndices, s_Data3D.MaxIndices);
		s_Data3D.CubeVertexArray->SetIndexBuffer(cubeIb);
		delete[] cubeIndices;

		s_Data3D.WhiteTexture = Texture2D::Create(1, 1);
		uint32_t whiteTexture = 0xffffffff;
		s_Data3D.WhiteTexture->SetData(&whiteTexture, sizeof(uint32_t));

		int32_t samplers[s_Data3D.MaxTextureSlots];
		for (int32_t i = 0; i < s_Data3D.MaxTextureSlots; i++)
			samplers[i] = i;

		s_Data3D.TextureSlots[0] = s_Data3D.WhiteTexture;

		s_Data3D.Renderer3DShader = Shader::Create("assets/shaders/Renderer3D.glsl");
		s_Data3D.Renderer3DShader->Bind();
		s_Data3D.Renderer3DShader->SetIntArray("u_Textures", samplers, s_Data3D.MaxTextureSlots);

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
	}

	void Renderer3D::Shutdown()
	{
		delete[] s_Data3D.CubeVertexBufferBase;
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
		s_Data3D.Renderer3DShader->Bind();
		s_Data3D.Renderer3DShader->SetMat4("u_VP", camera.GetViewProjectionMatrix());

		s_Data3D.CubeIndexCount = 0;
		s_Data3D.CubeVertexBufferPtr = s_Data3D.CubeVertexBufferBase;
		s_Data3D.TextureSlotIndex = 1;
	}

	void Renderer3D::EndScene()
	{
		uint32_t bufferSize = (uint32_t)((uint8_t*)s_Data3D.CubeVertexBufferPtr - (uint8_t*)s_Data3D.CubeVertexBufferBase);
		s_Data3D.CubeVertexBuffer->SetData(s_Data3D.CubeVertexBufferBase, bufferSize);

		Flush();
	}

	void Renderer3D::Flush()
	{
		if (s_Data3D.CubeIndexCount == 0)
			return; // Nothing to draw

		for (uint32_t i = 0; i < s_Data3D.TextureSlotIndex; i++)
			s_Data3D.TextureSlots[i]->Bind(i);

		s_Data3D.Renderer3DShader->Bind();
		RenderCommand::DrawIndexed(s_Data3D.CubeVertexArray, s_Data3D.CubeIndexCount);
		s_Data3D.Stats.DrawCalls++;
	}

	void Renderer3D::FlushAndReset()
	{
		EndScene();

		s_Data3D.CubeIndexCount = 0;
		s_Data3D.CubeVertexBufferPtr = s_Data3D.CubeVertexBufferBase;

		s_Data3D.TextureSlotIndex = 1;
	}

	void Renderer3D::DrawQuad(const glm::vec3& position, const glm::vec3& size, const glm::vec4& color)
	{
		if (s_Data3D.CubeIndexCount >= s_Data3D.MaxIndices)
			FlushAndReset();

		glm::mat4 model = glm::translate(glm::mat4(1.0f), position)
			* glm::scale(glm::mat4(1.0f), size);
		
		constexpr size_t vertexCount = 8;
		const float textureIndex = 0.0f; // White texture
		constexpr glm::vec2 textureCoords[] = { { 0.0f, 0.0f }, { 1.0f, 0.0f }, { 1.0f, 1.0f }, { 0.0f, 1.0f },
												{ 0.0f, 0.0f }, { 1.0f, 0.0f }, { 1.0f, 1.0f }, { 0.0f, 1.0f } };
		const float tilingFactor = 1.0f;

		for (size_t i = 0; i < vertexCount; i++)
		{
			s_Data3D.CubeVertexBufferPtr->Position = model * s_Data3D.CubePositions[i];
			s_Data3D.CubeVertexBufferPtr->TexCoord = textureCoords[i];
			s_Data3D.CubeVertexBufferPtr->Color = color;
			s_Data3D.CubeVertexBufferPtr->TexIndex = textureIndex;
			s_Data3D.CubeVertexBufferPtr->TilingFactor = tilingFactor;
			s_Data3D.CubeVertexBufferPtr++;
		}

		s_Data3D.CubeIndexCount += 36;

		s_Data3D.Stats.QuadCount++;
	}

	void Renderer3D::DrawQuad(const glm::vec3& position, const glm::vec3& size, const Ref<Texture2D>& texture, float tilingFactor /*= 1.0f*/, const glm::vec4& tintColor /*= glm::vec4(1.0f)*/)
	{
		glm::mat4 model = glm::translate(glm::mat4(1.0f), position)
			* glm::scale(glm::mat4(1.0f), size);

		constexpr size_t vertexCount = 8;
		constexpr glm::vec2 textureCoords[] = { { 0.0f, 0.0f }, { 1.0f, 0.0f }, { 1.0f, 1.0f }, { 0.0f, 1.0f },
												{ 0.0f, 0.0f }, { 1.0f, 0.0f }, { 1.0f, 1.0f }, { 0.0f, 1.0f } };

		float textureIndex = 0.0f;
		for (uint32_t i = 0; i < s_Data3D.TextureSlotIndex; i++)
		{
			if (*s_Data3D.TextureSlots[i].get() == *texture.get())
			{
				textureIndex = (float)i;
				break;
			}
		}

		if (textureIndex == 0.0f)
		{
			textureIndex = (float)s_Data3D.TextureSlotIndex;
			s_Data3D.TextureSlots[s_Data3D.TextureSlotIndex] = texture;
			s_Data3D.TextureSlotIndex++;
		}

		for (size_t i = 0; i < vertexCount; i++)
		{
			s_Data3D.CubeVertexBufferPtr->Position = model * s_Data3D.CubePositions[i];
			s_Data3D.CubeVertexBufferPtr->TexCoord = textureCoords[i];
			s_Data3D.CubeVertexBufferPtr->Color = tintColor;
			s_Data3D.CubeVertexBufferPtr->TexIndex = textureIndex;
			s_Data3D.CubeVertexBufferPtr->TilingFactor = tilingFactor;
			s_Data3D.CubeVertexBufferPtr++;
		}

		s_Data3D.CubeIndexCount += 36;

		s_Data3D.Stats.QuadCount++;
	}

	void Renderer3D::DrawRotatedQuad(const glm::vec3& position, const glm::vec3& size, float rotation, const glm::vec3& rotation_vec, const glm::vec4& color)
	{
		if (s_Data3D.CubeIndexCount >= s_Data3D.MaxIndices)
			FlushAndReset();

		glm::mat4 model = glm::translate(glm::mat4(1.0f), position)
			* glm::scale(glm::mat4(1.0f), size)
			* glm::rotate(glm::mat4(1.0f), glm::radians(rotation), rotation_vec);

		constexpr size_t vertexCount = 8;
		const float textureIndex = 0.0f; // White texture
		constexpr glm::vec2 textureCoords[] = { { 0.0f, 0.0f }, { 1.0f, 0.0f }, { 1.0f, 1.0f }, { 0.0f, 1.0f },
												{ 0.0f, 0.0f }, { 1.0f, 0.0f }, { 1.0f, 1.0f }, { 0.0f, 1.0f } };
		const float tilingFactor = 1.0f;

		for (size_t i = 0; i < vertexCount; i++)
		{
			s_Data3D.CubeVertexBufferPtr->Position = model * s_Data3D.CubePositions[i];
			s_Data3D.CubeVertexBufferPtr->TexCoord = textureCoords[i];
			s_Data3D.CubeVertexBufferPtr->Color = color;
			s_Data3D.CubeVertexBufferPtr->TexIndex = textureIndex;
			s_Data3D.CubeVertexBufferPtr->TilingFactor = tilingFactor;
			s_Data3D.CubeVertexBufferPtr++;
		}

		s_Data3D.CubeIndexCount += 36;

		s_Data3D.Stats.QuadCount++;
	}

}