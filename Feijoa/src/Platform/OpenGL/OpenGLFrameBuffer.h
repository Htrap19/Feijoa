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

		virtual void Resize(uint32_t width, uint32_t height) override;

		virtual inline uint32_t GetColorAttachmentRendererID(uint32_t index = 0) const override { FJ_ASSERT(index < m_ColorAttachments.size()); return m_ColorAttachments[index]; }
		virtual inline const FrameBufferSpecification& GetSpecification() const override { return m_Specification; }

	private:
		uint32_t m_RendererID = 0;
		FrameBufferSpecification m_Specification;
		std::vector<FrameBufferTextureSpecification> m_ColorAttachmentSpecifications;
		FrameBufferTextureSpecification m_DepthAttachmentSpecification = FrameBufferTextureFormat::None;
		std::vector<uint32_t> m_ColorAttachments;
		uint32_t m_DepthAttachment = 0;
	};
}