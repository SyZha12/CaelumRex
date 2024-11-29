#ifndef OPENGLVERTEXARRAY_H
#define OPENGLVERTEXARRAY_H

/* CaelumRex Libraries */
#include <Renderer/VertexArray.h>

/* Third-Party Libraries & Co*/
#include <cstdint>

namespace CaelumRex
{
    class OpenGLVertexArray : public VertexArray
    {
        public:
            OpenGLVertexArray();
            ~OpenGLVertexArray() override;

            void Bind() override;
            void Unbind() override;

            void AddVertexBuffer(const Ref<VertexBuffer>& vertexBuffer) override;
            void SetIndexBuffer(const Ref<IndexBuffer>& indexBuffer) override;

            const std::vector<Ref<VertexBuffer>>& GetVertexBuffers() override { return m_VertexBuffers; }
            const Ref<IndexBuffer>& GetIndexBuffer() override { return m_IndexBuffer; }
        private:
            uint32_t m_RendererID;
            std::vector<Ref<VertexBuffer>> m_VertexBuffers;
            Ref<IndexBuffer> m_IndexBuffer;
    };
}

#endif //OPENGLVERTEXARRAY_H
