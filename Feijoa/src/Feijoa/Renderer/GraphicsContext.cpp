#include "fjpch.h"
#include "GraphicsContext.h"

#include "Feijoa/Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLContext.h"

namespace Feijoa
{

	Feijoa::Scope<Feijoa::GraphicsContext> GraphicsContext::Create(GLFWwindow* window)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None: FJ_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case RendererAPI::API::OpenGL: return CreateScope<OpenGLContext>(window);

		default:
			break;
		}

		FJ_CORE_ASSERT(false, "Unknown RendererAPI");
		return nullptr;
	}

}