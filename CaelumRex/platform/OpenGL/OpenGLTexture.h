#ifndef OPENGLTEXTURE_H
#define OPENGLTEXTURE_H

/* CaelumRex Libraries */
#include <Renderer/Texture.h>

/* Third-Party Libraries & Co*/
#include <glad/glad.h>

namespace CaelumRex
{
    class OpenGLTexture2D : public Texture2D
    {
    public:
        OpenGLTexture2D(uint32_t width, uint32_t height);
        OpenGLTexture2D(const std::string& path);
        ~OpenGLTexture2D() override;

        uint32_t GetWidth() const override { return m_Width; }
        uint32_t GetHeight() const override { return m_Height; }

        void SetData(void* data, uint32_t size) override;

        void Bind(uint32_t slot = 0) const override;

        bool operator==(const Texture& other) const override { return m_RendererID == ((OpenGLTexture2D&)other).m_RendererID; }

    private:
        std::string m_Path;
        uint32_t m_Width, m_Height;
        uint32_t m_RendererID;
        GLenum m_InternalFormat, m_DataFormat;
    };
}

#endif //OPENGLTEXTURE_H
