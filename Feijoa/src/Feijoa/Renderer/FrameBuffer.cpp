#include "fjpch.h"
#include "Framebuffer.h"

#include "Feijoa/Renderer/Renderer.h"
#include "Feijoa/Core/Log.h"

#include "Platform/OpenGL/OpenGLFramebuffer.h"

namespace Feijoa
{

	Ref<Framebuffer> Framebuffer::Create(const FramebufferSpecification& spec)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None: FJ_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case RendererAPI::API::OpenGL: return CreateRef<OpenGLFramebuffer>(spec);

		default:
			break;
		}

		FJ_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

}