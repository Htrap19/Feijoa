#include "fjpch.h"
#include "Buffer.h"

#include "Feijoa/Renderer/Renderer.h"

#include "Platform/OpenGL/OpenGLBuffer.h"

namespace Feijoa
{
	Ref<VertexBuffer> VertexBuffer::Create(unsigned int size)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None: FJ_CORE_ASSERT(false, "Renderer::None is currently not supported!"); return nullptr;
		case RendererAPI::API::OpenGL: return CreateRef<OpenGLVertexBuffer>(size);

		default:
			break;
		}

		FJ_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

	Ref<VertexBuffer> VertexBuffer::Create(float* vertices, unsigned int size)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None: FJ_CORE_ASSERT(false, "Renderer::None is currently not supported!"); return nullptr;
		case RendererAPI::API::OpenGL: return CreateRef<OpenGLVertexBuffer>(vertices, size);

		default:
			break;
		}

		FJ_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

	Ref<IndexBuffer> IndexBuffer::Create(unsigned int* indices, unsigned int count)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None: FJ_CORE_ASSERT(false, "Renderer::None is currently not supported!"); return nullptr;
		case RendererAPI::API::OpenGL: return CreateRef<OpenGLIndexBuffer>(indices, count * sizeof(unsigned int));

		default:
			break;
		}

		FJ_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

}