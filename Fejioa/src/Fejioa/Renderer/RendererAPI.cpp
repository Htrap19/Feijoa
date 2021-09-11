#include "fjpch.h"
#include "RendererAPI.h"

#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace Fejioa
{

	RendererAPI::API RendererAPI::s_API = RendererAPI::API::OpenGL;

	Fejioa::Scope<Fejioa::RendererAPI> RendererAPI::Create()
	{
		switch (s_API)
		{
		case API::None: FJ_CORE_ASSERT(false, "RendererAPI::None is currently not supported!") return nullptr;
		case API::OpenGL: return CreateScope<OpenGLRendererAPI>();
		}

		FJ_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

}