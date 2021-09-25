#pragma once

#include "Feijoa/Renderer/RenderCommand.h"
#include "Feijoa/Renderer/OrthographicCamera.h"
#include "Feijoa/Renderer/Shader.h"

namespace Feijoa
{
	class Renderer
	{
	public:
		static void Init();
		static void Shutdown();
		static void OnWindowResize(uint32_t width, uint32_t height);
		static void BeginScene(OrthographicCamera& camera);
		static void EndScene();

		static void Submit(const Ref<Shader>& shader, const Ref<VertexArray>& vertexArray, const glm::mat4& transform);

		static inline RendererAPI::API GetAPI() { return RendererAPI::GetApi(); }

	private:
		struct SceneData
		{
			glm::mat4 ViewProjectionMatrix;
		};

		static SceneData* m_SceneData;
	};
}