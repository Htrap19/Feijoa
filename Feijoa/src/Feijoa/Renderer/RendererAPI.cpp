#include "fjpch.h"
#include "RendererAPI.h"

#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace Feijoa
{

	RendererAPI::API RendererAPI::s_API = RendererAPI::API::OpenGL;

	Feijoa::Scope<Feijoa::RendererAPI> RendererAPI::Create()
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