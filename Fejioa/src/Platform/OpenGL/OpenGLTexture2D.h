#pragma once

#include "Fejioa/Renderer/Texture.h"

namespace Fejioa
{
	class OpenGLTexture2D : public Texture2D
	{
	public:
		OpenGLTexture2D(const std::string& path);
		virtual ~OpenGLTexture2D();

		virtual inline unsigned int GetWidth() const override { return m_Width; }
		unsigned int GetHeight() const override { return m_Height; }
		void Bind(unsigned int slot = 0) const override;

	private:
		unsigned int m_Width, m_Height;
		unsigned int m_RendererID;
		std::string m_Path;
	};
}