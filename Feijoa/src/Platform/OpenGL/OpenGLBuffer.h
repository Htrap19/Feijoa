#pragma once

#include "Feijoa/Renderer/Buffer.h"

namespace Feijoa
{
	class OpenGLVertexBuffer : public VertexBuffer
	{
	public:
		OpenGLVertexBuffer(unsigned int size);
		OpenGLVertexBuffer(float* vertices, unsigned int size);
		virtual ~OpenGLVertexBuffer();

		virtual void Bind() const override;
		virtual void Unbind() const override;

		virtual void SetData(const void* data, unsigned int size) override;

		inline void SetLayout(const BufferLayout& layout) override { m_Layout = layout; }
		inline const BufferLayout& GetLayout() const override { return m_Layout; }

	private:
		unsigned int m_RendererID;
		BufferLayout m_Layout;
	};

	class OpenGLIndexBuffer : public IndexBuffer
	{
	public:
		OpenGLIndexBuffer(unsigned int* indices, unsigned int count);
		virtual ~OpenGLIndexBuffer();

		virtual void Bind() const override;
		virtual void Unbind() const override;

		virtual inline unsigned int GetCount() const override { return m_Count; }

	private:
		unsigned int m_RendererID, m_Count;
	};
}