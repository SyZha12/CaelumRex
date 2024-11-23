#ifndef OPENGLBUFFER_H
#define OPENGLBUFFER_H

#include "Renderer/Buffer.h"

namespace CaelumRex
{
    class OpenGLVertexBuffer : public VertexBuffer
    {
    public:
        OpenGLVertexBuffer(float* vertices, u_int32_t size);
        ~OpenGLVertexBuffer() override;

        void Bind() override;
        void Unbind() override;
    private:
        u_int32_t m_RendererID;
    };

    class OpenGLIndexBuffer : public IndexBuffer
    {
    public:
        OpenGLIndexBuffer(u_int32_t* indices, u_int32_t count);
        ~OpenGLIndexBuffer() override;

        void Bind() override;
        void Unbind() override;

        u_int32_t GetCount() { return m_Count; }
    private:
        u_int32_t m_RendererID;
        u_int32_t m_Count;
    };
}

#endif //OPENGLBUFFER_H
