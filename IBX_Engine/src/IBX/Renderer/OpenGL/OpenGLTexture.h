#pragma once

#include "IBX/Renderer/Texture.h"
#include <glad/glad.h>

namespace IBX_Engine
{
	class OpenGLTexture2D : public Texture2D
	{
	public:
		OpenGLTexture2D(uint32_t width, uint32_t height);
		OpenGLTexture2D(const std::string& path);
		virtual ~OpenGLTexture2D();

		virtual uint32_t GetWidth() const override { return m_Width; }
		virtual uint32_t GetHeight() const override { return m_Height; }

		virtual void SetData(void* data, uint32_t size) override;

		virtual void Bind(uint32_t slot = 0) const override;
		virtual void Unbind() const override;

	private:
		uint32_t m_RendererID;
		std::string m_Path;

		uint32_t m_Width, m_Height;
		uint32_t m_Channels;

		GLenum m_InternalFormat, m_DataFormat;
	};
}