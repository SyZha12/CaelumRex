#ifndef OPENGLBUFFER_H
#define OPENGLBUFFER_H

/* CaelumRex Libraries */
#include <Renderer/Buffer.h>

namespace CaelumRex
{
    class OpenGLVertexBuffer : public VertexBuffer
    {
    public:
        OpenGLVertexBuffer(uint32_t size);
        OpenGLVertexBuffer(const float* vertices, uint32_t size);
        ~OpenGLVertexBuffer() override;

        void Bind() override;
        void Unbind() override;

        void SetData(const void* data, uint32_t size) override;

        void SetLayout(const BufferLayout& layout) override { m_Layout = layout; }
        const BufferLayout& GetLayout() const override { return m_Layout; }
    private:
        uint32_t m_RendererID;
        BufferLayout m_Layout;
    };

    class OpenGLIndexBuffer : public IndexBuffer
    {
    public:
        OpenGLIndexBuffer(const uint32_t* indices, uint32_t count);
        ~OpenGLIndexBuffer() override;

        void Bind() override;
        void Unbind() override;

        uint32_t GetCount() override { return m_Count; }
    private:
        uint32_t m_RendererID;
        uint32_t m_Count;
    };
}

#endif //OPENGLBUFFER_H
