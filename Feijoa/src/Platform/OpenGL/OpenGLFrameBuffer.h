#pragma once

#include "Feijoa/Renderer/FrameBuffer.h"

namespace Feijoa
{
	class OpenGLFrameBuffer : public FrameBuffer
	{
	public:
		OpenGLFrameBuffer(const FrameBufferSpecification& spec);
		virtual ~OpenGLFrameBuffer();

		void Invalidate();

		virtual void Bind() const override;
		virtual void Unbind() const override;

		virtual inline unsigned int GetColorAttachmentRendererID() const override { return m_ColorAttachment; }
		virtual inline const FrameBufferSpecification& GetSpecification() const override { return m_Specification; }

	private:
		unsigned int m_RendererID;
		unsigned int m_ColorAttachment, m_DepthAttachment;
		FrameBufferSpecification m_Specification;
	};
}