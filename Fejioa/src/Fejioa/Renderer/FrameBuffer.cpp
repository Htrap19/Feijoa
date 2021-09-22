#include "fjpch.h"
#include "FrameBuffer.h"

#include "Fejioa/Renderer/Renderer.h"
#include "Fejioa/Core/Log.h"

#include "Platform/OpenGL/OpenGLFrameBuffer.h"

namespace Fejioa
{

	Fejioa::Ref<Fejioa::FrameBuffer> FrameBuffer::Create(const FrameBufferSpecification& spec)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None: FJ_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case RendererAPI::API::OpenGL: return CreateRef<OpenGLFrameBuffer>(spec);

		default:
			break;
		}

		FJ_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

}