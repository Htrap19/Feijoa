#pragma once

#include "Feijoa/Renderer/Texture.h"
#include <glad/glad.h>

namespace Feijoa
{
	class OpenGLTexture2D : public Texture2D
	{
	public:
		OpenGLTexture2D(const std::string& path);
		OpenGLTexture2D(unsigned int width, unsigned int height);
		virtual ~OpenGLTexture2D();

		virtual inline unsigned int GetWidth() const override { return m_Width; }
		virtual inline unsigned int GetHeight() const override { return m_Height; }
		virtual inline unsigned int GetRendererID() const override { return m_RendererID; }

		virtual void SetData(void* data, unsigned int size) override;

		virtual void Bind(unsigned int slot = 0) const override;

		virtual inline bool operator==(const Texture& other) const override
		{
			return m_RendererID == ((OpenGLTexture2D&)other).m_RendererID;
		}

	private:
		unsigned int m_Width, m_Height;
		unsigned int m_RendererID;
		std::string m_Path;
		GLenum m_InternalFormat, m_DataFormat;
	};
}