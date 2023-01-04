#pragma once

#include "Feijoa/Renderer/PerspectiveCamera.h"
#include "Feijoa/Renderer/Texture.h"
#include "Feijoa/Scene/SceneCamera.h"

namespace Feijoa
{
	struct RenderMesh;
	struct ModelVertex
	{
		glm::vec3 Position;
		glm::mat4 Model;
		glm::vec4 Color;
		glm::vec2 TexCoord = glm::vec2(0.0f);
		float TexIndex;
	};

	class Renderer3D
	{
	public:
		struct Statistics
		{
			uint32_t DrawCalls = 0;
			uint32_t MeshCount = 0;
			uint32_t ModelTotalVertexCount = 0;
			uint32_t ModelTotalIndexCount = 0;
		};

	public:
		static void Init();
		static void Shutdown();

		static void ResetStats();
		static Statistics GetStats();

		static void BeginScene(const Camera& camera, const glm::mat4& view);
		static void BeginScene(PerspectiveCamera& camera);
		static void EndScene();
		static void Flush();

		static void DrawMesh(const glm::mat4& model, const RenderMesh& mesh, const glm::vec4& color = glm::vec4(1.0f));
		static void DrawMesh(const glm::vec3& position, const glm::vec3& size, const RenderMesh& mesh);

	private:
		static void FlushAndReset();
	};
}