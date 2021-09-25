#include "fjpch.h"
#include "VertexArray.h"

#include "Renderer.h"
#include "Platform/OpenGL/OpenGLVertexArray.h"

namespace Feijoa
{
	
	Ref<VertexArray> VertexArray::Create()
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None: FJ_CORE_ASSERT(false, "Renderer::None is currently not supported!"); return nullptr;
		case RendererAPI::API::OpenGL: return CreateRef<OpenGLVertexArray>();

		default:
			break;
		}

		FJ_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

}