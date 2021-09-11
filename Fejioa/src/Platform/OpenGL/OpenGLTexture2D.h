#pragma once

#include "Fejioa/Renderer/Texture.h"
#include <glad/glad.h>

namespace Fejioa
{
	class OpenGLTexture2D : public Texture2D
	{
	public:
		OpenGLTexture2D(const std::string& path);
		OpenGLTexture2D(unsigned int width, unsigned int height);
		virtual ~OpenGLTexture2D();

		virtual inline unsigned int GetWidth() const override { return m_Width; }
		virtual inline unsigned int GetHeight() const override { return m_Height; }

		virtual void SetData(void* data, unsigned int size) override;

		virtual void Bind(unsigned int slot = 0) const override;

	private:
		unsigned int m_Width, m_Height;
		unsigned int m_RendererID;
		std::string m_Path;
		GLenum m_InternalFormat, m_DataFormat;
	};
}