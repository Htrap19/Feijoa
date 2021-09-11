#pragma once

#include <glm/glm.hpp>
#include <memory>

#include "Fejioa/Renderer/VertexArray.h"

namespace Fejioa
{
	class RendererAPI
	{
	public:
		enum class API
		{
			None = 0, OpenGL = 1
		};

	public:
		virtual ~RendererAPI() = default;
		
		virtual void Init() = 0;
		virtual void SetViewport(unsigned int x, unsigned int y, unsigned int width, unsigned int height) = 0;
		virtual void Clear() = 0;
		virtual void SetClearColor(const glm::vec4& color) = 0;
		
		virtual void DrawIndexed(const Ref<VertexArray>& vertexArray) = 0;

		static inline API GetApi() { return s_API; }
		static Scope<RendererAPI> Create();
	private:
		static API s_API;
	};
}