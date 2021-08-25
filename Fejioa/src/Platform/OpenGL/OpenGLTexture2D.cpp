#include "fjpch.h"
#include "OpenGLTexture2D.h"

#include "stb_image.h"
#include <glad/glad.h>

namespace Fejioa
{

	OpenGLTexture2D::OpenGLTexture2D(const std::string& path)
		: m_Path(path)
	{
		int width, height, channels;
		stbi_set_flip_vertically_on_load(true);
		stbi_uc* data = stbi_load(path.c_str(), &width, &height, &channels, 0);
		FJ_CORE_ASSERT(data, "Failed to load image!");
		m_Width = width;
		m_Height = height;

		glGenTextures(1, &m_RendererID);
		glBindTexture(GL_TEXTURE_2D, m_RendererID);
		glTexStorage2D(GL_TEXTURE_2D, 0, GL_RGB8, m_Width, m_Height);

		glTexParameteri(m_RendererID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(m_RendererID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		GLenum format = GL_RGB;
		switch (channels)
		{
		case 1:
			format = GL_R;
			break;
		case 4:
			format = GL_RGBA;
			break;

		default:
			break;
		}

		glTexImage2D(GL_TEXTURE_2D, 0, format, m_Width, m_Height, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);

		// glTexSubImage2D(GL_TEXTURE_2D, 0, m_Width / 2, m_Height / 2, m_Width, m_Height, format, GL_UNSIGNED_BYTE, data);
		stbi_image_free(data);
	}

	OpenGLTexture2D::~OpenGLTexture2D()
	{
		glDeleteTextures(1, &m_RendererID);
	}

	void OpenGLTexture2D::Bind(unsigned int slot /*= 0*/) const
	{
		glBindTexture(GL_TEXTURE_2D, m_RendererID);
		glActiveTexture(GL_TEXTURE0 + slot);
	}

}