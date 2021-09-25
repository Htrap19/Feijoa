#include "fjpch.h"
#include "OpenGLTexture.h"

#include <stb_image.h>

namespace Feijoa
{

	OpenGLTexture2D::OpenGLTexture2D(const std::string& path)
		: m_Path(path)
	{
		FJ_PROFILE_FUNCTION();

		int width, height, channels;
		stbi_set_flip_vertically_on_load(true);
		stbi_uc* data = stbi_load(path.c_str(), &width, &height, &channels, 0);
		FJ_CORE_ASSERT(data, "Failed to load image!");
		m_Width = width;
		m_Height = height;

		GLenum internalFormat = 0, dataFormat = 0;
		if (channels == 4)
		{
			internalFormat = GL_RGBA8;
			dataFormat = GL_RGBA;
		}
		else if (channels == 3)
		{
			internalFormat = GL_RGB8;
			dataFormat = GL_RGB;
		}
		FJ_CORE_ASSERT(internalFormat & dataFormat, "Format not supported!");
		m_InternalFormat = internalFormat;
		m_DataFormat = dataFormat;

		glGenTextures(1, &m_RendererID);
		glBindTexture(GL_TEXTURE_2D, m_RendererID);
		//glTexStorage2D(GL_TEXTURE_2D, 1, internalFormat, m_Width, m_Height);

		glTexParameteri(m_RendererID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(m_RendererID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		glTexParameteri(m_RendererID, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(m_RendererID, GL_TEXTURE_WRAP_T, GL_REPEAT);

		glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, m_Width, m_Height, 0, dataFormat, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);

		//glTexSubImage2D(GL_TEXTURE_2D, 0, m_Width / 2, m_Height / 2, m_Width, m_Height, dataFormat, GL_UNSIGNED_BYTE, data);
		stbi_image_free(data);
	}

	OpenGLTexture2D::OpenGLTexture2D(unsigned int width, unsigned int height)
		: m_Width(width), m_Height(height)
	{
		FJ_PROFILE_FUNCTION();

		m_InternalFormat = GL_RGBA8;
		m_DataFormat = GL_RGBA;

		glGenTextures(1, &m_RendererID);
		glBindTexture(GL_TEXTURE_2D, m_RendererID);

		glTexParameteri(m_RendererID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(m_RendererID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(m_RendererID, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(m_RendererID, GL_TEXTURE_WRAP_T, GL_REPEAT);
	}

	OpenGLTexture2D::~OpenGLTexture2D()
	{
		FJ_PROFILE_FUNCTION();

		glDeleteTextures(1, &m_RendererID);
	}

	void OpenGLTexture2D::SetData(void* data, unsigned int size)
	{
		FJ_PROFILE_FUNCTION();

		unsigned int bpp = m_DataFormat == GL_RGBA ? 4 : 3;
		FJ_CORE_ASSERT(size == m_Width * m_Height * bpp, "Data must be entire texture!");
		glBindTexture(GL_TEXTURE_2D, m_RendererID);
		glTexImage2D(GL_TEXTURE_2D, 0, m_InternalFormat, m_Width, m_Height, 0, m_DataFormat, GL_UNSIGNED_BYTE, data);
	}

	void OpenGLTexture2D::Bind(unsigned int slot /*= 0*/) const
	{
		FJ_PROFILE_FUNCTION();

		glActiveTexture(GL_TEXTURE0 + slot);
		glBindTexture(GL_TEXTURE_2D, m_RendererID);
	}

}