#pragma once

#include <glm/glm.hpp>
#include <memory>

#include "VertexArray.h"

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
		virtual void Clear() = 0;
		virtual void SetClearColor(const glm::vec4& color) = 0;
		
		virtual void DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray) = 0;

		static inline API GetApi() { return s_API; }
	private:
		static API s_API;
	};
}