#pragma once

#include "Feijoa/Core/Base.h"

namespace Feijoa
{
	struct FrameBufferSpecification
	{
		unsigned int Width, Height;
		unsigned int Samples = 1;
		bool SwapChainTarget = false;
	};

	class FrameBuffer
	{
	public:
		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual unsigned int GetColorAttachmentRendererID() const = 0;
		virtual const FrameBufferSpecification& GetSpecification() const = 0;

		static Ref<FrameBuffer> Create(const FrameBufferSpecification& spec);
	};
}