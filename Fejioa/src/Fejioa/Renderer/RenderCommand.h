#pragma once

#include "Fejioa/Renderer/RendererAPI.h"

namespace Fejioa
{
	class RenderCommand
	{
	public:
		static inline void Init() { s_RendererAPI->Init(); }
		static inline void SetViewport(unsigned int x, unsigned int y, unsigned int width, unsigned int height) { s_RendererAPI->SetViewport(x, y, width, height); }
		static inline void Clear() { s_RendererAPI->Clear(); }
		static inline void SetClearColor(const glm::vec4& color) { s_RendererAPI->SetClearColor(color); }
		static inline void DrawIndexed(const Ref<VertexArray>& vertexArray, unsigned int count = 0) { s_RendererAPI->DrawIndexed(vertexArray, count); }

	private:
		static Scope<RendererAPI> s_RendererAPI;
	};
}