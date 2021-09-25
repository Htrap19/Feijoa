#pragma once

#include "Feijoa/Renderer/RendererAPI.h"

namespace Feijoa
{
	class RenderCommand
	{
	public:
		static inline void Init() { s_RendererAPI->Init(); }
		static inline void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) { s_RendererAPI->SetViewport(x, y, width, height); }
		static inline void Clear() { s_RendererAPI->Clear(); }
		static inline void SetClearColor(const glm::vec4& color) { s_RendererAPI->SetClearColor(color); }
		static inline void DrawIndexed(const Ref<VertexArray>& vertexArray, uint32_t count = 0) { s_RendererAPI->DrawIndexed(vertexArray, count); }

	private:
		static Scope<RendererAPI> s_RendererAPI;
	};
}