#include "fjpch.h"
#include "FrameBuffer.h"

#include "Feijoa/Renderer/Renderer.h"
#include "Feijoa/Core/Log.h"

#include "Platform/OpenGL/OpenGLFrameBuffer.h"

namespace Feijoa
{

	Feijoa::Ref<Feijoa::FrameBuffer> FrameBuffer::Create(const FrameBufferSpecification& spec)
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